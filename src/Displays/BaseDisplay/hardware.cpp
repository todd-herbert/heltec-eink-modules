/* 
    File: hardware.cpp

        - Direct interface with the display
*/

#include "base.h"

// Clear the screen in one step
void BaseDisplay::clear() {
    fastmodeOff();
    while( calculating() ) {    // Less efficient, but smaller
        fillScreen(default_color);
    }
}

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
    SPI.beginTransaction(spi_settings);
    digitalWrite(pin_dc, LOW);  // D/C pin LOW means SPI transfer is a command
    digitalWrite(pin_cs, LOW);

    SPI.transfer(command);

    digitalWrite(pin_cs, HIGH);
    SPI.endTransaction();
}

void BaseDisplay::sendData(uint8_t data) {
    SPI.beginTransaction(spi_settings);
    digitalWrite(pin_dc, HIGH);     // D/C pin HIGH means SPI transfer is data
    digitalWrite(pin_cs, LOW);

    SPI.transfer(data);

    digitalWrite(pin_cs, HIGH);
    SPI.endTransaction();
}

// Soft-reset the display
void BaseDisplay::reset() {
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
    // Calculate rotated x start and stop values (y is already done via paging)
    int16_t sx, sy, ex, ey;
    specifyMemoryArea(sx, sy, ex, ey);  // Virtual, derived class

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

// Enter a power-saving state. Display needs power-cycle to wake.
void BaseDisplay::deepSleep(uint16_t pause) {
    sendCommand(0x10);
    sendData(0x01);
    delay(pause);
}