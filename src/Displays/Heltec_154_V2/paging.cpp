#include "Heltec_154_V2.h"


//If it's a window calculation, save the dimensions
bool Heltec_154_V2::calculating(RegionList::Region update_region, uint8_t left, uint8_t top, uint8_t width, uint8_t height) {

	if (page_cursor == 0) {			//If first execution of a a calcuate block
		uint8_t right = left + width;	//Retrofitting for consistency
		uint8_t bottom = top + height;
		this->window_left = left;
		this->window_top = top;
		this->window_right = right;
		this->window_bottom = bottom;

		// //TODO: optimise so this code only runs once per calculation
		// //Round generously-er
		// if(left % 8 != 0) this->window_left = left - (left % 8);
		// if(right % 8 != 0) this->window_right = right - (right % 8) + 8;
		// if(top % 8 != 0) this->window_top = top - (top % 8);
		// if(bottom % 8 != 0) this->window_bottom = bottom - (bottom % 8) + 8;

		// //Correct the window boundaries and store
		// if(this->window_right >= panel_width) this->window_right -= 8;
		// if(this->window_bottom >= panel_height) this->window_bottom -= 8;
	}

	//Pass through the the regular method
	return calculating(update_region);
}

///Used with a WHILE loop, to break the graphics into small parts, and draw them one at a time
bool Heltec_154_V2::calculating(RegionList::Region update_region) {
	//Pass the processing over to the mode-specific calculating method

	//NOTE: this loop runs BEFORE every new page.
	//This means that it is actually also processing all the data generated in the last loop

	//Some of this looks weird, but it's that everything is being evaluated at the start of the next loop
	//No real reason for this over a do while, just personal preference



	//Store further calculation info
	if (page_cursor == 0)
		this->update_region = update_region;

	//Hand processing over to mode-specific methods
	if (update_region == region.FULLSCREEN)
		return calculating_Fullscreen();
	else	//Windowed
		return calculating_Windowed();
}

///Clear the data arrays in between pages
void Heltec_154_V2::clearPage(uint16_t bgcolor) {
		for (uint16_t i = 0; i < page_bytecount; i++) {
			uint8_t black_byte = (bgcolor & colors.WHITE) * 255;	//We're filling in bulk here; bits are either all on or all off
			page_black[i] = black_byte;
		}
}