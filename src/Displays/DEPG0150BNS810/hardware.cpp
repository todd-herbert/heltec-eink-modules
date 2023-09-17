#include "DEPG0150BNS810.h"

void DEPG0150BNS810::calculateMemoryArea( int16_t &sx, int16_t &sy, int16_t &ex, int16_t &ey ) {
    sx = winrot_left / 8;
    sy = page_top;
    ex = ((winrot_right + 1) / 8) - 1;
    ey = page_bottom;
}

void DEPG0150BNS810::activate() {
    // Specify the update operation to run
    sendCommand(0x22);

    if ( fastmode_state == OFF )    
        sendData(0xF7);
    else
        sendData(0xCF);

    // Execute the update
    sendCommand(0x20);

    // Block while the command runs
    wait();
}