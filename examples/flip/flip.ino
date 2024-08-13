#include <heltec-eink-modules.h>

// Pick your panel  -  https://github.com/todd-herbert/heltec-eink-modules
// ---------------

    // "All-in-one" boards
    // --------------------------------------

        // EInkDisplay_WirelessPaperV1 display;
        // EInkDisplay_WirelessPaperV1_1 display
        // EInkDisplay_VisionMasterE213 display;
        // EInkDisplay_VisionMasterE290 display;


    // SPI Displays
    // --------------------------------------

        // Wiring (SPI Displays only)
        #define PIN_DC   2
        #define PIN_CS   4
        #define PIN_BUSY 5

        // DEPG0150BNS810 display( PIN_DC, PIN_CS, PIN_BUSY );      // 1.54" - Mono 
        // DEPG0154BNS800 display( PIN_DC, PIN_CS, PIN_BUSY);       // 1.54" - Mono 
        // GDEP015OC1 display( PIN_DC, PIN_CS, PIN_BUSY);           // 1.54" - Mono 
        // DEPG0213RWS800 display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.13" - 3 Color Red
        // QYEG0213RWS800 display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.13" - 3 Color Red
        // DEPG0290BNS75A display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.9"  - Mono 
        // DEPG0290BNS800 display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.9"  - Mono 
        // GDE029A1 display( PIN_DC, PIN_CS, PIN_BUSY );            // 2.9"  - Mono 


// DEMO: setFlip()
// --------------------------------------------------------

void setup() {

    // A bit of prep work: Draw the "dashed line" background
    // ------------------------------------------------------
    int DASH_LENGTH = 10;
    display.setRotation(90);

    DRAW (display) {

        // Step from left to right, drawing dashes
        for(unsigned int x = 0; x < display.width(); x += DASH_LENGTH * 2)

            display.drawLine(   x,                                  // dash, left point
                                display.centerY(),      // (midscreen y)
                                x + (DASH_LENGTH -1),               // dash, right point
                                display.centerY(),      // (midscreen y)
                                BLACK   );

        // Step from top to bottom, drawing dashes
        for(unsigned int y = 0; y < display.height(); y += DASH_LENGTH * 2)

            display.drawLine(   display.centerX(),      // (midscreen x)
                                y,                                  // dash, top point
                                display.centerX(),      // (midscreen x)
                                y + (DASH_LENGTH - 1),              // dash, bottom point
                                BLACK   );   

        // End of DRAW(), display will update now
    }

    

    // Draw the first box
    // ------------------------------------------------

    // By default, no flip
    // display.setFlip(NONE);

    display.setWindow(10, 10, 80, 24);

    DRAW (display) {
        // Draw a border around the window
        display.drawRect(   display.window.left(), 
                            display.window.top(), 
                            display.window.width(), 
                            display.window.height(),
                            BLACK   );

        // Some text for reference
        display.setCursor(  display.window.left() + 3,
                            display.window.top() + 13 );
        
        display.print("NONE");
    }

    // Pause for user to read the label
    delay(2000);


    // Flip the box horizontal
    // -----------------------------------------

    display.setFlip(HORIZONTAL);
    DRAW (display) {
        // Draw a border around the window
        display.drawRect(   display.window.left(), 
                            display.window.top(), 
                            display.window.width(), 
                            display.window.height(),
                            BLACK   );

        // Some text for reference
        display.setCursor(  display.window.left() + 3,
                            display.window.top() + 13 );
        
        display.print("HORIZONTAL");
    }

    // Pause for emphasis
    delay(2000);


    // Flip the box vertical
    // ------------------------------------------

    display.setFlip(VERTICAL);
    DRAW (display) {
        // Draw a border around the window
        display.drawRect(   display.window.left(), 
                            display.window.top(), 
                            display.window.width(), 
                            display.window.height(),
                            BLACK   );

        // Some text for reference
        display.setCursor(  display.window.left() + 3,
                            display.window.top() + 13 );
        
        display.print("VERTICAL");
    }

    // Pause for emphasis
    delay(2000);


    // Draw a new box, in middle
    // ------------------------------------------

    display.setFlip(NONE);
    display.setWindow(10, 50, 120, 24);

    DRAW (display) {
        // Draw a border around the window
        display.drawRect(   display.window.left(), 
                            display.window.top(), 
                            display.window.width(), 
                            display.window.height(),
                            BLACK   );

        // Some text for reference
        display.setCursor(  display.window.left() + 3,
                            display.window.top() + 13 );
        
        display.print("NONE");
    }

    // Pause for emphasis
    delay(2000);


    // Windowed Flip
    // ------------------------------------------

    display.setFlip(HORIZONTAL_WINDOW);

    DRAW (display) {
        // Draw a border around the window
        display.drawRect(   display.window.left(), 
                            display.window.top(), 
                            display.window.width(), 
                            display.window.height(),
                            BLACK   );

        // Some text for reference
        display.setCursor(  display.window.left() + 3,
                            display.window.top() + 13 );
        
        display.print("HORIZONTAL_WINDOW");
    }

}

void loop() {
    
}
