#include "DEPG0290BNS75A.h"

// Have to initialize because of GFX class
DEPG0290BNS75A::DEPG0290BNS75A( uint8_t pin_dc, uint8_t pin_cs, uint8_t pin_busy, uint8_t page_height) : GFX(panel_width, panel_height) {
    // Store the config
    this->pin_dc = pin_dc;
    this->pin_cs = pin_cs;
    this->pin_busy = pin_busy;
    this->pagefile_height = page_height;

    // Instantiate nested classes and pass references
    this->bounds = Bounds(  &winrot_top, 
                            &winrot_right, 
                            &winrot_bottom, 
                            &winrot_left, 
                            &rotation,
                            &imgflip    );

    // Set the digital pins that supplement the SPI interface
    pinMode(pin_cs, OUTPUT);        // Incase we weren't give the standard pin 10 as SS
    pinMode(pin_dc, OUTPUT);
    pinMode(pin_busy, INPUT);   // NOTE: do not use internal pullups, as we're reading a 3.3v output with our ~5v arduino
    
    // Prepare SPI
    digitalWrite(pin_cs, HIGH); // Helpful if using more than one display
    SPI.begin();    

    // Calculate pagefile size
    pagefile_height = constrain(pagefile_height, 1, 50);
    page_bytecount = panel_width * pagefile_height / 8;     // nb: this is a class member and gets reused
    
    // Set an initial configuration for drawing
    setDefaultColor(colors.WHITE);
    setTextColor(colors.BLACK);
    fullscreen();
}

/// Clear the screen in one step
void DEPG0290BNS75A::clear() {
    reset();
    int16_t x, y;
    uint8_t blank_byte = (default_color & colors.WHITE) * 255;  // We're filling in bulk here; bits are either all on or all off

    // Calculate memory values for the slice
    // Note, x values are divided by 8 as horizontal lines are rows of 8bit bytes
    const uint8_t end_x = (panel_width / 8) - 1;

    // y locations are two bytes
    const uint8_t end_y1 = (uint8_t)((panel_height - 1) & 0xFF);
    const uint8_t end_y2 = ((panel_height - 1) >> 8);

    // Data entry mode - Left to Right, Top to Bottom
    sendCommand(0x11);
    sendData(0x03);
    
    // Inform the panel hardware of our chosen memory location
    sendCommand(0x44);  // Memory X start - end
    sendData(0);
    sendData(end_x);
    sendCommand(0x45);  // Memory Y start - end
    sendData(0);
    sendData(0);                                        
    sendData(end_y1);
    sendData(end_y2);                                       
    sendCommand(0x4E);  // Memory cursor X
    sendData(0);
    sendCommand(0x4F);  // Memory cursor y
    sendData(0);
    sendData(0);                                        // Bit 8 - not required, max y is 250

    sendCommand(0x24);   // Fill "BLACK" memory with default_color
    for(y = 0; y < (panel_width / 8) + 1; y++) {    // (+1 overscan)
        for(x = 0; x < panel_height; x++) {
            sendData(blank_byte);
        }
    }

    sendCommand(0x26);   // Fill "RED" memory with default_color
    for(y = 0; y < (panel_width / 8) + 1; y++) {  // (+1 overscan)
        for(x = 0; x < panel_height; x++) {
            sendData(blank_byte);
        }
    }
    
    // Manually update the display
    sendCommand(0x22);
    sendData(0xF7);
    sendCommand(0x20);
    wait();
}


// Allocate and Deallocate dynamic memory for graphics operations

void DEPG0290BNS75A::grabPageMemory() {
    page_black = new uint8_t[page_bytecount];
}

void DEPG0290BNS75A::freePageMemory() {
    delete[] page_black;
}

// Interface directly with display

void DEPG0290BNS75A::sendCommand(uint8_t command) {
    SPI.beginTransaction(spi_settings);
    digitalWrite(pin_dc, LOW);  // Data-Command pin LOW, tell PanelHardware this SPI transfer is a command
    digitalWrite(pin_cs, LOW);

    SPI.transfer(command);

    digitalWrite(pin_cs, HIGH);
    SPI.endTransaction();
}

void DEPG0290BNS75A::sendData(uint8_t data) {
    SPI.beginTransaction(spi_settings);
    digitalWrite(pin_dc, HIGH); // Data-Command pin HIGH, tell PanelHardware this SPI transfer is data
    digitalWrite(pin_cs, LOW);

    SPI.transfer(data);

    digitalWrite(pin_cs, HIGH);
    SPI.endTransaction();
}

/// Reset the panel
void DEPG0290BNS75A::reset() {

    if (mode == fastmode.OFF) { 
        sendCommand(0x12); // Software Reset
        wait();
    }

    // Technical settings. Released by Heltec.
    // -------------------------------------------------------
    sendCommand(0x74); // "Analog Block Control"
    sendData(0x54);

    sendCommand(0x7E); // "Digital Block Control"
    sendData(0x3B);

    sendCommand(0x01); // "Driver Output Control" 
    sendData(0x27);
    sendData(0x01);
    sendData(0x00);

    sendCommand(0x3C); // "Border Waveform"
    sendData(0x01); 

    sendCommand(0x18); // Use the internal temperature sensor
    sendData(0x80);

    // These values stored in OTP for full refresh, but we need to enter them manually incase of partial refresh

    sendCommand(0x2C);  // "VCOM"
    sendData(0x26);

    sendCommand(0x03);  // "Gate Driving Voltage"
    sendData(0x17);

    sendCommand(0x04);  // "Source Driving Voltage"
    sendData(0x41);
    sendData(0x00);
    sendData(0x32);

    sendCommand(0x3C);  // "Border Waveform"
    sendData(0x01);

    // --------------------------------------------------------
    wait();
}

/// Wait until the PanelHardware is idle. Important as any commands made while Panel Hardware is busy will be discarded.
void DEPG0290BNS75A::wait() {
    while(digitalRead(pin_busy) == HIGH)    {   // Low = idle   
        delay(1);
    }
}


/// Specify the technique used to draw the image onto the screen
void DEPG0290BNS75A::setFastmode(FastmodeList::Fastmode mode) {
    // If moving out of fastmode
    if(mode == fastmode.OFF) {
        this->mode = fastmode.OFF;
        reset();
        return;
    }

    // If we're coming from .OFF, do a proper soft reset to unload the old settings
    if (this->mode == fastmode.OFF) {
        sendCommand(0x12);
        wait();
    
        // Load the fastmode lut
        sendCommand(0x32);
        for(uint8_t i=0;i < sizeof(lut_partial); i++) 
            sendData(lut_partial[i]);

        wait();

        sendCommand(0x37);      // "Write Register for Display Option"
        sendData(0x00);         // Ping-Pong mode. Image writes to black ram,
        sendData(0x00);         // display updates, then image is copied to red ram.
        sendData(0x00);         // On next image, red ram is used as a mask,
        sendData(0x00);         // To determine which parts of new black ram
        sendData(0x40);         // should not be set to white... 
        sendData(0x00);         // I think..
        sendData(0x00);   
    }
    
    // Store the mode
    this->mode = mode;
}

/// Write one page to the panel memory
void DEPG0290BNS75A::writePage() {
    // Calculate rotate x start and stop values (y is already done via paging)
    int16_t sx, sy, ex, ey;

    sx = (winrot_left / 8);
    sy = page_top;
    ex = ((winrot_right + 1) / 8) - 1;
    ey = page_bottom;

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

    // Now we can send over our image data
    sendCommand(0x24);   // Write "BLACK" memory
    for (uint16_t i = 0; i < pagefile_length; i++) {
        sendData(page_black[i]);
    }

    // Write so-called "RED" memory. With this display, the memory is used during fastmode.
    // Counter-intuitively, need to write both BLACK and RED during normal use.
    // This preserves the image when moving into fastmode.

    if(mode == fastmode.OFF) {
        sendCommand(0x26);   
        for (uint16_t i = 0; i < pagefile_length; i++) {
            sendData(page_black[i]);
        }
    }

    wait();
}

/// Draw the image in Panel's memory to the screen
void DEPG0290BNS75A::update(bool override_checks) {
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
void DEPG0290BNS75A::deepSleep(uint16_t pause) {
    sendCommand(0x10);
    sendData(0x01);
    delay(pause);
}