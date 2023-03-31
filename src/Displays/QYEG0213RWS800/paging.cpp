#include "QYEG0213RWS800.h"

//If it's a window calculation, save the dimensions
bool QYEG0213RWS800::calculating(RegionList::Region update_region, uint8_t left, uint8_t top, uint8_t width, uint8_t height) {
	if (page_cursor == 0) {			//If first execution of a a calcuate block

		this->update_region = update_region;	//This member will determine calculating_Windowed vs _Fullscreen
		this->window_left = left;
		this->window_top = top;
		this->window_right = left + width - 1;
		this->window_bottom = top + height - 1;
	}

	//Pass through to next overload
	return calculating(update_region);
}


///Used with a WHILE loop, to break the graphics into small parts, and draw them one at a time
bool QYEG0213RWS800::calculating(RegionList::Region update_region) {
	//NOTE: this loop runs BEFORE every new page.
	//This means that it is actually also processing all the data generated in the last loop

	if(update_region == region.FULLSCREEN)
		return calculating_Fullscreen();
	else //windowed
		return calculating_Windowed();

	//See you soon..
}

