// Pick your panel  -  https://github.com/todd-herbert/heltec-eink-modules
// ---------------

    // All-in-one boards
        // #define USING_WIRELESSPAPER_V1
        // #define USING_WIRELESSPAPER_V1_1
        // #define USING_VISIONMASTER_E213
        // #define USING_VISIONMASTER_E290


    // SPI Displays
    // --------------------------------------

        // Wiring (SPI Displays only)
        #define PIN_DC   2
        #define PIN_CS   4
        #define PIN_BUSY 5

        // #define  USING_DEPG0150BNS810        // 1.54" - Mono 
        // #define  USING_DEPG0154BNS800        // 1.54" - Mono 
        // #define  USING_GDEP015OC1            // 1.54" - Mono 
        // #define  USING_DEPG0213RWS800        // 2.13" - 3 Color Red
        // #define  USING_QYEG0213RWS800        // 2.13" - 3 Color Red
        // #define  USING_DEPG0290BNS75A        // 2.9"  - Mono
        // #define  USING_DEPG0290BNS800        // 2.9"  - Mono
        // #define  USING_GDE029A1              // 2.9"  - Mono


// DEMO: Black & White XBitmap Images
// -------------------------------------

// XBitmap is an old image file format from the early days of the internet
// It was very inefficient as the imagedata was stored more or less as human readable C code
// This, however, serves our purposes very well. As such, Adafruit have chosen to add support for XBM images
// These can be easily created with the free GIMP software.

// The process of creating these images is a little bit involved.
// Please see the tutorial at:

// https://github.com/todd-herbert/heltec-eink-modules/blob/main/docs/XBitmapTutorial/README.md


#include <heltec-eink-modules.h>
#include "example_resources.h"

// Example auto-selects an image
#include CHESS_H

// Example auto-selects correct class
#if ALL_IN_ONE
    // For "Wireless Paper" and "Vision Master" boards, no need to set pins.
    DISPLAY_CLASS display;
#else
    // For SPI displays, you would normally set your pins here
    DISPLAY_CLASS display(PIN_DC, PIN_CS, PIN_BUSY);
#endif


void setup() {
    display.setRotation(1);   // Don't forget to set the rotation, so your image fits how you intended

    DRAW (display) {
        display.drawXBitmap(0, 0, chess_bits, chess_width, chess_height, BLACK);
    }
}

void loop() {

}

// "That was confusing!"
// Okay, look, here it is without all the tricky stuff to get the example to run with different displays

/*

#include <heltec-eink-modules.h>
#include "chess_200x200.h"

DEPG0150BNS810 display(2, 4, 5);

void setup() {

    display.setRotation(90); // Landscape
    
    DRAW (display) {
        display.drawXBitmap(0, 0, chess_bits, chess_width, chess_height, BLACK);
    }
}

void loop() {}

*/