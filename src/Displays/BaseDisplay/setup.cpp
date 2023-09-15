/* 
    File: setup.cpp

        - Constructor, init, setup methods
*/

#include "base.h"

BaseDisplay::BaseDisplay(   uint8_t pin_dc, 
                            uint8_t pin_cs, 
                            uint8_t pin_busy, 
                            uint8_t pin_sdi, 
                            uint8_t pin_clk, 
                            int16_t page_height ) 
                                                : GFX(0, 0)                   
{
    // Store config from the derived class
    this->pin_dc = pin_dc;
    this->pin_cs = pin_cs;
    this->pin_busy = pin_busy;
    this->pin_sdi = pin_sdi;
    this->pin_clk = pin_clk;
    this->pagefile_height = page_height;
}        


void BaseDisplay::init() {

    // We lied to GFX about dimensions in the constructor, but now we do have the information.
    // I'm not sure it matters, but..

    _width = WIDTH = drawing_width;
    _height = HEIGHT = drawing_height;

    // Instantiate the "Bounds" subclass system, and pass references
    this->bounds = Bounds(  drawing_width,
                            drawing_height,
                            &winrot_top, 
                            &winrot_right, 
                            &winrot_bottom, 
                            &winrot_left, 
                            &rotation,
                            &imgflip    );

    // Set the digital pins that supplement the SPI interface
    pinMode(pin_cs, OUTPUT);
    pinMode(pin_dc, OUTPUT);
    pinMode(pin_busy, INPUT);       // NOTE: do not use internal pullups: incompatible logic levels
    
    // Prepare SPI
    digitalWrite(pin_cs, HIGH);
    #if !LATE_INIT
        SPI_BEGIN();
    #endif    

    // Calculate pagefile size
    pagefile_height = constrain(pagefile_height, 1, MAX_PAGE_HEIGHT);
    page_bytecount = panel_width * pagefile_height / 8;

    // Set an initial configuration for drawing
    setDefaultColor(WHITE);
    setTextColor(BLACK);

    // If PRESERVE_IMAGE, allocate the memory now (it will not allocate in calculating)
    #if PRESERVE_IMAGE
        grabPageMemory();
        fullscreen();   // Window change, clears page

        // SAMD21 can't call SPI.begin from a constructor. See BaseDisplay::lateInit()
        #if LATE_INIT
            return;
        #endif

        writePage();    // Make sure display memory is also blanked
        init_done = true;
    #else
        // Otherwise, just set the region
        fullscreen();
    #endif
}

// Same platforms won't run SPI commands from constructor. This method is called later to finish the job.
void BaseDisplay::lateInit() {

    // Start SPI and clear display mem
    if (!init_done) {
        SPI.begin();
        init_done = true;
        
        // SAMD21: change SPI pins if requested
        #ifdef __SAMD21G18A__
            if (pin_sdi != DEFAULT_SDI && pin_clk != DEFAULT_CLK)
                PinMux().setSPIPins(pin_sdi, pin_clk);
        #endif
        
        // After all that, clear the display memory
        writePage();
    }
}

// Set configuration of custom power-swiching circuit, then power up
void BaseDisplay::usePowerSwitching(uint8_t pin, SwitchType type) {
    this->pin_power = pin;
    this->switch_type = type;

    // Start powered up
    delay(50);
    pinMode(pin_power, OUTPUT);
    digitalWrite(pin_power, switch_type);

    // Wait for powerup
    delay(100);
}