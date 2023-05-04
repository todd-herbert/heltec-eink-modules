#include "HTE029A1.h"

/// Begin the E-Ink library
void HTE029A1::begin(const PageProfile profile) {
    // Store the page profile
    this->page_profile = profile;

    // Set the digital pins that supplement the SPI interface
    pinMode(pin_cs, OUTPUT);        // Incase we weren't give the standard pin 10 as SS
    pinMode(pin_dc, OUTPUT);
    pinMode(pin_busy, INPUT);   // NOTE: do not use internal pullups, as we're reading a 3.3v output with our ~5v arduino
    
    // Prepare SPI
    SPI.begin();    

    page_bytecount = panel_width * page_profile.height / 8;     // nb: this is a class member and gets reused
    
    // Set height in the library
    _width = WIDTH = panel_width;
    _height = HEIGHT = panel_height;

    // Set an initial configuration for drawing
    setDefaultColor(colors.WHITE);
    setTextColor(colors.BLACK);
    fullscreen();
}

/// Clear the screen in one step
void HTE029A1::clear() {
    reset();

    int16_t x, y;
    uint8_t blank_byte = (default_color & colors.WHITE) * 255;  // We're filling in bulk here; bits are either all on or all off

    // Calculate memory values for the slice
    // Note, x values are divided by 8 as horizontal lines are rows of 8bit bytes
    const uint8_t end_x = (panel_width / 8) - 1;        // This is taken from the official heltec driver

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
    sendData(0);                                        // Bit 8 - not required, max y is 250
    sendData(end_y1);
    sendData(end_y2);                                       // Bit 8 - not required, max y is 250
    sendCommand(0x4E);  // Memory cursor X
    sendData(0);
    sendCommand(0x4F);  // Memory cursor y
    sendData(0);
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
    
    // This display is particularly "sticky", so we run through the refresh procedure twice
    // Clears off the problematic ghosting
    sendCommand(0x22);
    sendData(0xC7);
    sendCommand(0x20);
    wait();
    sendCommand(0x22);
    sendData(0xC7);
    sendCommand(0x20);
    wait();
}


// Allocate and Deallocate dynamic memory for graphics operations

void HTE029A1::grabPageMemory() {
    page_black = new uint8_t[page_bytecount];
}

void HTE029A1::freePageMemory() {
    delete page_black;
}

// Interface directly with display

void HTE029A1::sendCommand(uint8_t command) {
    SPI.beginTransaction(spi_settings);
    digitalWrite(pin_dc, LOW);  // Data-Command pin LOW, tell PanelHardware this SPI transfer is a command
    digitalWrite(pin_cs, LOW);

    SPI.transfer(command);

    digitalWrite(pin_cs, HIGH);
    SPI.endTransaction();
}

void HTE029A1::sendData(uint8_t data) {
    SPI.beginTransaction(spi_settings);
    digitalWrite(pin_dc, HIGH); // Data-Command pin HIGH, tell PanelHardware this SPI transfer is data
    digitalWrite(pin_cs, LOW);

    SPI.transfer(data);

    digitalWrite(pin_cs, HIGH);
    SPI.endTransaction();
}

/// Reset the panel
void HTE029A1::reset() {
    if(this->mode == fastmode.OFF) {
        sendCommand(0x12);
        wait();

        // "Driver Output Control"
        sendCommand(0x01);  
        sendData((uint8_t)((panel_height - 1) & 0xFF)); // (Height - 1) bit 0
        sendData(((panel_height - 1) >> 8) & 0xFF); // (Height - 1) bit 1
        sendData(0x00);

        // "Booster Soft Start Control"
        sendCommand(0x0C);
        sendData(0xD7);
        sendData(0xD6);
        sendData(0x9D);

        // "Write VCOM Register"
        sendCommand(0x2C);
        sendData(0xA8);

        // "Set dummy line period"
        sendCommand(0x3A);
        sendData(0x1A); // "4 dummy lines per gate"

        // "Set gate time"
        sendCommand(0x3B);
        sendData(0x08); // "2us per line"

        // Load the Look Up Table (LUT) for full update
        sendCommand(0x32);
        for(uint8_t i=0;i < sizeof(lut_full); i++) 
            sendData(lut_full[i]); 

        wait();
    }

}

/// Wait until the PanelHardware is idle. Important as any commands made while Panel Hardware is busy will be discarded.
void HTE029A1::wait() {
    while(digitalRead(pin_busy) == HIGH)    {   // Low = idle   
        delay(1);
    }
}


/// Specify the technique used to draw the image onto the screen
void HTE029A1::setFastmode(FastmodeList::Fastmode mode) {
        // If moving out of fastmode
        if(mode == fastmode.OFF) {
            reset();
            this->mode = fastmode.OFF;
            return;
        }

        // If we're coming from .OFF, do a proper soft reset to unload the old settings
        if (this->mode == fastmode.OFF) {
            sendCommand(0x12);
            wait();
        }

        // Store the mode
        this->mode = mode;

        // Now peform a modifed reset()
        // -----------------------------

        // "Driver Output Control"
        sendCommand(0x01);  
        sendData((uint8_t)((panel_height - 1) & 0xFF)); // (Height - 1) bit 0
        sendData(((panel_height - 1) >> 8) & 0xFF); // (Height - 1) bit 1
        sendData(0x00); // Gate scanning settings

        // "Booster Soft Start Control"
        sendCommand(0x0C);
        sendData(0xD7);
        sendData(0xD6);
        sendData(0x9D);

        // "Write VCOM Register"
        sendCommand(0x2C);
        sendData(0xA8);

        // "Set dummy line period"
        sendCommand(0x3A);
        sendData(0x1A); // "4 dummy lines per gate"

        // "Set gate time"
        sendCommand(0x3B);
        sendData(0x08); // "2us per line"

        // Load the LUT for partial update
        sendCommand(0x32);
        for(uint8_t i=0;i < sizeof(lut_partial); i++) 
            sendData(lut_partial[i]);

        wait();

        // "Write register for display option"
        sendCommand(0x37);
        sendData(0x00);
        sendData(0x00);  
        sendData(0x00);  
        sendData(0x00); 
        sendData(0x00);     
        sendData(0x40); // RAM "Ping Pong" enabled
        sendData(0x00);  
        sendData(0x00);   
        sendData(0x00);  
        sendData(0x00);


}

/// Write one page to the panel memory
void HTE029A1::writePage() {
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
    if (mode == fastmode.OFF) {
        sendCommand(0x26);   
        for (uint16_t i = 0; i < pagefile_length; i++) {
            sendData(page_black[i]);
        }
    }

    wait();
}

/// Draw the image in Panel's memory to the screen
void HTE029A1::update(bool override_checks) {
    if (mode == fastmode.OFF || override_checks) {

        // Specify the update operation to run
        sendCommand(0x22);
        if (mode == fastmode.OFF)   sendData(0xC7);
        else                        sendData(0xC7);

        // Execute the update
        sendCommand(0x20);

        // Block while the command runs
        wait();
    }
}

/// Set the panel to an ultra low power state. Only way to exit is to cycle power to VCC.
void HTE029A1::deepSleep(uint16_t pause) {
    sendCommand(0x10);
    sendData(0x01);
    delay(pause);
}