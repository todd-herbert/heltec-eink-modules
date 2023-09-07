#include "DEPG0290BNS800.h"

// Required definition, when using PROGMEM inside a class
PROGMEM constexpr uint8_t DEPG0290BNS800::lut_partial[];

void DEPG0290BNS800::configPartial() {

    // Load the fastmode lut
    sendCommand(0x32);
    for(uint8_t i=0;i < sizeof(lut_partial); i++) 
        sendData(pgm_read_byte_near(lut_partial+i));

    sendCommand(0x37);      // "Write Register for Display Option"
    sendData(0x00);         // Ping-Pong mode. Image writes to black ram,
    sendData(0x00);         // display updates, then image is copied to red ram.
    sendData(0x00);         // On next image, red ram is used as a mask,
    sendData(0x00);         // To determine which parts of new black ram
    sendData(0x00);         // should not be set to white...
    sendData(0x40);         // I think..
    sendData(0x00);  
    sendData(0x00);   
    sendData(0x00);  
    sendData(0x00);
}