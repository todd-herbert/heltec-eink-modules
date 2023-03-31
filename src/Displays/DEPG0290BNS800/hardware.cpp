#include "DEPG0290BNS800.h"

///Begin the E-Ink library
void DEPG0290BNS800::begin(const PageProfile profile,  void (*wake_callback)(void), void (*sleep_callback)(void)) {
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
    //Debug: bigger pagefile. Todo: remove
	page_bytecount = panel_width * page_profile.height / 8;		//nb: this is a class member and gets reused
	page_black = new uint8_t[page_bytecount * 2];
	
	//Set height in the library
	_width = WIDTH = panel_width;
	_height = HEIGHT = panel_height;

	//Set an initial configuration for drawing
	setDefaultColor(colors.WHITE);
	setTextColor(colors.BLACK);
}


///Wait until the PanelHardware is idle. Important as any commands made while PanelHardware is busy will be discarded.
void DEPG0290BNS800::wait() {
	while(digitalRead(pin_busy) == HIGH)	{	//Low = idle	
		delay(1);
	}
}

//Allocate and Deallocate dynamic memory for graphics operations

void DEPG0290BNS800::grabPageMemory() {
    page_black = new uint8_t[page_bytecount];
}

void DEPG0290BNS800::freePageMemory() {
	delete page_black;
}

//Interface directly with display

void DEPG0290BNS800::sendCommand(uint8_t command) {
	SPI.beginTransaction(spi_settings);
	digitalWrite(pin_dc, LOW);	//DC pin low, tell PanelHardware this spi transfer is a command
	digitalWrite(pin_cs, LOW);

	SPI.transfer(command);

	digitalWrite(pin_cs, HIGH);
	SPI.endTransaction();
}

void DEPG0290BNS800::sendData(uint8_t data) {
	SPI.beginTransaction(spi_settings);
	digitalWrite(pin_dc, HIGH);	//DC pin low, tell PanelHardware this spi transfer is a command
	digitalWrite(pin_cs, LOW);

	SPI.transfer(data);

	digitalWrite(pin_cs, HIGH);
	SPI.endTransaction();
}

///Wake the Panel Hardware from sleep mode, so it can be changed
void DEPG0290BNS800::wake() {
	//User callback
	if(wake_callback != NULL) 
		(*wake_callback)();

	wait();

	sendCommand(0x12); //Soft Reset
	wait();

	// Technical Hardware Settings (ex. Heltec)
	//--------------------------------------------------------
	sendCommand(0x74); //Analog block control       
    sendData(0x54);
    sendCommand(0x7E); //Digital block control          
    sendData(0x3B);
	sendCommand(0x01); //Driver output control      
    sendData(0x27);
    sendData(0x01);
    sendData(0x00);
	sendCommand(0x18); //Use internal temperature sensor
    sendData(0x80);
	sendCommand(0x3C); //Border waveform
    sendData(0x01);	
	//---------------------------------------------------------
}


void DEPG0290BNS800::writePage() {

	//Calculate rotate x start and stop values (y is already done in the page calculations)
	int16_t sx, sy, ex, ey;
	int16_t sy2(0), ey2(0);

	sx = (winrot_left / 8);
	sy = page_top;
	ex = (winrot_right / 8) - 1;
	ey = page_bottom;

	if(sy>=256) {
		sy2=sy/256;
		sy=sy%256;
	}

	if(ey>=256) {
		ey2=ey/256;
		ey=ey%256;		
	}		

	// Data entry mode - which was the image bits are sent
	sendCommand(0x11);
  	sendData(0x03);		//Increment Y, increment X. What you'd expect

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


///Draw the image in PanelHardware's memory to the screen
void DEPG0290BNS800::update(bool blocking) {
	sendCommand(0x21);	// Which of the display's two memory areas to draw from
	sendData(0x40);
	sendCommand(0x22);	// Operation sequence for the display hardware
	sendData(0xF7);

	sendCommand(0x20); // Actually update the display

	if (blocking) {
		wait();	//Block while the command runs
		if(sleep_callback != NULL) 
			(*sleep_callback)();
	}
}


///Clear the screen in one step
void DEPG0290BNS800::clear() {
	wake();
	wait();

	uint16_t x, y;
	uint8_t black_byte = (default_color & colors.WHITE) * 255;	//We're filling in bulk here; bits are either all on or all off

	sendCommand(0x24);   //write RAM for black(0)/white (1)
	for(y = 0; y < panel_width; y++) {
		for(x = 0; x < panel_height; x++) {
			sendData(black_byte);
		}
  	}
	update();
}

