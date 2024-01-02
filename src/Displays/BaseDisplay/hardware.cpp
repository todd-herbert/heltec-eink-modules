/*
    File: hardware.cpp

        - Direct interface with the display
*/

#include "base.h"

// Allocate memory to the pagefile(s)
void BaseDisplay::grabPageMemory() {
    page_black = new uint8_t[page_bytecount];

    if (supportsColor(RED))     // Only if 3-color disply
        page_red = new uint8_t[page_bytecount];
}

// Free pagefile memory
void BaseDisplay::freePageMemory() {
    delete[] page_black;

    if (supportsColor(RED))     // Only if 3-color display
        delete[] page_red;
}

void BaseDisplay::sendCommand(uint8_t command) {
    display_spi->beginTransaction(spi_settings);
    digitalWrite(pin_dc, LOW);  // D/C pin LOW means SPI transfer is a command
    digitalWrite(pin_cs, LOW);

    display_spi->transfer(command);

    digitalWrite(pin_cs, HIGH);
    display_spi->endTransaction();
}

void BaseDisplay::sendData(uint8_t data) {
    display_spi->beginTransaction(spi_settings);
    digitalWrite(pin_dc, HIGH);     // D/C pin HIGH means SPI transfer is data
    digitalWrite(pin_cs, LOW);

    display_spi->transfer(data);

    digitalWrite(pin_cs, HIGH);
    display_spi->endTransaction();
}

// Soft-reset the display
void BaseDisplay::softReset() {
    sendCommand(0x12);
    wait();
}

// Wait until the display hardware is idle. Important as any commands made while "busy" will be discarded.
void BaseDisplay::wait() {
    while(digitalRead(pin_busy) == HIGH) {      // Pin is HIGH when busy
        delay(1);
    }
}

/// Write one page to the panel memory
void BaseDisplay::writePage() {

    // Call begin() automatically. 
    // TODO: require manual call in next major version, breaking change.
    begin();

    // Intercept here for WRITE_CANVAS
    // Potentially disabled by optimization.h
    #if !defined(__AVR_ATmega328P__) || defined(UNO_ENABLE_SDWRITE)
        if (writing_canvas) {
            writePageToCanvas();
            return; // Don't draw to screen at same time?
        }
    #endif

    // Calculate rotated x start and stop values (y is already done via paging)
    int16_t sx, sy, ex, ey;
    calculateMemoryArea(sx, sy, ex, ey);  // Virtual, derived class
    setMemoryArea(sx, sy, ex, ey);
   

    // Now we can send over our image data
    sendCommand(0x24);   // Write "BLACK" memory
    for (uint16_t i = 0; i < pagefile_length; i++) {
        sendData(page_black[i]);
    }

    if ( supportsColor(RED) ) {   // If 3-Color red display
        sendCommand(0x26);          // Write memory for red(1)/white (0)
        for (uint16_t i = 0; i < pagefile_length; i++) {
            sendData(page_red[i]);
        }
    }

    else {  // Black and White only

        // Write so-called "RED" memory. With this display, the memory is used during fastmode.
        // Counter-intuitively, need to write both BLACK and RED during normal use.
        // This preserves the image when moving into fastmode.

        if(fastmode_state == OFF) {
            sendCommand(0x26);
            for (uint16_t i = 0; i < pagefile_length; i++) {
                sendData(page_black[i]);
            }
        }
    }

    wait();
}

// Inform the display of selected memory area
void BaseDisplay::setMemoryArea(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey) {
    // Split into bytes
    uint8_t sy1, sy2, ey1, ey2;
    sy1 = sy & 0xFF;
    sy2 = (sy >> 8) & 0xFF;
    ey1 = ey & 0xFF;
    ey2 = (ey >> 8) & 0xFF;

    // Data entry mode - Left to Right, Top to Bottom
    sendCommand(0x11);
    sendData(0x03);

    // Inform the panel hardware of our chosen memory location
    sendCommand(0x44);  // Memory X start - end
    sendData(sx);
    sendData(ex);
    sendCommand(0x45);  // Memory Y start - end
    sendData(sy1);
    sendData(sy2);
    sendData(ey1);
    sendData(ey2);
    sendCommand(0x4E);  // Memory cursor X
    sendData(sx);
    sendCommand(0x4F);  // Memory cursor y
    sendData(sy1);
    sendData(sy2);
}

// Send power-off signal to your custom power switching circuit, and set the display pins to prevent unwanted current flow
void BaseDisplay::externalPowerOff(uint16_t pause) {
    // If poweroff is called immediately after drawing, it can compromise the image
    delay(pause);

    // Stop SPI
    display_spi->end();

    // Send the power-down signal
    digitalWrite(pin_power, !switch_type);

    // Set the logic pins: prevent a small current return path
    digitalWrite(pin_dc, switch_type);
    digitalWrite(pin_cs, switch_type);
    digitalWrite(pin_sdi, switch_type);
    digitalWrite(pin_clk, switch_type);

    // Same, if we're using sd card
    if (pin_cs_card != 0xFF) {
        digitalWrite(pin_cs_card, switch_type);
        digitalWrite(pin_miso, switch_type);
    }
}

// Send power-on signal to your custom power switching circuit, then re-init display
void BaseDisplay::externalPowerOn() {

    // CS pin deselcted; power-up the display
    digitalWrite(pin_cs, HIGH);
    digitalWrite(pin_power, switch_type);

    // Wait for powerup
    delay(50);

    // SPI resumes
    Platform::beginSPI(display_spi, pin_miso, pin_miso, pin_clk);
    
    // SAMD21: Move the SPI pins back to custom location
    #ifdef __SAMD21G18A__
        if (pin_sdi != MOSI || pin_clk != SCK || pin_miso != MISO)
            Platform::setSPIPins(pin_sdi, pin_clk, pin_miso);
    #endif

    // Re-load settings for full-refresh
    fastmodeOff();

    // Mark display as potentially out of sync with memory
    just_restarted = true;

    // Re-initialize display memory
    #if PRESERVE_IMAGE
        if (pagefile_height == panel_height)
            writePage();
        else        
            clear(false);   // If user has (for some reason) re-enabled paging on a fancy mcu
    #else
        // No record of old image, just fill blank
        clear(false);
    #endif
}

// Clear the screen in one optimized step - public
void BaseDisplay::clear() {
    clear(true);
}

// Private clear method, with optional refresh
void BaseDisplay::clear(bool refresh) {

    // Call begin() automatically. 
    // TODO: require manual call in next major version, breaking change.
    begin();

    // Store current settings
    uint16_t page_top_original = page_top;
    uint16_t page_bottom_original = page_bottom;
    Fastmode mode_original = fastmode_state;
    uint8_t rotation_original = rotation;
    uint16_t l = bounds.window.left();
    uint16_t t = bounds.window.top();
    uint16_t w = bounds.window.width();
    uint16_t h = bounds.window.height();

    // Back to default settings, temporarily
    fastmodeOff();
    fullscreen();

    // Claim that the page file is "fullscreen", even though it isn't
    page_top = 0;
    page_bottom = panel_height - 1;

    int16_t sx, sy, ex, ey;
    calculateMemoryArea(sx, sy, ex, ey);  // Virtual, derived class
    setMemoryArea(sx, sy, ex, ey);

    uint16_t x, y;
    uint8_t black_byte, red_byte;

    black_byte = (default_color & WHITE) * 255;          // We're filling in bulk here; bits are either all on or all off
    if (supportsColor(RED))
        red_byte = ((default_color & RED) >> 1) * 255;
    else
        red_byte = black_byte;

    sendCommand(0x24);   // Fill "BLACK" memory with default_color
    for(y = 0; y < (panel_width / 8) + 1; y++) {    // (+1 overscan)
        for(x = 0; x < panel_height; x++) {
            sendData(black_byte);
        }
    }

    sendCommand(0x26);   // Fill "RED" memory with default_color
    for(y = 0; y < (panel_width / 8) + 1; y++) {  // (+1 overscan)
        for(x = 0; x < panel_height; x++) {
            sendData(red_byte);
        }
    }

    // Update the display with blank memory
    if (refresh) {
        activate(); 

        // Track state of display memory (re:externalPowerOn)
        display_cleared = true;
        just_restarted = false;
    }    

    // Restore old settings
    if (mode_original == Fastmode::ON)
        fastmodeOn();
    else if(mode_original == Fastmode::TURBO)
        fastmodeTurbo();

    setRotation(rotation_original);
    setWindow(l, t, w, h);
    page_top = page_top_original;
    page_bottom = page_bottom_original;
    
}

#if PRESERVE_IMAGE
    // Manually update display, drawing on-top of existing contents
    void BaseDisplay::update() {

        // Init display, if needed
        if (fastmode_state == NOT_SET)
            fastmodeOff();

        // Copy the local image data to the display memory, then update
        writePage();
        activate(); 

        // If fastmode setting requires, repeat
        if (fastmode_state == ON) {
            writePage();
            activate(); 
        }

        // Track state of display memory (re:externalPowerOn)
        display_cleared = false;
        just_restarted = false;
    }
#endif