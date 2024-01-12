/* 
    File: mode.cpp

        - Move between full and partial refresh modes
*/

#include "base.h"

// Slow, detailed updates
void BaseDisplay::fastmodeOff() {

    // Init hardware, if not yet done
    begin();

    fastmode_state = Fastmode::OFF;
    reset();
    configFull();
    wait();
}

// Fast, low quality updates.
// Use sparingly.
void BaseDisplay::fastmodeOn() {

    // Init hardware, if not yet done
    begin();

    if(fastmode_state == NOT_SET)
        clear(false);     // Initialize display memory, if needed

    // If memory was lost after customPowerOff
    #if !PRESERVE_IMAGE
        if (just_restarted && !display_cleared)
            clear(true);
    #endif

    fastmode_state = Fastmode::ON;
    reset();
    configPartial();
    wait();
}

// Fastest, low quality updates. Unstable.
// Use with caution.
void BaseDisplay::fastmodeTurbo() {

    // Init hardware, if not yet done
    begin();

    if(fastmode_state == NOT_SET)
        clear(false);    // Initialize dispaly memory, if needed

    fastmode_state = Fastmode::TURBO;
    reset();
    configPartial();
    wait();
}

