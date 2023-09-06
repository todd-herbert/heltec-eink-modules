#include "DEPG0150BNS810.h"

// Required definition, when using PROGMEM inside a class
PROGMEM constexpr uint8_t DEPG0150BNS810::lut_partial[];

void DEPG0150BNS810::configPartial() {
    // Settings from official Heltec repo

    // Load the fastmode lut
    sendCommand(0x32);
    for(uint8_t i=0;i < sizeof(lut_partial); i++) 
        sendData(pgm_read_byte_near(lut_partial+i));

    sendCommand(0x3F);      // "Option for LUT end"
    sendData(0x02);

    sendCommand(0x03);      // "Gate voltage"  
    sendData(0x17);

    sendCommand(0x04);      // "Source voltage"   
    sendData(0x41); 
    sendData(0xB0);
    sendData(0x32);

    sendCommand(0x2C);      // vcom   
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
}
