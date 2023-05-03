#include "QYEG0213RWS800.h"

void QYEG0213RWS800::fullscreen() {
    uint8_t left = 0;
    uint8_t top = 0;
    uint8_t width = rotation%2?drawing_height:drawing_width;
    uint8_t height = rotation%2?drawing_width:drawing_height;
    setWindow(left, top, width, height);
}


/// Draw to only a portion of the display
void QYEG0213RWS800::setWindow(uint8_t left, uint8_t top, uint8_t width, uint8_t height) {
    uint8_t right = left + (width - 1);
    uint8_t bottom = top + (height - 1);
    this->window_left = left;
    this->window_top = top;
    this->window_right = right;
    this->window_bottom = bottom;

    // Calculate rotated window locations
    // These "winrot" values are the *absolute* locations of the window borders, i.e. a rectangle as described when rotation = 0
    switch (rotation) {
        case 0:
            winrot_left = window_left;
            winrot_left = winrot_left - (winrot_left % 8);	// Expand box on left to fit contents

            winrot_right = winrot_left + 7;
            while(winrot_right < window_right) winrot_right += 8;	// Iterate until box includes the byte where our far-left bit lives

            winrot_top = window_top;
            winrot_bottom = window_bottom;
            break;

        case 1:
            winrot_left = (drawing_width - 1) - window_bottom;
            winrot_left = winrot_left - (winrot_left % 8);	// Expand box on left to fit contents

            winrot_right = winrot_left + 7;
            while(winrot_right < (drawing_width - 1) - window_top) winrot_right += 8;	// Iterate until box includes the byte where our far-left bit lives

            winrot_top = window_left;
            winrot_bottom = window_right;
            break;

        case 2:	
            winrot_left = (drawing_width - 1) - window_right;
            winrot_left = winrot_left - (winrot_left % 8);	// Expand box on left to fit contents

            winrot_right = winrot_left + 7;
            while(winrot_right < (drawing_width - 1) - window_left) winrot_right += 8;	// Iterate until box includes the byte where our far-left bit lives

            winrot_bottom = (drawing_height - 1) - window_top;
            winrot_top = (drawing_height - 1) - window_bottom;

            break;

        
        case 3:
            winrot_left = window_top;
            winrot_left = winrot_left - (winrot_left % 8);	// Expand box on left to fit contents

            winrot_right = winrot_left + 7;
            while(winrot_right < window_bottom) winrot_right += 8;	// Iterate until box includes the byte where our far-left bit lives

            winrot_top = (drawing_height - 1) - window_right;
            winrot_bottom = (drawing_height - 1) - window_left;
            break;
    }	// -- Finish calculating window rotation
}

/// Used with a WHILE loop, to render the screen image in several small pieces, rather than all at once. Workaround for low-memory devices.
bool QYEG0213RWS800::calculating() {

    // NOTE: this loop runs BEFORE every new page.
    // This means that in *this loop*, it is really processing the gfx data generated in the *previous loop*.
    // No real reason for this, rather than a do while; just felt it was a neater UX

    // Beginning of first loop
    // Lay a bunch of ground work, before we get any real image data in
    // ------------------------------------------------------------------
    if (page_cursor == 0) {

        // Limit window to panel 
        if (window_left < 0) 					window_left = 0;
        if (window_top < 0)						window_top = 0;
        if (rotation % 2) {	// Landscape
            if (window_right >= panel_height - 1)		window_right = panel_height - 1;
            if (window_bottom >= panel_width - 1)		window_bottom = panel_width - 1;
        }
        else {	// Portrait
            if (window_right >= panel_width - 1)		window_right = panel_width - 1;
            if (window_bottom >= panel_height - 1)		window_bottom = panel_height - 1;
        }

        grabPageMemory();				// Dynamically grab the page memory. TODO: Compile-time option for static memory?
        clearPage(default_color);
        reset();						// If panel is asleep, Wake to receive SPI image data.

        page_top = winrot_top;											// Minimum (topmost) y-value for this paging operation
        page_bottom = (winrot_top + page_profile.height) - 1;

        // This value is used sending image to the display, to know how much data to read out of the page file
        pagefile_length = (page_bottom - page_top + 1) * ((winrot_right - winrot_left + 1) / 8);
    }

    // End of each loop
    // -----------------
    else {
        // Check if the last page contained any part of the window
        if (!(winrot_bottom < page_top || winrot_top > page_bottom))
            writePage();	// Send off the old page

        // Calculate memory locations for the new page
        page_top += page_profile.height;
        page_bottom = min(page_top + page_profile.height - 1, winrot_bottom);
        pagefile_length = (page_bottom - page_top + 1) * ((winrot_right - winrot_left+1) / 8);
        clearPage(default_color);
    }

    // Check whether loop should continue
    // ----------------------------------
    if (page_top > winrot_bottom) {
        page_cursor = 0; // Reset for next time
        freePageMemory();
        return false;
    }
    else {
        page_cursor++;
        return true;	// Keep looping
    }
}

