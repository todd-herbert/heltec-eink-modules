#include "DEPG0150BNS810.h"


//If it's a window calculation, save the dimensions
bool DEPG0150BNS810::calculating(RegionList::Region update_region, uint8_t left, uint8_t top, uint8_t width, uint8_t height) {

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
bool DEPG0150BNS810::calculating(RegionList::Region update_region) {
	//Pass the processing over to the mode-specific calculating method

	//NOTE: this loop runs BEFORE every new page.
	//This means that it is actually also processing all the data generated in the last loop

	//Some of this looks weird, but it's that everything is being evaluated at the start of the next loop
	//No real reason for this over a do while, just personal preference

	//If no window specified, run as fullscreen
	if(update_region == region.FULLSCREEN) {
		return calculating(RegionList::WINDOWED, 0, 0, rotation%2?drawing_height:drawing_width, rotation%2?drawing_width:drawing_height);
	}

	//Beginning of first loop
	//===============
	if (page_cursor == 0) {

		//Limit window to panel 
		if (window_left < 0) 					window_left = 0;
		if (window_top < 0)						window_top = 0;
		if (rotation % 2) {	//Landscape
			if (window_right > drawing_height)		window_right = drawing_height;
			if (window_bottom > drawing_width)		window_bottom = drawing_width;
		}
		else {	//Portrait
			if (window_right > drawing_width)		window_right = drawing_width;
			if (window_bottom > drawing_height)		window_bottom = drawing_height;
		}

		//Calculate rotated window locations
		uint16_t target_byte;
		switch (rotation) {
			case 0:
				winrot_left = window_left;
				winrot_left = winrot_left - (winrot_left % 8);	//Expand box on left to fit contents

				winrot_right = winrot_left;
				while(winrot_right < window_right) winrot_right += 8;	//Iterate until box includes the byte where our far-left bit lives

				winrot_top = window_top;
				winrot_bottom = window_bottom + 1;
				break;

			case 1:
				winrot_left = drawing_width - window_bottom - 1;
				winrot_left = winrot_left - (winrot_left % 8);	//Expand box on left to fit contents

				winrot_right = winrot_left;
				while(winrot_right < drawing_width - window_top) winrot_right += 8;	//Iterate until box includes the byte where our far-left bit lives

				winrot_top = window_left;
				winrot_bottom = window_right + 1;
				break;

			case 2:	
				winrot_right = drawing_width - window_left;
				winrot_right = winrot_right - (winrot_right % 8);
				while(winrot_right < drawing_width - window_left) winrot_right += 8;	//Iterate until box includes the byte for the far-right

				winrot_left = winrot_right;
				target_byte = (drawing_width - window_right - 1) - ((drawing_width - window_right - 1) % 8);
				while(winrot_left > target_byte) winrot_left -= 8;	//Iterate until box includes the byte where our far-left bit lives

				winrot_bottom = drawing_height - window_top;
				winrot_top = drawing_height - window_bottom - 1;

				break;

			
			case 3:
				winrot_left = window_top;
				winrot_left = winrot_left - (winrot_left % 8);	//Expand box on left to fit contents

				winrot_right = winrot_left;
				while(winrot_right < window_bottom) winrot_right += 8;	//Iterate until box includes the byte where our far-left bit lives

				winrot_top = (drawing_height - window_right) - 1;
				winrot_bottom = (drawing_height - window_left);
				break;
		}

		grabPageMemory();		//This will grab slightly too much memory, but not a priority right now. TODO: fix eventually
		clearPage(default_color);
		wake();					//Get the panel ready to receive the spi data

		page_top = winrot_top;	//We're now translating the window in drawPixel()
		page_bottom = winrot_top + page_profile.height;
		pagefile_length = (page_bottom - page_top) * ((winrot_right - winrot_left) / 8);
	}

	//End of each loop
	//===============
	else {
		//Check if the last page contained any part of the window
		if (!(winrot_bottom < page_top || winrot_top > page_bottom))
			writePage();	//Send off the old page

		//Calculate memory locations for the new page
		page_top += page_profile.height;
		page_bottom = min(page_top + page_profile.height, winrot_bottom);
		pagefile_length = (page_bottom - page_top) * ((winrot_right - winrot_left) / 8);
		clearPage(default_color);
	}

	//Check whether loop should continue
	//=============
	if (page_top > winrot_bottom) {
		page_cursor = 0; //Reset for next time
		//update();		//We will make the user call the update manually
		freePageMemory();
		return false;	//We're done
	}
	else {
		page_cursor++;
		return true;	//Keep looping
	}
}

///Clear the data arrays in between pages
void DEPG0150BNS810::clearPage(uint16_t bgcolor) {
		for (uint16_t i = 0; i < page_bytecount; i++) {
			uint8_t black_byte = (bgcolor & colors.WHITE) * 255;	//We're filling in bulk here; bits are either all on or all off
			page_black[i] = black_byte;
		}
}