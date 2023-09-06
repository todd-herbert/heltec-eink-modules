#include "DEPG0154BNS800.h"

void DEPG0154BNS800::specifyMemoryArea( int16_t &sx, int16_t &sy, int16_t &ex, int16_t &ey ) {
    sx = (winrot_left / 8) + 1; //Notice the offset
    sy = page_top;
    ex = ((winrot_right + 1) / 8);
    ey = page_bottom;
}

void DEPG0154BNS800::activate() {
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