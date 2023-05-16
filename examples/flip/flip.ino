// Which panel are you using?  (uncomment one)
// --------------------------------------------
    // #define  USING_DEPG0150BNS810        // 1.54" V2 - BW - Reb Tab
    // #define  USING_DEPG0154BNS800        // 1.54" V2 - BW - Red Tab
    // #define  USING_GDEP015OC1            // 1.54" V2 - BW - Blue Tab
    // #define  USING_QYEG0213RWS800        // 2.13" V2 - BWR - Red Tab
    // #define  USING_DEPG0290BNS75A        // 2.9" V2 - BW - Red Tab
    // #define  USING_DEPG0290BNS800        // 2.9" V2 - BW - Red Tab
    // #define  USING_HTE029A1              // 2.9" V2 - BW - Blue Tab


// Where is your panel connected?
// --------------------------------
    #define DC_PIN 8
    #define CS_PIN 10
    #define BUSY_PIN 7


// (Example automatically picks the correct class)
#if     defined USING_DEPG0150BNS810
    #define     PANEL_CLASS     DEPG0150BNS810
#elif   defined USING_DEPG0154BNS800
    #define     PANEL_CLASS     DEPG0154BNS800  
#elif   defined USING_GDEP015OC1
    #define     PANEL_CLASS     GDEP015OC1  
#elif   defined USING_QYEG0213RWS800
    #define     PANEL_CLASS     QYEG0213RWS800 
#elif   defined USING_DEPG0290BNS75A
    #define     PANEL_CLASS     DEPG0290BNS75A
#elif   defined USING_DEPG0290BNS800
    #define     PANEL_CLASS     DEPG0290BNS800       
#elif   defined USING_HTE029A1
    #define     PANEL_CLASS     HTE029A1    
#endif

// DEMO: setFlip()
// --------------------------------------------------------

#include "heltec-eink-modules.h"

PANEL_CLASS display(DC_PIN, CS_PIN, BUSY_PIN);

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
