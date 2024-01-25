#include <heltec-eink-modules.h>

// Find your wiring  -  https://github.com/todd-herbert/heltec-eink-modules#wiring
// ----------------

    #define PIN_DC      2
    #define PIN_CS      4
    #define PIN_BUSY    5

    // "Wireless Paper" boards: skip this, your wiring is pre-set


// Pick your panel  -  https://github.com/todd-herbert/heltec-eink-modules#supported-displays
// ---------------

    // -- SPI Displays --

    // DEPG0150BNS810 display( PIN_DC, PIN_CS, PIN_BUSY );      // 1.54" - Mono 
    // DEPG0154BNS800 display( PIN_DC, PIN_CS, PIN_BUSY);       // 1.54" - Mono 
    // GDEP015OC1 display( PIN_DC, PIN_CS, PIN_BUSY);           // 1.54" - Mono 
    // DEPG0213RWS800 display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.13" - 3 Color Red
    // QYEG0213RWS800 display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.13" - 3 Color Red
    // DEPG0290BNS75A display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.9"  - Mono 
    // DEPG0290BNS800 display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.9"  - Mono 
    // GDE029A1 display( PIN_DC, PIN_CS, PIN_BUSY );            // 2.9"  - Mono 

    // -- "Wireless Paper" --

    // DEPG0213BNS800 display;      // (Red Tab)
    // LCMEN2R13EFC1 display;       // (Green Tab)


// DEMO: Window
// --------------
// It is possible to redraw only a portion of the display, without disturbing the existing image
// This is particularly relevant when using the DRAW() loop, instead of update()


const char lorem[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. " 
                        "Suspendisse massa dui, rhoncus id varius faucibus, tempor quis nulla.";

// Shortcuts to save typing
FullBounds f = display.bounds.full;
WindowBounds w = display.bounds.window;

void setup() {

    // Lay down a background first - big wall of text
    // -----------------------------------------------
    display.setRotation(PINS_ABOVE);

    DRAW (display) {
        display.setCursor(0, 0);

        for(int i = 0; i<10; i++)
            display.print(lorem);
    }

    delay(1000);  // Pause for dramatic effect


    // Draw to only a small "window" of the display, leaving the rest undisturbed
    // ----------------------------------------------------------------------------

    const char proclamation[] = "Behold the window";
    display.setRotation(PINS_RIGHT);    // Set rotation before window dimensions
    
    // Pre-calculate window dimensions
    unsigned int W_LEFT = f.centerX() - (display.getTextWidth(proclamation) / 2) - 10;
    unsigned int W_TOP = 16;
    unsigned int W_WIDTH = display.getTextWidth(proclamation) + 20;
    unsigned int W_HEIGHT = display.getTextHeight(proclamation) + 20;

    // Set the window
    display.setWindow(W_LEFT, W_TOP, W_WIDTH, W_HEIGHT);

    // Pre-calculate text position
    unsigned int TEXT_X = display.getTextCenterX(proclamation);     // Position the text after setWindow,
    unsigned int TEXT_Y = display.getTextCenterY(proclamation);     // so we can find the *true* center

    DRAW (display)
    {
        display.drawRect(w.left(), w.top(), w.width(), w.height(), BLACK);  // Put a border around the very edge of the window
        display.setCursor(TEXT_X, TEXT_Y);
        display.print(proclamation);
    }

    delay(1000);  // Dramatic.. PAUSE

    // Draw another window, just to really make a point
    // ------------------------------------------------
    
    // Load the window xbm image
    #include "window_cartoon.h"

    // Pre-calculate the new window dimensions
    W_LEFT = f.centerX() - (window_cartoon_width / 2);
    W_TOP = f.centerY() - (window_cartoon_height / 2);
    W_WIDTH = window_cartoon_width;
    W_HEIGHT = window_cartoon_height;

    // Set the new window
    display.setWindow(W_LEFT, W_TOP, W_WIDTH, W_HEIGHT);

    DRAW (display)
    {
        // Note the small gap between the border we draw, and the image which SHOULD fill the space
        // This is a hardware limitation of the display
        // Window regions must have a horizontal dimension which is a multiple of 8 (because bits -> bytes blah blah)
        display.drawRect(w.left(), w.top(), w.width(), w.height(), BLACK);  // Put a border around the very edge of the window

        display.drawXBitmap(    w.centerX() - (window_cartoon_width / 2),   // Left
                                w.centerY() - (window_cartoon_height / 2),  // Top
                                window_cartoon_bits,                        // Image data
                                window_cartoon_width,                       // Width, set in window_cartoon.h
                                window_cartoon_height,                      // Height, set in window_cartoon.h
                                BLACK   );                                  // Color of image data
    }

}

void loop() {
    
}
