#include "QYEG0213RWS800.h"

// Constructor
QYEG0213RWS800::QYEG0213RWS800(uint8_t pin_dc, uint8_t pin_cs, uint8_t pin_busy, uint8_t page_height) : GFX(panel_width, panel_height) {
    // Store the config
    this->pin_dc = pin_dc;
    this->pin_cs = pin_cs;
    this->pin_busy = pin_busy;
    this->pagefile_height = page_height;

    // Instantiate nested classes and pass references
    this->bounds = Bounds(  &winrot_top, 
                            &winrot_right, 
                            &winrot_bottom, 
                            &winrot_left, 
                            &rotation,
                            &imgflip    );
    
    // Set the digital pins that supplement the SPI interface
    pinMode(pin_cs, OUTPUT);    // Incase we weren't give the standard pin 10 as SS
    pinMode(pin_dc, OUTPUT);
    pinMode(pin_busy, INPUT);   // NOTE: do not use internal pullups, as we're reading a 3.3v output with our ~5v arduino
    
    // Prepare SPI
    digitalWrite(pin_cs, HIGH); // Helpful if using more than one display
    SPI.begin();

    // Calculate pagefile size
    pagefile_height = constrain(pagefile_height, 1, 50);
    page_bytecount = panel_width * pagefile_height / 8;     

    // Set an initial configuration for drawing
    setDefaultColor(colors.WHITE);
    setTextColor(colors.BLACK);
    fullscreen();
}

/// Clear the screen in one step
void QYEG0213RWS800::clear() {
    reset();
    wait();

    // Tell panel hardware that we want to clear the whole screen
    fullscreen();
    
    int16_t sx, sy, ex, ey;
    sx = 0 + 1;      // I don't understand why this is +1, but it seems necessary, and the official Heltec driver also does this.
    ex = ((drawing_width - 1) / 8) + 1;
    sy = 0;
    ey = drawing_height;

    // Data entry mode - Right to Left, Top to Bottom
    sendCommand(0x11);
      sendData(0x03);

    // Inform the panel hardware of our chosen memory location
    sendCommand(0x44);  // Memory X start - end
    sendData(sx);
    sendData(ex);
    sendCommand(0x45);  // Memory Y start - end
    sendData(sy);
    sendData(0);        // NB: Controller accepts Y values > 256, but this panel is small, so second byte is always 0
    sendData(ey);
    sendData(0);                                        
    sendCommand(0x4E);  // Memory cursor X
    sendData(sx);
    sendCommand(0x4F);  // Memory cursor y
    sendData(sy);
    sendData(0);    

    uint16_t x, y;
    uint8_t black_byte = (default_color & colors.WHITE) * 255;          // We're filling in bulk here; bits are either all on or all off
    uint8_t red_byte = ((default_color & colors.RED) >> 1) * 255;

    sendCommand(0x24);   // Write RAM for black(0)/white (1)
    for(y = 0; y < panel_width; y++) {
        for(x = 0; x < panel_height; x++) {
            sendData(black_byte);
        }
      }
    
    sendCommand(0x26);   // Write RAM for red(1)/white (0)
    for(y = 0; y < panel_width; y++) {
        for(x=0; x < panel_height; x++) {
            sendData(red_byte);
        }
      }
    update();
    wait();
}



// Allocate and Deallocate dynamic memory for graphics operations
void QYEG0213RWS800::grabPageMemory() {
    page_black = new uint8_t[page_bytecount];
    page_red = new uint8_t[page_bytecount];
}

void QYEG0213RWS800::freePageMemory() {
    delete[] page_black;
    delete[] page_red;
}

// Interface directly with display
// -----------------------------------

void QYEG0213RWS800::sendCommand(uint8_t command) {
    SPI.beginTransaction(spi_settings);
    digitalWrite(pin_dc, LOW);  // Data-Command pin LOW, tell PanelHardware this SPI transfer is a command
    digitalWrite(pin_cs, LOW);

    SPI.transfer(command);

    digitalWrite(pin_cs, HIGH);
    SPI.endTransaction();
}

void QYEG0213RWS800::sendData(uint8_t data) {
    SPI.beginTransaction(spi_settings);
    digitalWrite(pin_dc, HIGH); // Data-Command pin HIGH, tell PanelHardware this SPI transfer is data
    digitalWrite(pin_cs, LOW);

    SPI.transfer(data);

    digitalWrite(pin_cs, HIGH);
    SPI.endTransaction();
}

/// Wake the PanelHardware from sleep mode, so it can be changed
void QYEG0213RWS800::reset() {
    // A lot of this is over my head.
    // Info from the display datasheets, and the official Heltec Driver

    wait();

    // Technical settings. Released by Heltec.
    // -------------------------------------------------------

    sendCommand(0x12); // Software Reset
    wait();

    sendCommand(0x74); // "Analog Block Control"
    sendData(0x54);
    sendCommand(0x7E); // "Digital Block Control"
    sendData(0x3B);

    sendCommand(0x01); // "Driver output control" 
    sendData(0xF9);
    sendData(0x00);
    sendData(0x00);

    sendCommand(0x3C); // "Border Waveform"
    sendData(0x01); 

      sendCommand(0x18);    // "Use internal temperature sensor"
    sendData(0x80); 

    wait();
}

/// Reset the Panel Hardware
void QYEG0213RWS800::wait() {
    while(digitalRead(pin_busy) == HIGH)    {   // Low = idle   
        delay(1);
    }
}

void QYEG0213RWS800::writePage() {
    // Calculate the memory location (in the Display Controller IC), for this particular display segment (page) we are about to transmit. 

    int16_t sx, sy, ex, ey;

    sx = (winrot_left / 8) + 1;     // I don't understand why this is +1, but it seems necessary, and the official Heltec driver also does this.
    ex = ((winrot_right) / 8) + 1;
    sy = page_top;
    ey = page_bottom;

    // Data entry mode - Right to Left, Top to Bottom
    sendCommand(0x11);
      sendData(0x03);

    // Inform the panel hardware of our chosen memory location
    sendCommand(0x44);  // Memory X start - end
    sendData(sx);
    sendData(ex);
    sendCommand(0x45);  // Memory Y start - end
    sendData(sy);
    sendData(0);        // NB: Controller accepts Y values > 256, but this panel is small, so second byte is always 0
    sendData(ey);
    sendData(0);                                        
    sendCommand(0x4E);  // Memory cursor X
    sendData(sx);
    sendCommand(0x4F);  // Memory cursor y
    sendData(sy);
    sendData(0);                                        

    // Now we can send over our image data
    sendCommand(0x24);   // Write memory for black(0)/white (1)
    for (uint16_t i = 0; i < pagefile_length; i++) {
        sendData(page_black[i]);
    }

    sendCommand(0x26);   // Write memory for red(1)/white (0)
    for (uint16_t i = 0; i < pagefile_length; i++) {
        sendData(page_red[i]);
    }

    wait();
    // Nothing happens now until update() is called
}


/// Draw the image in PanelHardware's memory to the screen
void QYEG0213RWS800::update() {
    sendCommand(0x22);
    sendData(0xF7);
    sendCommand(0x20);

    wait(); // Block while the command runs
}

/// Set the panel to an ultra low power state. Only way to exit is to cycle power to VCC.
void QYEG0213RWS800::deepSleep(uint16_t pause) {
    sendCommand(0x10);
    sendData(0x01);
    delay(pause);
}