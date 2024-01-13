#include "DEPG0213BNS800.h"

void DEPG0213BNS800::calculateMemoryArea( int16_t &sx, int16_t &sy, int16_t &ex, int16_t &ey ) {
    sx = (winrot_left / 8) + 1;     // Get the quirky offsets in the right place
    sy = page_top;
    ex = ((winrot_right) / 8) + 1;
    ey = page_bottom;
}

void DEPG0213BNS800::activate() {
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

#ifdef WIRELESS_PAPER
    void DEPG0213BNS800::sleep() {
        sendCommand(0x10);
        sendData(0x1);
    }

    void DEPG0213BNS800::wake() {
        // On "Wireless Paper" platforms: ensure peripheral power is on, then briefly pull the display's reset pin to ground
        Platform::VExtOn();

        // If display controller was put into "deep sleep"
        Platform::toggleResetPin();

        // Re-load settings for full-refresh
        fastmodeOff();

        // Mark display as potentially out of sync with memory
        just_restarted = true;

        // Re-initialize display memory
        #if PRESERVE_IMAGE                          // Always true for this display - currently..
            if (pagefile_height == panel_height)
                writePage();
            else        
                clear(false);   // If user has (for some reason) re-enabled paging on a fancy mcu
        #else
            // No record of old image, just fill blank
            clear(false);
        #endif
    }
#endif