#include "Heltec_290_V2_BLUETAB.h"

///Begin the E-Ink library
void Heltec_290_V2_BLUETAB::begin(const PageProfile profile,  void (*wake_callback)(void), void (*sleep_callback)(void)) {
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
void Heltec_290_V2_BLUETAB::wait() {
	while(digitalRead(pin_busy) == HIGH)	{	//Low = idle	
		delay(1);
	}
}

//Allocate and Deallocate dynamic memory for graphics operations

void Heltec_290_V2_BLUETAB::grabPageMemory() {
    page_black = new uint8_t[page_bytecount];
}

void Heltec_290_V2_BLUETAB::freePageMemory() {
	delete page_black;
}

//Interface directly with display

void Heltec_290_V2_BLUETAB::sendCommand(uint8_t command) {
	SPI.beginTransaction(spi_settings);
	digitalWrite(pin_dc, LOW);	//DC pin low, tell PanelHardware this spi transfer is a command
	digitalWrite(pin_cs, LOW);

	SPI.transfer(command);

	digitalWrite(pin_cs, HIGH);
	SPI.endTransaction();
}

void Heltec_290_V2_BLUETAB::sendData(uint8_t data) {
	SPI.beginTransaction(spi_settings);
	digitalWrite(pin_dc, HIGH);	//DC pin low, tell PanelHardware this spi transfer is a command
	digitalWrite(pin_cs, LOW);

	SPI.transfer(data);

	digitalWrite(pin_cs, HIGH);
	SPI.endTransaction();
}

///Wake the PanelHardware from sleep mode, so it can be changed
void Heltec_290_V2_BLUETAB::wake() {
	//To be honest, not having read the datasheet, this is all well over my head

	//But first, callback anyone?
	if(wake_callback != NULL) 
		(*wake_callback)();

	wait();
	sendCommand(0x12); // soft reset
	wait();

	sendCommand(0x01);	//Driver Output Control
    sendData(0x27); 	//
	sendData(0x01);		//0x127
    sendData(0x00);     //GD = 0; SM = 0; TB = 0 (?)

    sendCommand(0x0C);	//Booster Soft Start Control
    sendData(0xD7);
    sendData(0xD6);
    sendData(0x9D);

    sendCommand(0x2C);	//Write VCOM Register
    sendData(0xA8);     //VCOM 7C (?)

    sendCommand(0x3A);	//Set Dummy Line Register
    sendData(0x1A);     //4 dummy lines per gate (?)

    sendCommand(0x3B);	//Set Gate Time
    sendData(0x08);     //2us per line

    sendCommand(0x11);	//Data Entry Mode Setting
    sendData(0x03);     // X increment; Y increment

	//Write waveform for patial update
	sendCommand(0x32);
	/* the length of look-up table is 30 bytes */
    for (int i = 0; i < 30; i++) {
        sendData(waveform_full[i]);
    }
}



///Draw the image in PanelHardware's memory to the screen
void Heltec_290_V2_BLUETAB::update(bool blocking) {
		wake();
		sendCommand(0x22);	//Display update control 2
		sendData(0xC4);
		sendCommand(0x20);	//Master activation
		sendCommand(0xFF);	//Terminate frame

	if (blocking) {
		wait();	//Block while the command runs
		if(sleep_callback != NULL) 
			(*sleep_callback)();
	}
}


///Clear the screen in one step
void Heltec_290_V2_BLUETAB::clear() {
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

