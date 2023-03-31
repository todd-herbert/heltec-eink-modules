// #include "Displays/DEPG0290BNS800/DEPG0290BNS800.h"

// //Methods that run only in fullscreen mode

// void DEPG0290BNS800::drawPixel_Fullscreen(int16_t x, int16_t y, uint16_t color) {

// 	//Translate the pixel here to allow screen rotation
// 	int16_t x1, y1;
// 	switch(rotation) {
// 		case 0:			//No rotation
// 			x1=x;
// 			y1=y;
// 			break;
// 		case 1:			//90deg clockwise
// 			x1 = (drawing_width - y) - 1;	//First 8 pixels of data are discarded by screen
// 			y1 = x;
// 			break;
// 		case 2:			//180deg
// 			x1 = (drawing_width - x) - 1;
// 			y1 = (drawing_height - 1) - y;
// 			break;
// 		case 3:			//270deg clockwise
// 			x1 = y; //First 8 pixels of data are discarded by screen
// 			y1 = (panel_height - 1) - x;
// 			break;
// 	}
// 	x = x1;
// 	y = y1;

// 	//Potential bandaid for an issues when pixel value is greater than 0xFF?
// 	if (y == 0xFF)
// 		color = colors.BLACK;

// 	//Check if pixel falls in our page
// 	if(y >= (int16_t)page_top && y <= (int16_t)page_bottom && x >= 0 && x <= drawing_width - 1) {	//typecasts only to silence warnings

// 		//Calculate a memory location for our pixel
// 		//A whole lot of this was emperically derived..

// 		uint16_t memory_location;
// 		memory_location = (y - ((page_cursor - 1) * page_profile.height));	//Allow for y offset, to place it correctly in the current page
// 		//memory_location = (page_profile.height - 1) - memory_location;	//Inverting our y location in the page. No idea why, but it makes the screen happy.
// 		memory_location *=  (panel_width / 8);	//Y value is the "outer loop"
// 		memory_location += (x / 8);	//Find which byte our desired bit is in
// 		uint16_t bit_location = x % 8;	//Find the location of the bit in which the value will be stored
// 		bit_location = 7 - bit_location;	//For some reason, the screen wants the bit order flipped. MSB vs LSB?
		
// 		//Insert the correct color values into the appropriate location
// 		uint8_t bitmask = ~(1 << bit_location);
// 		page_black[memory_location] &= bitmask;
// 		page_black[memory_location] |= (color & colors.WHITE) << bit_location;

// 	}
// }

// bool DEPG0290BNS800::calculating_Fullscreen() {
// 	//Some of this looks weird, but it's that everything is being evaluated at the start of the next loop
// 	//No real reason for this over a do while, I just think it looks tidier on the front end

// 	//Beginning of first loop
// 	//===============

// 	if (page_cursor == 0) {
// 		clearPage(default_color);
// 		wake();					//Get the panel ready to receive the spi data
// 		page_top = 0;
// 		page_bottom = page_profile.height - 1;
// 	}

// 	//End of each loop
// 	//===============
// 	else { 
// 		//Send off the old page
// 		writePage_Fullscreen();

// 		//Calculate memory locations for the new page
// 		page_top = page_cursor * page_profile.height;
// 		page_bottom = page_top + page_profile.height - 1;
// 		clearPage(default_color);
// 	}

// 	//Check whether loop should continue
// 	//=============
// 	if ((page_cursor) == page_profile.count) {
// 		page_cursor = 0; //Reset for next time
// 		return false;	//We're done
// 	}
// 	else {
// 		page_cursor++;
// 		return true;	//Keep looping
// 	}
// }

// ///Write one small slice of the screen
// void DEPG0290BNS800::writePage_Fullscreen() {

// 	//Calculate memory values for the slice
// 	//Note, x values are divided by 8 as horizontal lines are rows of 8bit bytes
// 	int16_t sx, sy, ex, ey;
// 	int16_t sy2(0), ey2(0);
// 	sx = 0;	
// 	ex = (drawing_width / 8) - 1;		//This is taken from the official heltec driver

// 	//y locations are two bytes
// 	sy = page_top;
// 	ey = page_bottom;	

// 	if(sy>=256) {	//Imported from heltec driver
// 		sy2=sy/256;
// 		sy=sy%256;
// 	}

// 	if(ey>=256) {
// 		ey2=ey/256;
// 		ey=ey%256;		
// 	}		

// 	// //"Data entry mode??"	-- new command demonstrated in heltec sdk
// 	sendCommand(0x11); //data entry mode
//   	sendData(0x03);	//Increment x, increment y

// 	//Inform the panel hardware of our chosen memory location
// 	sendCommand(0x44);	//Memory X start - end
// 	sendData(sx);
// 	sendData(ex);
// 	sendCommand(0x45);	//Memory Y start - end
// 	sendData(sy);
// 	sendData(sy2);										
// 	sendData(ey);
// 	sendData(ey2);										
// 	sendCommand(0x4E);	//Memory cursor X
// 	sendData(sx);
// 	sendCommand(0x4F);	//Memory cursor y
// 	sendData(sy);
// 	sendData(sy2);										

// 	//Now we can send over our image data

// 	sendCommand(0x24);   //write memory for black(0)/white (1)
// 	for (uint16_t i = 0; i < page_bytecount; i++) {
// 		sendData(page_black[i]);
// 	}

// 	wait();	
// 	//Nothing happens now until hardware.update() is called
// }