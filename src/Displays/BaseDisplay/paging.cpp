/* 
    File: paging.cpp

        - Paging loop control
*/

#include "base.h"

// Used with a WHILE loop, to break the graphics into small parts, and draw them one at a time
bool BaseDisplay::calculating() {

    // NOTE: this loop runs BEFORE every new page.
    // This means that it is actually processing data generated in the last loop
    // No real reason for this over a do while, just personal preference

    // Beginning of first loop (initial setup)
    // --------------------------------------
    if (page_cursor == 0) {

        // Init display, if needed
        if (fastmode_state == NOT_SET) {
            fastmodeOff();
            clear(false);   // Fill whole memory, incase updating window after reset (static)
        }

        // Grab memory, if it doesn't persist between updates
        #if !PRESERVE_IMAGE
            grabPageMemory();
        #endif

        // Specify display region handled, either in paging, or outside loop
        page_top = winrot_top;
        page_bottom = min((winrot_top + pagefile_height) - 1, winrot_bottom);
        pagefile_length = (page_bottom - page_top + 1) * ((winrot_right - winrot_left + 1) / 8);

        clearPage(default_color);

        // Track state of display memory (re:externalPowerOn)
        display_cleared = false;
        just_restarted = false;
    }

    // End of each loop (start of next)
    // --------------------------------
    else {
        // Check if the last page contained any part of the window
        if (!(winrot_bottom < page_top || winrot_top > page_bottom))
            writePage();    // Send off the old page

        // Calculate memory locations for the new page
        page_top += pagefile_height;
        page_bottom = min(page_top + pagefile_height - 1, winrot_bottom);
        pagefile_length = (page_bottom - page_top + 1) * ((winrot_right - winrot_left+1) / 8);
    }

    // Check whether loop should continue
    // ----------------------------------
    if (page_top > winrot_bottom) {
        page_cursor = 0; // Reset for next time

        // Release the memory, if not preserved
        #if !PRESERVE_IMAGE
            freePageMemory();
        #else
            // Reset now, incase big MCU wants to draw outside loop
            page_top = winrot_top;
            page_bottom = min((winrot_top + pagefile_height) - 1, winrot_bottom);
            pagefile_length = (page_bottom - page_top + 1) * ((winrot_right - winrot_left + 1) / 8);
        #endif

        // Fastmode OFF or TURBO, single pass
        if (fastmode_state == OFF || fastmode_state == TURBO) {
            if(!writing_canvas)
                activate(); 
                
            return false;
        }

        // Fastmode ON: double pass
        else {
            // End of first pass
            if (fastmode_secondpass == false) {
                if (!writing_canvas)
                    activate(); 
         
                fastmode_secondpass = true;
                return true;                    // Re-calculate the whole display again
            }
            // End of second pass
            else {
                if (!writing_canvas)
                    activate(); 
      
                fastmode_secondpass = false;    // Reset state for next time
                return false;
            }
        }
    }
    else {
        clearPage(default_color);
        page_cursor++;
        return true;    // Keep looping
    }
}

// Clear the data arrays in between pages
void BaseDisplay::clearPage(uint16_t bgcolor) {
        uint8_t black_byte = (bgcolor & WHITE) * 255;    // We're filling in bulk here; bits are either all on or all off
        for (uint16_t i = 0; i < page_bytecount; i++)
            page_black[i] = black_byte;

        // Repeat for red
        if (supportsColor(RED)) {
            uint8_t red_byte = ((bgcolor & RED) >> 1) * 255;
            for (uint16_t i = 0; i < page_bytecount; i++)
                page_red[i] = red_byte;
        }
}