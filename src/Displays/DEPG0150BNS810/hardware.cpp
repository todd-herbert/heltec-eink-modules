#include "DEPG0150BNS810.h"

///Begin the E-Ink library
void DEPG0150BNS810::begin(const PageProfile profile,  void (*wake_callback)(void), void (*sleep_callback)(void)) {
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

	page_bytecount = panel_width * page_profile.height / 8;		//nb: this is a class member and gets reused
	//page_black = new uint8_t[page_bytecount];	//now called in calculating method for relevant modes
	
	//Set height in the library
	_width = WIDTH = panel_width;
	_height = HEIGHT = panel_height;

	//Set an initial configuration for drawing
	setDefaultColor(colors.WHITE);
	setTextColor(colors.BLACK);
}

///Clear the screen in one step
void DEPG0150BNS810::clear() {
	wake();

	int16_t x, y;
	uint8_t blank_byte = (default_color & colors.WHITE) * 255;	//We're filling in bulk here; bits are either all on or all off

	//Calculate memory values for the slice
	//Note, x values are divided by 8 as horizontal lines are rows of 8bit bytes
	const uint8_t start_x = 0;	//Note the offset
	const uint8_t end_x = (panel_width / 8) - 1;		//This is taken from the official heltec driver

	//y locations are two bytes
	const uint8_t start_y = 0;
	const uint8_t end_y = panel_height - 1;

	//"Data entry mode??"	-- new undocumented command from heltec sdk
	sendCommand(0x11); //data entry mode
  	sendData(0x03);	

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
	sendData(0);

	sendCommand(0x24);   //write RAM for black(0)/white (1)
	for(y = 0; y < panel_width / 8; y++) {
		for(x = 0; x < panel_height; x++) {
			sendData(blank_byte);
		}
  	}

	sendCommand(0x26);   //write RAM for black(0)/white (1)
	for(y = 0; y < panel_width / 8; y++) {
		for(x = 0; x < panel_height; x++) {
			sendData(blank_byte);
		}
  	}
	  
	wait();
	sendCommand(0x22);
	sendData(0xF7);
	sendCommand(0x20);
	wait();
}


//Allocate and Deallocate dynamic memory for graphics operations

void DEPG0150BNS810::grabPageMemory() {
    page_black = new uint8_t[page_bytecount];
}

void DEPG0150BNS810::freePageMemory() {
	delete page_black;
}

//Interface directly with display

void DEPG0150BNS810::sendCommand(uint8_t command) {
	SPI.beginTransaction(spi_settings);
	digitalWrite(pin_dc, LOW);	//DC pin low, tell PanelHardware this spi transfer is a command
	digitalWrite(pin_cs, LOW);

	SPI.transfer(command);

	digitalWrite(pin_cs, HIGH);
	SPI.endTransaction();
}

void DEPG0150BNS810::sendData(uint8_t data) {
	SPI.beginTransaction(spi_settings);
	digitalWrite(pin_dc, HIGH);	//DC pin low, tell PanelHardware this spi transfer is a command
	digitalWrite(pin_cs, LOW);

	SPI.transfer(data);

	digitalWrite(pin_cs, HIGH);
	SPI.endTransaction();
}

///Wake the PanelHardware from sleep mode, so it can be changed
void DEPG0150BNS810::wake() {

	//But first, callback anyone?
	if(wake_callback != NULL) 
		(*wake_callback)();

	wait();
	sendCommand(0x12); // soft reset
	wait();
}

///Wait until the PanelHardware is idle. Important as any commands made while PanelHardware is busy will be discarded.
void DEPG0150BNS810::wait() {
	while(digitalRead(pin_busy) == HIGH)	{	//Low = idle	
		delay(1);
	}
}

void DEPG0150BNS810::setModePartial() {
	//All this stuff is taken from the Heltec Heltec SDK on github
	sendCommand(0x12);	//Reset the panel
	wait();

	unsigned char count;
  	sendCommand(0x32);
  	for(count=0;count<153;count++) 
		sendData(waveform_partial[count]); 
  	wait();

	sendCommand(0x3F); //I have no clue.
	sendData(waveform_partial[153]);

	sendCommand(0x03);      //allegedly: gate voltage  
	sendData(waveform_partial[154]);

	sendCommand(0x04);      //allegedly: source voltage   
	sendData(waveform_partial[155]); 
	sendData(waveform_partial[156]);
	sendData(waveform_partial[157]);

	sendCommand(0x2C);		//allegedly: vcom   
	sendData(waveform_partial[158]);

	sendCommand(0x37);  //allegedly: "Local flash function is enabled, pingpong mode is enabled"
	sendData(0x00);  
	sendData(0x00);  
	sendData(0x00);  
	sendData(0x00); 
	sendData(0x00);  	
	sendData(0x40);  
	sendData(0x00);  
	sendData(0x00);   
	sendData(0x00);  
	sendData(0x00);

	sendCommand(0x3C);  //allegedly: border setting
	sendData(0x80);   
}

void DEPG0150BNS810::setModeFull() {	
	//Resetting the panel seems to be enough to return to full mode
	sendCommand(0x12);
	wait();
}

///Draw the image in Panel's memory to the screen
void DEPG0150BNS810::update(QualityList::Quality update_quality, bool blocking) {
	if (update_quality == quality.FAST) {	//If partial mode
		setModePartial();
		sendCommand(0x22);   //Partial Refresh
		sendData(0xCF);    //?? Translation maybe = "End Partial Mode"
		sendCommand(0x20); //Master Update
	}
	else {	//If full update mode
		sendCommand(0x20);
	}

	if (blocking) {
		wait();	//Block while the command runs
		if(sleep_callback != NULL) 
			(*sleep_callback)();
	}
}

///Redraw screen contents, upgrading from FAST to DETAILED mode
void DEPG0150BNS810::detail() {
	calculating(region.WINDOWED, 0,0,0,0);
    update(quality.DETAILED);
}