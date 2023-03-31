#include "DEPG0290BNS800.h"

//If it's a window calculation, save the dimensions
bool DEPG0290BNS800::calculating(RegionList::Region update_region, uint16_t left, uint16_t top, uint16_t width, uint16_t height) {
	if (page_cursor == 0) {			//If first execution of a a calcuate block

		this->update_region = update_region;	//This member will determine calculating_Windowed vs _Fullscreen
		this->window_left = left;
		this->window_top = top;
		this->window_right = left + width - 1;
		this->window_bottom = top + height -1;
	}

	//Pass through to next overload
	return calculating(update_region);	//this is passed as a parameter but also saved. part of the mess around fullscreen.cpp becoming redundant
}


///Used with a WHILE loop, to break the graphics into small parts, and draw them one at a time
bool DEPG0290BNS800::calculating(RegionList::Region update_region) {
	//NOTE: this loop runs BEFORE every new page.
	//This means that it is actually also processing all the data generated in the last loop

	if(update_region == region.FULLSCREEN) {
		//Ugh, TODO: yank off this bandaid. Currently redirecting all fullscreen through a window
		//This will probably be more efficient when it gets impletemented, but right now I just can't figure out why fullscreen.cpp won't work
		return calculating(RegionList::WINDOWED, 0, 0, rotation%2?drawing_height:drawing_width, rotation%2?drawing_width:drawing_height);
	}
	else //windowed
		return calculating_Windowed();

	//See you soon..
}

