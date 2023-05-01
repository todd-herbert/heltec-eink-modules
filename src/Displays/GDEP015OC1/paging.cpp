#include "GDEP015OC1.h"

/// Draw using the whole screen area
/// Call before calculating()
void GDEP015OC1::fullscreen() {
		uint8_t left = 0;
		uint8_t top = 0;
		uint8_t width = rotation%2?drawing_height:drawing_width;
		uint8_t height = rotation%2?drawing_width:drawing_height;
		setWindow(left, top, width, height);
}

/// Draw on only part of the screen, leaving the rest unchanged
/// Call before calculating
void GDEP015OC1::setWindow(uint8_t left, uint8_t top, uint8_t width, uint8_t height) {
	uint8_t right = left + (width - 1);
	uint8_t bottom = top + (height - 1);
	this->window_left = left;
	this->window_top = top;
	this->window_right = right;
	this->window_bottom = bottom;

	// Calculate rotated window locations
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
			winrot_bottom = window_right + 1;
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

/// Used with a WHILE loop, to break the graphics into small parts, and draw them one at a time
bool GDEP015OC1::calculating() {
	// Pass the processing over to the mode-specific calculating method

	// NOTE: this loop runs BEFORE every new page.
	// This means that it is actually also processing all the data generated in the last loop

	// Some of this looks weird, but it's that everything is being evaluated at the start of the next loop
	// No real reason for this over a do while, just personal preference

	// Beginning of first loop
	// -----------------------
	if (page_cursor == 0) {

		// Limit window to panel 
		if (window_left < 0) 					window_left = 0;
		if (window_top < 0)						window_top = 0;
		if (rotation % 2) {	// Landscape
			if (window_right >= drawing_height - 1)		window_right = drawing_height - 1;
			if (window_bottom >= drawing_width - 1)		window_bottom = drawing_width - 1;
		}
		else {	// Portrait
			if (window_right >= drawing_width - 1)		window_right = drawing_width - 1;
			if (window_bottom >= drawing_height - 1)	window_bottom = drawing_height - 1;
		}

		grabPageMemory();		// This will grab slightly too much memory, but not a priority right now. TODO: fix eventually
		clearPage(default_color);
		reset();

		page_top = winrot_top;	// We're now translating the window in drawPixel()
		page_bottom = (winrot_top + page_profile.height) - 1;
		pagefile_length = (page_bottom - page_top + 1) * ((winrot_right - winrot_left + 1) / 8);
	}

	// End of each loop
	// ----------------
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

		// Normal Operation: manual update, single pass
		if (mode == fastmode.OFF) {
			return false;
		}

		// Fastmode: auto update, single pass
		else if(mode == fastmode.ON) {
			update(true);
			return false;
		}

		// Fastmode (finalizing): auto update, double pass
		else {	// fastmode.FINALIZE
			update(true);
			if (first_pass) {	// Two passes for this mode
				first_pass = false;
				mode = fastmode.OFF;	// Return to default mode (OFF)
				return true;	// Re-calculate the whole display again
			}
			else {
				first_pass = true;		// Reset for next time
				return false;
			}
		}
	}
	else {
		page_cursor++;
		return true;	// Keep looping
	}
}

/// Clear the data arrays in between pages
void GDEP015OC1::clearPage(uint16_t bgcolor) {
		for (uint16_t i = 0; i < page_bytecount; i++) {
			uint8_t black_byte = (bgcolor & colors.WHITE) * 255;	// We're filling in bulk here; bits are either all on or all off
			page_black[i] = black_byte;
		}
}