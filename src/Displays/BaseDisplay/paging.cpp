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
        if (fastmode_state == NOT_SET)
            fastmodeOff();

        // Limit window to panel 
        if (window_left < 0)                    window_left = 0;
        if (window_top < 0)                     window_top = 0;
        if (rotation % 2) { // Landscape
            if (window_right >= drawing_height - 1)     window_right = drawing_height - 1;
            if (window_bottom >= drawing_width - 1)     window_bottom = drawing_width - 1;
        }
        else {  // Portrait
            if (window_right >= drawing_width - 1)      window_right = drawing_width - 1;
            if (window_bottom >= drawing_height - 1)    window_bottom = drawing_height - 1;
        }

        grabPageMemory();
        clearPage(default_color);

        // Specify display region handled this iteration
        page_top = winrot_top;
        page_bottom = min((winrot_top + pagefile_height) - 1, winrot_bottom);
        pagefile_length = (page_bottom - page_top + 1) * ((winrot_right - winrot_left + 1) / 8);
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
        clearPage(default_color);
    }

    // Check whether loop should continue
    // ----------------------------------
    if (page_top > winrot_bottom) {
        page_cursor = 0; // Reset for next time
        freePageMemory();

        // Fastmode OFF or TURBO, single pass
        if (fastmode_state == OFF || fastmode_state == TURBO) {
            activate();
            return false;
        }

        // Fastmode ON: double pass
        else {
            // End of first pass
            if (fastmode_secondpass == false) {
                activate();            
                fastmode_secondpass = true;
                return true;                    // Re-calculate the whole display again
            }
            // End of second pass
            else { 
                activate();            
                fastmode_secondpass = false;    // Reset state for next time
                return false;
            }
        }
    }
    else {
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