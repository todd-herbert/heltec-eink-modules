#include "DEPG0154BNS800.h"

// Out-of-line definition for LUT
// Required for an in-class PROGMEM definition
PROGMEM constexpr uint8_t DEPG0154BNS800::lut_partial[];

// Constructor
DEPG0154BNS800::DEPG0154BNS800(uint8_t pin_dc, uint8_t pin_cs, uint8_t pin_busy, uint16_t page_height) : GFX(panel_width, panel_height) {
    
    // Store the config
    this->pin_dc = pin_dc;
    this->pin_cs = pin_cs;
    this->pin_busy = pin_busy;
    this->pagefile_height = page_height;

    // Pass references to nested classes
    this->bounds = Bounds(  &winrot_top, 
                        &winrot_right, 
                        &winrot_bottom, 
                        &winrot_left, 
                        &rotation,
                        &imgflip);

    // Set the digital pins that supplement the SPI interface
    pinMode(pin_cs, OUTPUT);        // Incase we weren't give the standard pin 10 as SS
    pinMode(pin_dc, OUTPUT);
    pinMode(pin_busy, INPUT);   // NOTE: do not use internal pullups, as we're reading a 3.3v output with our ~5v arduino
    
    // Prepare SPI
    digitalWrite(pin_cs, HIGH); // Helpful if using more than one display
    SPI_BEGIN();

    // Calculate pagefile size
    pagefile_height = constrain(pagefile_height, 1, 50);
    page_bytecount = panel_width * pagefile_height / 8;

    // Set an initial configuration for drawing
    setDefaultColor(colors.WHITE);
    setTextColor(colors.BLACK);
    fullscreen();
}

/// Clear the screen in one step
void DEPG0154BNS800::clear() {
    reset();
    
    int16_t x, y;
    uint8_t blank_byte = (default_color & colors.WHITE) * 255;  // We're filling in bulk here; bits are either all on or all off

    // Calculate memory values for the slice
    // Note, x values are divided by 8 as horizontal lines are rows of 8bit bytes
    const uint8_t start_x = 1;  // Note the offset
    const uint8_t end_x = (panel_width / 8);        // This is taken from the official heltec driver

    // y locations are two bytes
    const uint8_t start_y = 0;
    const uint8_t end_y = panel_height - 1;

    // Data entry mode - Left to Right, Top to Bottom
    sendCommand(0x11);
      sendData(0x03);

    // Inform the panel hardware of our chosen memory location
    sendCommand(0x44);  // Memory X start - end
    sendData(start_x);
    sendData(end_x);
    sendCommand(0x45);  // Memory Y start - end
    sendData(start_y);
    sendData(0);                                        // Bit 8 - not required, max y is 250
    sendData(end_y);
    sendData(0);                                        // Bit 8 - not required, max y is 250
    sendCommand(0x4E);  // Memory cursor X
    sendData(start_x);
    sendCommand(0x4F);  // Memory cursor y
    sendData(start_y);
    sendData(0);                                        // Bit 8 - not required, max y is 250

    sendCommand(0x24);   // Fill "BLACK" memory with default_color
    for(y = 0; y < panel_width / 8; y++) {
        for(x = 0; x < panel_height; x++) {
            sendData(blank_byte);
        }
      }

    sendCommand(0x26);   // Fill "RED" memory with default_color
    for(y = 0; y < panel_width / 8; y++) {
        for(x = 0; x < panel_height; x++) {
            sendData(blank_byte);
        }
      }
    
    // Trigger the display update
    sendCommand(0x22);
    sendData(0xF7);
    sendCommand(0x20);
    wait();
}


// Allocate and Deallocate dynamic memory for graphics operations

void DEPG0154BNS800::grabPageMemory() {
    page_black = new uint8_t[page_bytecount];
}

void DEPG0154BNS800::freePageMemory() {
    delete[] page_black;
}

// Interface directly with display

void DEPG0154BNS800::sendCommand(uint8_t command) {
    SPI.beginTransaction(spi_settings);
    digitalWrite(pin_dc, LOW);  // Data-Command pin LOW, tell PanelHardware this SPI transfer is a command
    digitalWrite(pin_cs, LOW);

    SPI.transfer(command);

    digitalWrite(pin_cs, HIGH);
    SPI.endTransaction();
}

void DEPG0154BNS800::sendData(uint8_t data) {
    SPI.beginTransaction(spi_settings);
    digitalWrite(pin_dc, HIGH); // Data-Command pin HIGH, tell PanelHardware this SPI transfer is data
    digitalWrite(pin_cs, LOW);

    SPI.transfer(data);

    digitalWrite(pin_cs, HIGH);
    SPI.endTransaction();
}

/// Reset the panel
void DEPG0154BNS800::reset() {
    if (mode == fastmode.OFF) {
        sendCommand(0x12); // Software Reset
        wait();
    }
}

/// Wait until the PanelHardware is idle. Important as any commands made while Panel Hardware is busy will be discarded.
void DEPG0154BNS800::wait() {
    while(digitalRead(pin_busy) == HIGH)    {   // Low = idle   
        delay(1);
    }
}


/// Specify the technique used to draw the image onto the screen
void DEPG0154BNS800::setFastmode(FastmodeList::Fastmode mode) {

    // Moving to partial refresh (fastmode)
    if (mode == fastmode.ON && this->mode != fastmode.ON) {
        reset();

        // Technical settings on display, to allow partial refresh (fastmode). Released by Heltec.
        // -----------------------------------------------
        unsigned char count;
        sendCommand(0x32);      // "LUT"
        for(count=0; count < sizeof(lut_partial); count++) 
            sendData(pgm_read_byte_near(lut_partial + count)); 
        wait();

        sendCommand(0x3F);      // "Option for LUT end"
        sendData(0x02);

        sendCommand(0x03);      // "Gate voltage"  
        sendData(0x17);

        sendCommand(0x04);      // "Source voltage"   
        sendData(0x41); 
        sendData(0xB0);
        sendData(0x32);

        sendCommand(0x2C);      // allegedly: vcom   
        sendData(0x28);
                                    
        sendCommand(0x37);      // "Write Register for Display Option"
        sendData(0x00);         // Heltec comment: "Local flash function is enabled, pingpong mode is enabled"
        sendData(0x00);  
        sendData(0x00);  
        sendData(0x00); 
        sendData(0x00);     
        sendData(0x40);  
        sendData(0x00);  
        sendData(0x00);   
        sendData(0x00);  
        sendData(0x00);

        sendCommand(0x3C);  // "Border Waveform Control"
        sendData(0x80);
        // -------------------------------------------------

    }

    // If incorrectly entered fastmode, recurse
    else if (mode == fastmode.FINALIZE && this->mode == fastmode.OFF)
        setFastmode(fastmode.ON);

    // If explicitly leaving fastmode.
    //This shouldn't really be called in normal usage, but just in case: if moving out of fastmode ex
    else if (mode == fastmode.OFF)
        reset();

    // Store the mode
    this->mode = mode;
}

/// Write one page to the panel memory
void DEPG0154BNS800::writePage() {
    // Calculate rotate x start and stop values (y is already done via paging)
    int16_t sx, sy, ex, ey;

    sx = (winrot_left / 8) + 1;
    sy = page_top;
    ex = ((winrot_right + 1) / 8);
    ey = page_bottom;

    // Data entry mode - Left to Right, Top to Bottom
    sendCommand(0x11);
      sendData(0x03);

    // Inform the panel hardware of our chosen memory location
    sendCommand(0x44);  // Memory X start - end
    sendData(sx);
    sendData(ex);
    sendCommand(0x45);  // Memory Y start - end
    sendData(sy);
    sendData(0);                                        // Bit 8 - not required, max y is 250
    sendData(ey);
    sendData(0);                                        // Bit 8 - not required, max y is 250
    sendCommand(0x4E);  // Memory cursor X
    sendData(sx);
    sendCommand(0x4F);  // Memory cursor y
    sendData(sy);
    sendData(0);                                        // Bit 8 - not required, max y is 250

    // Now we can send over our image data
    sendCommand(0x24);   // Write "BLACK" memory
    for (uint16_t i = 0; i < pagefile_length; i++) {
        sendData(page_black[i]);
    }

    // Write so-called "RED" memory. With this display, the memory is used during fastmode.
    // Counter-intuitively, need to write both BLACK and RED during normal use.
    // This preserves the image when moving into fastmode.
    if (mode == fastmode.OFF) {
        sendCommand(0x26);   
        for (uint16_t i = 0; i < pagefile_length; i++) {
            sendData(page_black[i]);
        }
    }
    wait();
}

/// Draw the image in Panel's memory to the screen
void DEPG0154BNS800::update(bool override_checks) {
    if (mode == fastmode.OFF || override_checks) {
        // Specify the update operation to run
        sendCommand(0x22);
        if (mode == fastmode.OFF)       sendData(0xF7);
        else if (mode == fastmode.ON)   sendData(0xCC);

        // Or, if finalizing
        else if (first_pass)            sendData(0xCC); // Update, but don't turn ANALOG off yet
        else                            sendData(0xCF); // Turn off ANALOG this time, we're done

        // Execute the update
        sendCommand(0x20);

        // Block while the command runs
        wait();
    }
}

/// Set the panel to an ultra low power state. Only way to exit is to cycle power to VCC.
void DEPG0154BNS800::deepSleep(uint16_t pause) {
    sendCommand(0x10);
    sendData(0x01);
    delay(pause);
}