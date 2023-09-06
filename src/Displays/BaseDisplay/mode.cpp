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
}

// Fast, low quality updates.
// Use sparingly.
void BaseDisplay::fastmodeOn() {
    fastmode_state = Fastmode::ON;
    reset();
    configPartial();
}

// Fastest, low quality updates. Unstable.
// Use with caution.
void BaseDisplay::fastmodeTurbo() {
    fastmode_state = Fastmode::TURBO;
    reset();
    configPartial();
}

