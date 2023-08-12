#include "heltec-eink-modules.h"

// Define your pins:
// ------------------

// ( DO NOT connect pins directly to display )
// See https://github.com/todd-herbert/heltec-eink-modules#wiring

    #define PIN_BUSY    7
    #define PIN_CS      10
    #define PIN_DC      8


// Pick your panel  -   https://github.com/todd-herbert/heltec-eink-modules#supported-displays
// ---------------

    // DEPG0150BNS810 display( PIN_DC, PIN_CS, PIN_BUSY );      // 1.54" V2 - BW - Red Tab
    // DEPG0154BNS800 display( PIN_DC, PIN_CS, PIN_BUSY);       // 1.54" V2 - BW - Red Tab
    // GDEP015OC1 display( PIN_DC, PIN_CS, PIN_BUSY);           // 1.54" V2 - BW - Blue Tab
    // DEPG0213RWS800 display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.13" V2 - BWR - Red Tab
    // QYEG0213RWS800 display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.13" V2 - BWR - Red Tab
    // DEPG0290BNS75A display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.9"  V2 - BW - Red Tab
    // DEPG0290BNS800 display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.9"  V2 - BW - Red Tab
    // GDE029A1 display( PIN_DC, PIN_CS, PIN_BUSY );            // 2.9"  V2 - BW - Blue Tab


// DEMO: setFlip()
// --------------------------------------------------------

void setup() {

    // A bit of prep work: Draw the "dashed line" background
    // ------------------------------------------------------
    static const int DASH_LENGTH = 10;
    display.setRotation(display.orientation.PINS_LEFT);

    while( display.calculating() ) {

        // Step from left to right, drawing dashes
        for(unsigned int x = 0; x < display.bounds.full.width(); x += DASH_LENGTH * 2)
            display.drawLine(   x,
                                display.bounds.full.centerY(),
                                x + (DASH_LENGTH -1),
                                display.bounds.full.centerY(),
                                display.colors.BLACK );

        // Step from top to bottom, drawing dashes
        for(unsigned int y = 0; y < display.bounds.full.height(); y += DASH_LENGTH * 2)
            display.drawLine(   display.bounds.full.centerX(),
                                y,
                                display.bounds.full.centerX(),
                                y + (DASH_LENGTH - 1),
                                display.colors.BLACK    );                            
    }

    // Draw the "dashed line" background onto the display
    display.update();
    

    // Draw the first box
    // ------------------------------------------------

    // By default, no flip
    // display.setFlip(display.flip.NONE);

    display.setWindow(10, 10, 80, 20);

    while( display.calculating() ) {
        // Draw a border around the window
        display.drawRect(   display.bounds.window.left(), 
                            display.bounds.window.top(), 
                            display.bounds.window.width(), 
                            display.bounds.window.height(),
                            display.colors.BLACK    );

        // Some text for reference
        display.setCursor(  display.bounds.window.left() + 3,
                            display.bounds.window.top() + 13 );
        
        display.print(".OFF");
    }
    display.update();   // Draw the first box top left
    delay(2000);


    // Flip the box horizontal
    // -----------------------------------------

    display.setFlip(display.flip.HORIZONTAL);
    display.setWindow(10, 10, 80, 20);          // Re-set your window after changing flip
    while( display.calculating() ) {
        // Draw a border around the window
        display.drawRect(   display.bounds.window.left(), 
                            display.bounds.window.top(), 
                            display.bounds.window.width(), 
                            display.bounds.window.height(),
                            display.colors.BLACK    );

        // Some text for reference
        display.setCursor(  display.bounds.window.left() + 3,
                            display.bounds.window.top() + 13 );
        
        display.print(".HORIZONTAL");
    }
    display.update();
    delay(2000);


    // Flip the box vertical
    // ------------------------------------------

    display.setFlip(display.flip.VERTICAL);
    display.setWindow(10, 10, 80, 20);          // Re-set your window after changing flip
    while( display.calculating() ) {
        // Draw a border around the window
        display.drawRect(   display.bounds.window.left(), 
                            display.bounds.window.top(), 
                            display.bounds.window.width(), 
                            display.bounds.window.height(),
                            display.colors.BLACK    );

        // Some text for reference
        display.setCursor(  display.bounds.window.left() + 3,
                            display.bounds.window.top() + 13 );
        
        display.print(".VERTICAL");
    }
    display.update();
    delay(2000);

}

void loop() { }
