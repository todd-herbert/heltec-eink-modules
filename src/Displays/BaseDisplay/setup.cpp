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

    // Set an initial configuration for drawing
    // Moved from begin(), as "auto-begin" call would overwrite any config by user before first update
    setDefaultColor(WHITE);
    setTextColor(BLACK);
}        


void BaseDisplay::begin() {

    // Only begin() once
    if (begun)
        return;
    else
        begun = true;

    // Set the digital pins that supplement the SPI interface
    pinMode(pin_cs, OUTPUT);
    pinMode(pin_dc, OUTPUT);
    pinMode(pin_busy, INPUT);       // NOTE: do not use internal pullups: incompatible logic levels

    // Prepare SPI
    digitalWrite(pin_cs, HIGH);
    SPI_BEGIN();

    // SAMD21: change SPI pins if requested
    #ifdef __SAMD21G18A__
        if (pin_sdi != DEFAULT_SDI || pin_clk != DEFAULT_CLK)
            pin_miso = Platform::setSPIPins(pin_sdi, pin_clk);
    #endif

    // Calculate pagefile size
    pagefile_height = constrain(pagefile_height, 1, MAX_PAGE_HEIGHT);
    page_bytecount = panel_width * pagefile_height / 8;

    // If PRESERVE_IMAGE possible, and enabled, allocate the memory now (it will not allocate in calculating)
    if (PRESERVE_IMAGE && pagefile_height == panel_height) {
        grabPageMemory();
        fullscreen();   // Window change, clears page
        writePage();    // Make sure display memory is also blanked
    }
    // Otherwise, just set the region
    else 
        fullscreen();
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

// Get the Bounds() subclass ready early, so it can be used to initialize globals
void BaseDisplay::instantiateBounds() {
    
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
}