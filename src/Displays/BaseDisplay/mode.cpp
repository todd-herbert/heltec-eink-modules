/* 
    File: mode.cpp

        - Move between full and partial refresh modes
*/

#include "base.h"

// Slow, detailed updates
void BaseDisplay::fastmodeOff() {
    fastmode_state = Fastmode::OFF;
    reset();
    configFull();
    wait();
}

// Fast, low quality updates.
// Use sparingly.
void BaseDisplay::fastmodeOn() {
    if(fastmode_state == NOT_SET)
        clear(false);     // Initialize display memory, if needed

    fastmode_state = Fastmode::ON;
    reset();
    configPartial();
    wait();
}

// Fastest, low quality updates. Unstable.
// Use with caution.
void BaseDisplay::fastmodeTurbo() {
    if(fastmode_state == NOT_SET)
        clear(false);    // Initialize dispaly memory, if needed

    fastmode_state = Fastmode::TURBO;
    reset();
    configPartial();
    wait();
}

