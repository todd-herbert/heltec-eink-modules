#include "Heltec_213Red_V2.h"

///Begin the E-Ink library
void Heltec_213Red_V2::begin(const PageProfile profile,  void (*wake_callback)(void), void (*sleep_callback)(void)) {
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
	page_red = new uint8_t[page_bytecount * 2];
	
	//Set height in the library
	_width = WIDTH = panel_width;
	_height = HEIGHT = panel_height;

	//Set an initial configuration for drawing
	setDefaultColor(colors.WHITE);
	setTextColor(colors.BLACK);
}


///Wait until the PanelHardware is idle. Important as any commands made while PanelHardware is busy will be discarded.
void Heltec_213Red_V2::wait() {
	while(digitalRead(pin_busy) == HIGH)	{	//Low = idle	
		delay(1);
	}
}

//Allocate and Deallocate dynamic memory for graphics operations

void Heltec_213Red_V2::grabPageMemory() {
    page_black = new uint8_t[page_bytecount];
	page_red = new uint8_t[page_bytecount];
}

void Heltec_213Red_V2::freePageMemory() {
	delete page_black;
	delete page_red;
}

//Interface directly with display

void Heltec_213Red_V2::sendCommand(uint8_t command) {
	SPI.beginTransaction(spi_settings);
	digitalWrite(pin_dc, LOW);	//DC pin low, tell PanelHardware this spi transfer is a command
	digitalWrite(pin_cs, LOW);

	SPI.transfer(command);

	digitalWrite(pin_cs, HIGH);
	SPI.endTransaction();
}

void Heltec_213Red_V2::sendData(uint8_t data) {
	SPI.beginTransaction(spi_settings);
	digitalWrite(pin_dc, HIGH);	//DC pin low, tell PanelHardware this spi transfer is a command
	digitalWrite(pin_cs, LOW);

	SPI.transfer(data);

	digitalWrite(pin_cs, HIGH);
	SPI.endTransaction();
}

///Wake the PanelHardware from sleep mode, so it can be changed
void Heltec_213Red_V2::wake() {
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
void Heltec_213Red_V2::update(bool blocking) {
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
void Heltec_213Red_V2::clear() {
	wake();
	wait();

	uint16_t x, y;
	uint8_t black_byte = (default_color & colors.WHITE) * 255;	//We're filling in bulk here; bits are either all on or all off
	uint8_t red_byte = ((default_color & colors.RED) >> 1) * 255;

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

