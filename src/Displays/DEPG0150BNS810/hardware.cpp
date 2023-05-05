#include "DEPG0150BNS810.h"

/// Begin the E-Ink library
void DEPG0150BNS810::begin() {
    // Set the digital pins that supplement the SPI interface
    pinMode(pin_cs, OUTPUT);        // Incase we weren't give the standard pin 10 as SS
    pinMode(pin_dc, OUTPUT);
    pinMode(pin_busy, INPUT);   // NOTE: do not use internal pullups, as we're reading a 3.3v output with our ~5v arduino
    
    // Prepare SPI
    SPI.begin();    

    // Calculate pagefile size
    pagefile_height = constrain(pagefile_height, 1, 50);
    page_bytecount = panel_width * pagefile_height / 8;     // nb: this is a class member and gets reused
    
    // Set height in the library
    _width = WIDTH = panel_width;
    _height = HEIGHT = panel_height;

    // Set an initial configuration for drawing
    setDefaultColor(colors.WHITE);
    setTextColor(colors.BLACK);
    fullscreen();
}

/// Clear the screen in one step
void DEPG0150BNS810::clear() {
    reset();

    int16_t x, y;
    uint8_t blank_byte = (default_color & colors.WHITE) * 255;  // We're filling in bulk here; bits are either all on or all off

    // Calculate memory values for the slice
    // Note, x values are divided by 8 as horizontal lines are rows of 8bit bytes
    const uint8_t start_x = 0;  // Note the offset
    const uint8_t end_x = (panel_width / 8) - 1;        // This is taken from the official heltec driver

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

void DEPG0150BNS810::grabPageMemory() {
    page_black = new uint8_t[page_bytecount];
}

void DEPG0150BNS810::freePageMemory() {
    delete page_black;
}

// Interface directly with display

void DEPG0150BNS810::sendCommand(uint8_t command) {
    SPI.beginTransaction(spi_settings);
    digitalWrite(pin_dc, LOW);  // Data-Command pin LOW, tell PanelHardware this SPI transfer is a command
    digitalWrite(pin_cs, LOW);

    SPI.transfer(command);

    digitalWrite(pin_cs, HIGH);
    SPI.endTransaction();
}

void DEPG0150BNS810::sendData(uint8_t data) {
    SPI.beginTransaction(spi_settings);
    digitalWrite(pin_dc, HIGH); // Data-Command pin HIGH, tell PanelHardware this SPI transfer is data
    digitalWrite(pin_cs, LOW);

    SPI.transfer(data);

    digitalWrite(pin_cs, HIGH);
    SPI.endTransaction();
}

/// Reset the panel
void DEPG0150BNS810::reset() {
    if (mode == fastmode.OFF) {
        sendCommand(0x12); // Software Reset
        wait();
    }
}

/// Wait until the PanelHardware is idle. Important as any commands made while Panel Hardware is busy will be discarded.
void DEPG0150BNS810::wait() {
    while(digitalRead(pin_busy) == HIGH)    {   // Low = idle   
        delay(1);
    }
}


/// Specify the technique used to draw the image onto the screen
void DEPG0150BNS810::setFastmode(FastmodeList::Fastmode mode) {

    // Moving to partial refresh (fastmode)
    if (mode == fastmode.ON && this->mode != fastmode.ON) {
        reset();

        // Technical settings on display, to allow partial refresh (fastmode). Released by Heltec.
        // -----------------------------------------------
        unsigned char count;
        sendCommand(0x32);      // "LUT"
        for(count=0;count<153;count++) 
            sendData(lut_partial[count]); 
        wait();

        sendCommand(0x3F);      // "Option for LUT end"
        sendData(lut_partial[153]);

        sendCommand(0x03);      // "Gate voltage"  
        sendData(lut_partial[154]);

        sendCommand(0x04);      // "Source voltage"   
        sendData(lut_partial[155]); 
        sendData(lut_partial[156]);
        sendData(lut_partial[157]);

        sendCommand(0x2C);      // allegedly: vcom   
        sendData(lut_partial[158]);
                                    
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
void DEPG0150BNS810::writePage() {
    // Calculate rotate x start and stop values (y is already done via paging)
    int16_t sx, sy, ex, ey;

    sx = winrot_left / 8;
    sy = page_top;
    ex = ((winrot_right + 1) / 8) - 1;
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
    sendData(0);        // Bit 8 - not required, max y is 250
    sendData(ey);
    sendData(0);        // Bit 8 - not required, max y is 250
    sendCommand(0x4E);  // Memory cursor X
    sendData(sx);
    sendCommand(0x4F);  // Memory cursor y
    sendData(sy);
    sendData(0);        // Bit 8 - not required, max y is 250

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
void DEPG0150BNS810::update(bool override_checks) {
    if (mode == fastmode.OFF || override_checks) {
        // Specify the update operation to run
        sendCommand(0x22);
        if (mode == fastmode.OFF)   sendData(0xF7);
        else                        sendData(0xCF);

        // Execute the update
        sendCommand(0x20);

        // Block while the command runs
        wait();
    }
}

/// Set the panel to an ultra low power state. Only way to exit is to cycle power to VCC.
void DEPG0150BNS810::deepSleep(uint16_t pause) {
    sendCommand(0x10);
    sendData(0x01);
    delay(pause);
}