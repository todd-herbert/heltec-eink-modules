#include "DEPG0154BNS800.h"

// Required definition, when using PROGMEM inside a class
PROGMEM constexpr uint8_t DEPG0154BNS800::lut_partial[];

void DEPG0154BNS800::configPartial() {
    // Load the fastmode LUT
    sendCommand(0x32);
    for(uint8_t i=0;i < sizeof(lut_partial); i++) 
        sendData(pgm_read_byte_near(lut_partial+i));

    sendCommand(0x3C);      // Set border (No more fuzzy edge)
    sendData(0x80);         // Somehow I ignored this in the Heltec example for years.. why?

    sendCommand(0x37);      // "Write Register for Display Option"
    sendData(0x00);         // Ping-Pong mode. Image writes to black ram,
    sendData(0x00);         // display updates, then image is copied to red ram.
    sendData(0x00);         // On next image, red ram is used as a mask,
    sendData(0x00);         // To determine which parts of new black ram
    sendData(0x00);         // should not be set to white...
    sendData(0x40);         // I think..
    sendData(0x00);  
    sendData(0x00);         // 2024-1-17: Wait... Does Ping-Pong mean "differential update"?
    sendData(0x00);  
    sendData(0x00);
}