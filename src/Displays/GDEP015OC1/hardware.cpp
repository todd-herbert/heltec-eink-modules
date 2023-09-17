#include "GDEP015OC1.h"

void GDEP015OC1::calculateMemoryArea( int16_t &sx, int16_t &sy, int16_t &ex, int16_t &ey ) {
    sx = (winrot_left / 8);
    sy = page_top;
    ex = ((winrot_right + 1) / 8) - 1;
    ey = page_bottom;
}

void GDEP015OC1::activate() {
    // Specify the update operation to run
    sendCommand(0x22);
    sendData(0xC7);

    // Execute the update
    sendCommand(0x20);

    // Block while the command runs
    wait();
}