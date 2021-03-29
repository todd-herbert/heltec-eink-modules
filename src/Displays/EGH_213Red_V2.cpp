#include "Displays/EGH_213Red_V2.h"

///Begin the E-Ink library
void EGH_213Red_V2::begin(const PageProfile profile,  void (*wake_callback)(void), void (*sleep_callback)(void)) {
	//Store the page profile
	this->page_profile = profile;

	//Store the callbacks
	this->wake_callback = wake_callback;
	this->sleep_callback = sleep_callback;

	//Set the digital pins that supplement the SPI interface
	pinMode(pin_cs, OUTPUT);		//Incase we weren't give the standard pin 10 as SS
	pinMode(pin_dc, OUTPUT);
	pinMode(pin_busy, INPUT); 	//NOTE: do not use internal pullups, as we're reading a 3.3v output with our ~5v arduino
	
	//Prepare SPI
	SPI.begin();

	//Grab some memory for the pages
	page_bytecount = panel_width * page_profile.height / 8;		//nb: this is a class member and gets reused
	page_black = new uint8_t[page_bytecount];
	page_red = new uint8_t[page_bytecount];
	
	//Set height in the library
	_width = WIDTH = panel_width;
	_height = HEIGHT = panel_height;

	//Set an initial configuration for drawing
	setDefaultColor(WHITE);
	setTextColor(BLACK);
}



///Draw a single pixel. 
///This method is overriden from GFX_Root, and all other drawing methods pass through here
void EGH_213Red_V2::drawPixel(int16_t x, int16_t y, uint16_t color) {
	//Page cursor reads 1 during first iteration
	//So we often need to subtract 1

	//Flip the image if needed
	if (img_flip == FLIP_WIDTH)
		x = drawing_width - x;
	else if (img_flip == FLIP_HEIGHT)
		y = drawing_width - y;
	else if (img_flip == FLIP_WIDTH_AND_HEIGHT) {
		x = drawing_width - x;
		y = drawing_height - y;
	}

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
			x1 = y;
			y1 = (panel_height - 1) - x;
			break;
	}
	x = x1;
	y = y1;

	//Check if pixel falls in our page
	if(y >= page_top && y <= page_bottom && x >= 0 && x <= drawing_width - 1) {

		//Calculate a memory location for our pixel
		//A whole lot of emperically derived "inverting" went on here
		//The y values of the pixels in each page are inverted, but not the pages themselves
		//The bit order of the x pixels is inverted, but not the order of the pixels themselves
		//To top it off, one final inversion is needed in writePage(), but all the nonsense seems to balance out eventually
		//(This is probably all my fault)
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
		page_black[memory_location] |= (color & WHITE) << bit_location;
		page_red[memory_location] &= bitmask;
		page_red[memory_location] |= (color >> 1) << bit_location;

	}
}



///Set the color of the blank canvas, before any drawing is done
///Note: Function is efficient, but only takes effect at the start of a calculation. At any other time, use fillScreen()
void EGH_213Red_V2::setDefaultColor(uint16_t bgcolor) {
	default_color = bgcolor;
}

void EGH_213Red_V2::setFlip(Flip flip) {
	this->img_flip = flip;
}



///Clear the data arrays in between pages
void EGH_213Red_V2::clearPage(uint16_t bgcolor) {
	for (uint16_t i = 0; i < page_bytecount; i++) {
		uint8_t black_byte = (bgcolor & WHITE) * 255;	//We're filling in bulk here; bits are either all on or all off
		uint8_t red_byte = ((bgcolor & RED) >> 1) * 255;
		page_black[i] = black_byte;
		page_red[i] = red_byte;
	}
}



///Used with a WHILE loop, to break the graphics into small parts, and draw them one at a time
bool EGH_213Red_V2::calculating(bool blocking = true) {
	//NOTE: this loop runs BEFORE every new page.
	//This means that it is actually also processing all the data generated in the last loop

	//Some of this looks weird, but it's that everything is being evaluated at the start of the next loop
	//No real reason for this over a do while, just personal preference

	//Beginning of first loop
	//===============

	if (page_cursor == 0) {
		clearPage(default_color);
		wake();					//Get the panel ready to receive the spi data
		page_top = 0;
		page_bottom = page_profile.height - 1;
	}

	//End of each loop
	//===============
	else { 
		//Send off the old page
		writePage();

		//Calculate memory locations for the new page
		page_top = page_cursor * page_profile.height;
		page_bottom = page_top + page_profile.height - 1;
		clearPage(default_color);
	}

	//Check whether loop should continue
	//=============
	if ((page_cursor) == page_profile.count) {
		page_cursor = 0; //Reset for next time
		update(blocking);		//Refresh changes onto the screen
		return false;	//We're done
	}
	else {
		page_cursor++;
		return true;	//Keep looping
	}
}

///Set the text cursor according to the desired upper left corner
void EGH_213Red_V2::setCursorCorner( char* text, uint16_t x, uint16_t y) {
	int16_t offset_x, offset_y;
	getTextBounds(text, 0, 0, &offset_x, &offset_y, NULL, NULL);
	setCursor(x + offset_x, y + offset_y);
}

//Hardware Methods
//======================================================================================================================

///Wait until the PanelHardware is idle. Important as any commands made while PanelHardware is busy will be discarded.
void EGH_213Red_V2::wait() {
	while(digitalRead(pin_busy) == HIGH)	{	//Low = idle	
		delay(1);
	}
}

void EGH_213Red_V2::sendCommand(uint8_t command) {
	SPI.beginTransaction(spi_settings);
	digitalWrite(pin_dc, LOW);	//DC pin low, tell PanelHardware this spi transfer is a command
	digitalWrite(pin_cs, LOW);

	SPI.transfer(command);

	digitalWrite(pin_cs, HIGH);
	SPI.endTransaction();
}

void EGH_213Red_V2::sendData(uint8_t data) {
	SPI.beginTransaction(spi_settings);
	digitalWrite(pin_dc, HIGH);	//DC pin low, tell PanelHardware this spi transfer is a command
	digitalWrite(pin_cs, LOW);

	SPI.transfer(data);

	digitalWrite(pin_cs, HIGH);
	SPI.endTransaction();
}

///Wake the PanelHardware from sleep mode, so it can be changed
void EGH_213Red_V2::wake() {
	//To be honest, not having read the datasheet, this is all well over my head
	//It came copied and pasted from the half-baked heltec driver

	//But first, callback anyone?
	if(wake_callback != NULL) 
		(*wake_callback)();

	wait();

	sendCommand(0x12); // soft reset
	wait();

	sendCommand(0x74); //set analog block control     
	sendData(0x54);
	sendCommand(0x7E); //set digital block control          
	sendData(0x3B);

	sendCommand(0x01); //Driver output control      
	sendData(0xF9);
	sendData(0x00);
	sendData(0x00);

	sendCommand(0x11); //data entry mode       
	sendData(0x01);

	sendCommand(0x44); //set Ram-X address start/end position   
	sendData(0x01);
	sendData(0x10);    //0x0F-->(15+1)*8=128

	sendCommand(0x45); //set Ram-Y address start/end position          
	sendData(0xF9);   //0xF9-->(249+1)=250
	sendData(0x00);
	sendData(0x00);
	sendData(0x00); 

	sendCommand(0x3C); //BorderWavefrom
	sendData(0x01);	

  	sendCommand(0x18); 
	sendData(0x80);	

	sendCommand(0x4E);   // set RAM x address count to 0;
	sendData(0x01);
	sendCommand(0x4F);   // set RAM y address count to 0xF9-->(249+1)=250;    
	sendData(0xF9);
	sendData(0x00);

	wait();
}



///Draw the image in PanelHardware's memory to the screen
void EGH_213Red_V2::update(bool blocking) {
	sendCommand(0x22);
	sendData(0xF7);
	sendCommand(0x20);

	if (blocking) {
		wait();	//Block while the command runs
		if(sleep_callback != NULL) 
			(*sleep_callback)();
	}
}


///Clear the screen in one step
void EGH_213Red_V2::clear() {
	wake();
	wait();

	uint16_t x, y;
	uint8_t black_byte = (default_color & WHITE) * 255;	//We're filling in bulk here; bits are either all on or all off
	uint8_t red_byte = ((default_color & RED) >> 1) * 255;

	sendCommand(0x24);   //write RAM for black(0)/white (1)
	for(y = 0; y < panel_width; y++) {
		for(x = 0; x < panel_height; x++) {
			sendData(black_byte);
		}
  	}
	
    sendCommand(0x26);   //write RAM for red(1)/white (0)
	for(y = 0; y < panel_width; y++) {
		for(x=0; x < panel_height; x++) {
			sendData(red_byte);
		}
  	}
	update();
}



///Write one small slice of the screen
void EGH_213Red_V2::writePage() {

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
		//sendData(0);
	}

    sendCommand(0x26);   //write memory for red(1)/white (0)
	for (uint16_t i = 0; i < page_bytecount; i++) {
		sendData(page_red[i]);
	}

	wait();	
	//Nothing happens now until hardware.update() is called
}
