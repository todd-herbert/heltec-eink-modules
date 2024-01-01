/* 
    File: mode.cpp

        - Move between full and partial refresh modes
*/

#include "base.h"

// Slow, detailed updates
void BaseDisplay::fastmodeOff() {

    // Call begin() automatically. 
    // TODO: require manual call in next major version, breaking change.
    begin();

    fastmode_state = Fastmode::OFF;
    softReset();
    configFull();
    wait();
}

// Fast, low quality updates.
// Use sparingly.
void BaseDisplay::fastmodeOn() {

    // Call begin() automatically. 
    // TODO: require manual call in next major version, breaking change.
    begin();

    if(fastmode_state == NOT_SET)
        clear(false);     // Initialize display memory, if needed

    // If memory was lost after externalPowerOff
    #if !PRESERVE_IMAGE
        if (just_restarted && !display_cleared)
            clear(true);
    #endif

    fastmode_state = Fastmode::ON;
    softReset();
    configPartial();
    wait();
}

// Fastest, low quality updates. Unstable.
// Use with caution.
void BaseDisplay::fastmodeTurbo() {

    // Call begin() automatically. 
    // TODO: require manual call in next major version, breaking change.
    begin();

    if(fastmode_state == NOT_SET)
        clear(false);    // Initialize dispaly memory, if needed

    fastmode_state = Fastmode::TURBO;
    softReset();
    configPartial();
    wait();
}

