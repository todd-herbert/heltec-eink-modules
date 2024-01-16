#include "DEPG0213BNS800.h"

// Required definition, when using PROGMEM inside a class
PROGMEM constexpr uint8_t DEPG0213BNS800::lut_partial[];

void DEPG0213BNS800::configPartial() {

    sendCommand(0x74); // "Analog Block Control"
    sendData(0x54);
    sendCommand(0x7E); // "Digital Block Control"
    sendData(0x3B);


    sendCommand(0x01); // "Driver output control" 
    sendData(0x27);
    sendData(0x01);
    sendData(0x00);

    sendCommand(0x3C);  // Border
    sendData(0x05);

    sendCommand(0x18);  // Temperature sensor
    sendData(0x80);

    wait();

    // Load the fastmode lut
    sendCommand(0x32);
    for(uint8_t i=0;i < sizeof(lut_partial); i++) 
        sendData(pgm_read_byte_near(lut_partial+i));

    sendCommand(0x37);      // "Write Register for Display Option"
    sendData(0x00);         // Ping-Pong mode. Image writes to black ram,
    sendData(0x00);         // display updates, then image is copied to red ram.
    sendData(0x00);         // On next image, red ram is used as a mask,
    sendData(0x00);         // To determine which parts of new black ram
    sendData(0x00);
    sendData(0x40);         // should not be set to white... 
    sendData(0x00);         // I think..
    sendData(0x00);
    sendData(0x00);
    sendData(0x00);
}

void DEPG0213BNS800::configFull() {

    // Technical settings. Released by Heltec.
    // -------------------------------------------------------

    sendCommand(0x74); // "Analog Block Control"
    sendData(0x54);
    sendCommand(0x7E); // "Digital Block Control"
    sendData(0x3B);

    sendCommand(0x01); // "Driver output control" 
    sendData(0xF9);
    sendData(0x00);
    sendData(0x00);

    sendCommand(0x3C); // "Border Waveform"
    sendData(0x01); 

    sendCommand(0x18);    // "Use internal temperature sensor"
    sendData(0x80);

    wait(); 
}

