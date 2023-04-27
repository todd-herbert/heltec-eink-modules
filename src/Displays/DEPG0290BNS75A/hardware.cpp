#include "DEPG0290BNS75A.h"

/// Begin the E-Ink library
void DEPG0290BNS75A::begin(const PageProfile profile) {
	// Store the page profile
	this->page_profile = profile;

	// Set the digital pins that supplement the SPI interface
	pinMode(pin_cs, OUTPUT);		// Incase we weren't give the standard pin 10 as SS
	pinMode(pin_dc, OUTPUT);
	pinMode(pin_busy, INPUT); 	// NOTE: do not use internal pullups, as we're reading a 3.3v output with our ~5v arduino
	
	// Prepare SPI
	SPI.begin();	

	page_bytecount = panel_width * page_profile.height / 8;		// nb: this is a class member and gets reused
	// page_black = new uint8_t[page_bytecount];	// now called in calculating method for relevant modes
	
	// Set height in the library
	_width = WIDTH = panel_width;
	_height = HEIGHT = panel_height;

	// Set an initial configuration for drawing
	setDefaultColor(colors.WHITE);
	setTextColor(colors.BLACK);
	fullscreen();
	// setFastmode(fastmode.OFF); 	// Unimplemented
}

/// Clear the screen in one step
void DEPG0290BNS75A::clear() {
	reset();

	int16_t x, y;
	uint8_t blank_byte = (default_color & colors.WHITE) * 255;	// We're filling in bulk here; bits are either all on or all off

	// Calculate memory values for the slice
	// Note, x values are divided by 8 as horizontal lines are rows of 8bit bytes
	const uint16_t start_x = 0;	// Note the offset
	const uint16_t end_x = (panel_width / 8) - 1;		// This is taken from the official heltec driver

	// y locations are two bytes
	uint16_t start_y = 0;
	uint16_t end_y = panel_height - 1;

	// Handle byte overflows
	uint16_t start_y2, end_y2;

	if(start_y >= 256) {
		start_y2 = start_y / 256;
		start_y = start_y % 256;
	}

	if(end_y >= 256) {
		end_y2 = end_y / 256;
		end_y = end_y % 256;	
	}

	// Data entry mode - Left to Right, Top to Bottom
	sendCommand(0x11);
  	sendData(0x03);

	// Inform the panel hardware of our chosen memory location
	sendCommand(0x44);	// Memory X start - end
	sendData(start_x);
	sendData(end_x);
	sendCommand(0x45);	// Memory Y start - end
	sendData(start_y);
	sendData(start_y2);
	sendData(end_y);
	sendData(end_y2);
	sendCommand(0x4E);	// Memory cursor X
	sendData(start_x);
	sendCommand(0x4F);	// Memory cursor y
	sendData(start_y);
	sendData(start_y2);										// Bit 8 - not required, max y is 250

	sendCommand(0x24);   // Fill "BLACK" memory with default_color
	for(y = 0; y < panel_width / 8; y++) {
		for(x = 0; x < panel_height; x++) {
			sendData(blank_byte);
		}
  	}

	sendCommand(0x26);   // Fill "RED" memory with default_color
	for(y = 0; y < panel_width / 8; y++) {
		for(x = 0; x < panel_height; x++) {
			sendData(blank_byte);
		}
  	}
	
	// Trigger the display update
	sendCommand(0x22);
	sendData(0xF7);
	sendCommand(0x20);
	wait();
}


// Allocate and Deallocate dynamic memory for graphics operations

void DEPG0290BNS75A::grabPageMemory() {
    page_black = new uint8_t[page_bytecount];
}

void DEPG0290BNS75A::freePageMemory() {
	delete page_black;
}

// Interface directly with display

void DEPG0290BNS75A::sendCommand(uint8_t command) {
	SPI.beginTransaction(spi_settings);
	digitalWrite(pin_dc, LOW);	// Data-Command pin LOW, tell PanelHardware this SPI transfer is a command
	digitalWrite(pin_cs, LOW);

	SPI.transfer(command);

	digitalWrite(pin_cs, HIGH);
	SPI.endTransaction();
}

void DEPG0290BNS75A::sendData(uint8_t data) {
	SPI.beginTransaction(spi_settings);
	digitalWrite(pin_dc, HIGH);	// Data-Command pin HIGH, tell PanelHardware this SPI transfer is data
	digitalWrite(pin_cs, LOW);

	SPI.transfer(data);

	digitalWrite(pin_cs, HIGH);
	SPI.endTransaction();
}

/// Wake the PanelHardware from sleep mode, so it can be changed
void DEPG0290BNS75A::reset() {

	if (mode == fastmode.OFF) { 
		sendCommand(0x12); // Software Reset
		wait();
	}

	// Technical settings. Released by Heltec.
	// -------------------------------------------------------
	sendCommand(0x74); // "Analog Block Control"
	sendData(0x54);
	sendCommand(0x7E); // "Digital Block Control"
	sendData(0x3B);

	sendCommand(0x01); // "Driver output control" 
	sendData(0x27);
	sendData(0x01);
	sendData(0x00);

	sendCommand(0x3C); // "Border Waveform"
	sendData(0x01);	

	sendCommand(0x18); // use the internal temperature sensor
    sendData(0x80);

	// --------------------------------------------------------
	wait();
}

/// Wait until the PanelHardware is idle. Important as any commands made while Panel Hardware is busy will be discarded.
void DEPG0290BNS75A::wait() {
	while(digitalRead(pin_busy) == HIGH)	{	// Low = idle	
		delay(1);
	}
}

/// Write one page to the panel memory
void DEPG0290BNS75A::writePage() {
	// Calculate rotate x start and stop values (y is already done via paging)
	int16_t sx, sy, ex, ey;
	int16_t sy2(0), ey2(0);

	sx = winrot_left / 8;
	sy = page_top;
	ex = ((winrot_right + 1) / 8) - 1;
	ey = page_bottom;

	if(sy>=256) {
		sy2=sy/256;
		sy=sy%256;
	}

	if(ey>=256) {
		ey2=ey/256;
		ey=ey%256;		
	}	

	// Data entry mode - Left to Right, Top to Bottom
	sendCommand(0x11);
  	sendData(0x03);

	// Inform the panel hardware of our chosen memory location
	sendCommand(0x44);	// Memory X start - end
	sendData(sx);
	sendData(ex);
	sendCommand(0x45);	// Memory Y start - end
	sendData(sy);
	sendData(sy2);										// Bit 8 - not required, max y is 250
	sendData(ey);
	sendData(ey2);										// Bit 8 - not required, max y is 250
	sendCommand(0x4E);	// Memory cursor X
	sendData(sx);
	sendCommand(0x4F);	// Memory cursor y
	sendData(sy);
	sendData(sy2);										// Bit 8 - not required, max y is 250

	// Now we can send over our image data
	sendCommand(0x24);   // Write "BLACK" memory
	for (uint16_t i = 0; i < pagefile_length; i++) {
		sendData(page_black[i]);
	}

	// Write so-called "RED" memory. With this display, the memory is used during fastmode.
	// Counter-intuitively, need to write both BLACK and RED during normal use.
	// This preserves the image when moving into fastmode.
	if (mode == fastmode.OFF) {
		sendCommand(0x26);   
		for (uint16_t i = 0; i < pagefile_length; i++) {
			sendData(page_black[i]);
		}
	}
	wait();
}

// /Draw the image in Panel's memory to the screen
void DEPG0290BNS75A::update(bool override_checks) {
	if (mode == fastmode.OFF || override_checks) {
		// Specify the update operation to run
		sendCommand(0x22);
		if (mode == fastmode.OFF) 	sendData(0xF7);
		else 						sendData(0xC4);

		// Execute the update
		sendCommand(0x20);

		// Block while the command runs
		wait();
	}
}

/// Set the panel to an ultra low power state. Only way to exit is to cycle power to VCC.
void DEPG0290BNS75A::deepSleep(uint16_t pause) {
	sendCommand(0x10);
	sendData(0x01);
	delay(pause);
}