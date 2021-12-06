#include "Displays/Heltec_290_V2_BLUETAB/Heltec_290_V2_BLUETAB.h"

//Methods that run only in windowed mode


bool Heltec_290_V2_BLUETAB::calculating_Windowed() {

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

		grabPageMemory();
		clearPage(default_color);
		wake();					//Get the panel ready to receive the spi data

		page_top = winrot_top;	//We're now translating the window in drawPixel()
		page_bottom = min(page_top + page_profile.height, winrot_bottom);
		pagefile_length = (page_bottom - page_top) * ((winrot_right - winrot_left) / 8);
	}

	//End of each loop
	//===============
	else {
		//Check if the last page contained any part of the window
		if (!(winrot_bottom < page_top || winrot_top > page_bottom))
			writePage_Windowed();	//Send off the old page

		//Calculate memory locations for the new page
		page_top += page_profile.height;
		page_bottom = min(page_top + page_profile.height, winrot_bottom);
		pagefile_length = (page_bottom - page_top) * ((winrot_right - winrot_left) / 8);
		clearPage(default_color);
	}

	//Check whether loop should continue
	//=============
	if (page_top >= winrot_bottom) {
		page_cursor = 0; //Reset for next time
        //Todo: grab and free page memory
		freePageMemory();
		return false;	//We're done
	
	}
	else {
		page_cursor++;
		return true;	//Keep looping
	}
}

void Heltec_290_V2_BLUETAB::drawPixel_Windowed(int16_t x, int16_t y, uint16_t color) {

	//Rotate the pixel
	int16_t x1, y1;
	switch(rotation) {
		case 0:			//No rotation
			x1=x;
			y1=y;
			break;
		case 1:			//90deg clockwise
			x1 = (drawing_width - y - 1);
			y1 = x;
			break;
		case 2:			//180deg
			x1 = (drawing_width - 1) - x;	//Make sure we really do draw the pixel within the imaginary margins, even though window is larger
			y1 = (drawing_height - 1) - y;
			break;
		case 3:			//270deg clockwise
			x1 = y;
			y1 = (drawing_height - 1) - x;
			break;
	}
	x = x1;
	y = y1;

	//Handle flip
	if (imgflip & FlipList::HORIZONTAL) {
		if (rotation % 2)	//If landscape
			y = (drawing_height - 1) - y;
		else					//If portrait
			x = (drawing_width - 1) - x;
	}
	if (imgflip & FlipList::VERTICAL) {
		if (rotation % 2)	//If landscape
			x = (drawing_width - 1) - x;
		else					//If portrait
			y = (drawing_height - 1) - y;
	}

	//Check if pixel falls in our page
	if(x >= (int16_t)winrot_left && y >= (int16_t)page_top && y <= (int16_t)page_bottom && x <= (int16_t)winrot_right - 1) {	//typecasts only to silence warnings

		//Calculate a memory location for our pixel
		//A whole lot of emperically derived "inverting" went on here

		uint16_t memory_location;
		
		memory_location = ((page_bottom - page_top) - (page_bottom - y)) * ((winrot_right - winrot_left) / 8);
		memory_location += ((x - winrot_left) / 8);		
		uint8_t bit_location = x % 8;	//Find the location of the bit in which the value will be stored
		bit_location = (7 - bit_location);	//For some reason, the screen wants the bit order flipped. MSB vs LSB?

		//Insert the correct color values into the appropriate location
		uint8_t bitmask = ~(1 << bit_location);
		page_black[memory_location] &= bitmask;
		page_black[memory_location] |= (color & colors.WHITE) << bit_location;
	}
}

void Heltec_290_V2_BLUETAB::writePage_Windowed() {
	//Calculate rotate x start and stop values (y is already done via paging)

	int16_t sx, sy, ex, ey;
	int16_t sy2(0), ey2(0);

	sx = (winrot_left / 8);
	sy = page_top;
	ex = (winrot_right / 8) - 1;
	ey = page_bottom;

	if(sy>=256) {	//Imported from heltec driver
		sy2=sy/256;
		sy=sy%256;
	}

	if(ey>=256) {
		ey2=ey/256;
		ey=ey%256;		
	}		

	//"Data entry mode??"	-- new command demonstrated in heltec sdk
	sendCommand(0x11); //data entry mode
  	sendData(0x03);	//Increment x, increment y

	//Inform the panel hardware of our chosen memory location
	sendCommand(0x44);	//Memory X start - end
	sendData(sx);
	sendData(ex);
	sendCommand(0x45);	//Memory Y start - end
	sendData(sy);
	sendData(sy2);										
	sendData(ey);
	sendData(ey2);										
	sendCommand(0x4E);	//Memory cursor X
	sendData(sx);
	sendCommand(0x4F);	//Memory cursor y
	sendData(sy);
	sendData(sy2);										

	//Now we can send over our image data
	sendCommand(0x24);   //write memory for black(0)/white (1)
	for (uint16_t i = 0; i < pagefile_length; i++) {
		sendData(page_black[i]);
	}

	wait();
	//Nothing happens now until update() is called
}