#include "Displays/Heltec_213Red_V2/Heltec_213Red_V2.h"

//Methods that run only in fullscreen mode

void Heltec_213Red_V2::drawPixel_Fullscreen(int16_t x, int16_t y, uint16_t color) {

	//Translate the pixel here to allow screen rotation
	int16_t x1, y1;
	switch(rotation) {
		case 0:			//No rotation
			x1=x;
			y1=y;
			break;
		case 1:			//90deg clockwise
			x1 = (panel_width - y) - 7;	//First 8 pixels of data are discarded by screen
			y1 = x;
			break;
		case 2:			//180deg
			x1 = (panel_width - x) - 7;
			y1 = (panel_height - 1) - y;
			break;
		case 3:			//270deg clockwise
			x1 = y; //First 8 pixels of data are discarded by screen
			y1 = (panel_height - 1) - x;
			break;
	}
	x = x1;
	y = y1;

	//Handle flip
	if (imgflip & FlipList::HORIZONTAL) {
		if (rotation % 2)	//If landscape
			y = drawing_height - y;
		else					//If portrait
			x = drawing_width - x;
	}
	if (imgflip & FlipList::VERTICAL) {
		if (rotation % 2)	//If landscape
			x = drawing_width - x;
		else					//If portrait
			y = drawing_height - y;
	}

	//Check if pixel falls in our page
	if(y >= page_top && y <= page_bottom && x >= 0 && x <= drawing_width - 1) {

		//Calculate a memory location for our pixel
		//A whole lot of this was emperically derived..

		uint16_t memory_location;
		memory_location = (y - ((page_cursor - 1) * page_profile.height));	//Allow for y offset, to place it correctly in the current page
		memory_location = (page_profile.height - 1) - memory_location;	//Inverting our y location in the page. No idea why, but it makes the screen happy.
		memory_location *=  (panel_width / 8);	//Y value is the "outer loop"
		memory_location += (x / 8);	//Find which byte our desired bit is in
		uint8_t bit_location = x % 8;	//Find the location of the bit in which the value will be stored
		bit_location = 7 - bit_location;	//For some reason, the screen wants the bit order flipped. MSB vs LSB?
		
		//Insert the correct color values into the appropriate location
		uint8_t bitmask = ~(1 << bit_location);
		page_black[memory_location] &= bitmask;
		page_black[memory_location] |= (color & colors.WHITE) << bit_location;
		page_red[memory_location] &= bitmask;
		page_red[memory_location] |= (color >> 1) << bit_location;

	}
}

bool Heltec_213Red_V2::calculating_Fullscreen() {
	//Some of this looks weird, but it's that everything is being evaluated at the start of the next loop
	//No real reason for this over a do while, I just think it looks tidier on the front end

	//Beginning of first loop
	//===============

	if (page_cursor == 0) {
		//Code is transitioning to "window only" backend. This straddles the gap
		this->window_left = bounds.full.left();
		this->window_top = bounds.full.top();
		this->window_right = bounds.full.right();
		this->window_bottom = bounds.full.bottom();
		switch (rotation) {
			case 0:
				winrot_top = window_top;
				winrot_right = window_right;
				winrot_bottom = window_bottom;
				winrot_left = window_left;
				break;

			case 1:
				winrot_top = window_left;
				winrot_right = panel_width - window_top;
				winrot_bottom = window_right;
				winrot_left = panel_width - window_bottom;
				break;

			case 2:
				winrot_top = panel_height - window_bottom;
				winrot_right = panel_width - window_left;
				winrot_bottom = panel_height - window_top;
				winrot_left = panel_width - window_right;
				break;
			
			case 3:
				winrot_top = panel_height - window_right;
				winrot_right = window_bottom;
				winrot_bottom = panel_height - window_left;
				winrot_left = window_top;
		}

		grabPageMemory();
		clearPage(default_color);
		wake();					//Get the panel ready to receive the spi data
		page_top = 0;
		page_bottom = page_profile.height - 1;
	}

	//End of each loop
	//===============
	else { 
		//Send off the old page
		writePage_Fullscreen();

		//Calculate memory locations for the new page
		page_top = page_cursor * page_profile.height;
		page_bottom = page_top + page_profile.height - 1;
		clearPage(default_color);
	}

	//Check whether loop should continue
	//=============
	if ((page_cursor) == page_profile.count) {
		page_cursor = 0; //Reset for next time
		freePageMemory();
		return false;	//We're done
	}
	else {
		page_cursor++;
		return true;	//Keep looping
	}
}

///Write one small slice of the screen
void Heltec_213Red_V2::writePage_Fullscreen() {

	//Calculate memory values for the slice
	//Note, x values are divided by 8 as horizontal lines are rows of 8bit bytes
	uint8_t start_x = 1;	//Note the offset
	uint8_t end_x = 16;		//This is taken from the official heltec driver

	//y locations are two bytes
	uint8_t end_y = page_top;		//Note the inversion of these two. No idea why, just note it.
	uint8_t start_y = page_bottom;	
	

	//Inform the panel hardware of our chosen memory location
	sendCommand(0x44);	//Memory X start - end
	sendData(start_x);
	sendData(end_x);
	sendCommand(0x45);	//Memory Y start - end
	sendData(start_y);
	sendData(0);										//Bit 8 - not required, max y is 250
	sendData(end_y);
	sendData(0);										//Bit 8 - not required, max y is 250
	sendCommand(0x4E);	//Memory cursor X
	sendData(start_x);
	sendCommand(0x4F);	//Memory cursor y
	sendData(start_y);
	sendData(0);										//Bit 8 - not required, max y is 250

	//Now we can send over our image data

	sendCommand(0x24);   //write memory for black(0)/white (1)
	for (uint16_t i = 0; i < page_bytecount; i++) {
		sendData(page_black[i]);
	}

    sendCommand(0x26);   //write memory for red(1)/white (0)
	for (uint16_t i = 0; i < page_bytecount; i++) {
		sendData(page_red[i]);
	}

	wait();	
	//Nothing happens now until hardware.update() is called
}