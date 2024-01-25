// Pick your panel  -  https://github.com/todd-herbert/heltec-eink-modules#supported-displays
// ---------------

    // -- SPI Displays --

    // #define  USING_DEPG0150BNS810        // 1.54" - Mono 
    // #define  USING_DEPG0154BNS800        // 1.54" - Mono 
    // #define  USING_GDEP015OC1            // 1.54" - Mono 
    // #define  USING_DEPG0213RWS800        // 2.13" - 3 Color Red
    // #define  USING_QYEG0213RWS800        // 2.13" - 3 Color Red
    // #define  USING_DEPG0290BNS75A        // 2.9"  - Mono 
    // #define  USING_DEPG0290BNS800        // 2.9"  - Mono 
    // #define  USING_GDE029A1              // 2.9"  - Mono 

    // -- "Wireless Paper" --

    // #define USING_DEPG0213BNS800         // (Red Tab)
    // #define USING_LCMEN2R13EFC1          // (Green Tab)


// Find your wiring  -  https://github.com/todd-herbert/heltec-eink-modules#wiring
// ----------------

    #define DC_PIN 2
    #define CS_PIN 4
    #define BUSY_PIN 5

    // "Wireless Paper" boards: skip this, your wiring is pre-set


// (Example automatically picks the correct class and sample image)
#if     defined USING_DEPG0150BNS810
    #define     DISPLAY_CLASS       DEPG0150BNS810    
    #define     CHESS_H             "chess_200x200.h"
#elif   defined USING_DEPG0154BNS800
    #define     DISPLAY_CLASS       DEPG0154BNS800
    #define     CHESS_H             "chess_152x152.h"
#elif   defined USING_GDEP015OC1
    #define     DISPLAY_CLASS       GDEP015OC1
    #define     CHESS_H             "chess_200x200.h"
#elif   defined USING_DEPG0213RWS800
    #define     DISPLAY_CLASS       QYEG0213RWS800    
    #define     CHESS_H             "chess_250x122.h"    
#elif   defined USING_QYEG0213RWS800
    #define     DISPLAY_CLASS       QYEG0213RWS800    
    #define     CHESS_H             "chess_250x122.h"
#elif   defined USING_DEPG0290BNS75A
    #define     DISPLAY_CLASS       DEPG0290BNS75A    
    #define     CHESS_H             "chess_296x128.h"
#elif   defined USING_DEPG0290BNS800
    #define     DISPLAY_CLASS       DEPG0290BNS800   
    #define     CHESS_H             "chess_296x128.h"
#elif   defined USING_GDE029A1
    #define     DISPLAY_CLASS       GDE029A1    
    #define     CHESS_H             "chess_296x128.h"
#elif   defined USING_DEPG0213BNS800
    #define     DISPLAY_CLASS       DEPG0213BNS800
    #define     CHESS_H             "chess_250x122.h"
#elif   defined USING_LCMEN2R13EFC1
    #define     DISPLAY_CLASS       LCMEN2R13EFC1  
    #define     CHESS_H             "chess_250x122.h"  
#endif


// DEMO: Black & White XBitmap Images
// -------------------------------------

// XBitmap is an old image file format from the early days of the internet
// It was very inefficient as the imagedata was stored more or less as human readable C code
// This, however, serves our purposes very well. As such, Adafruit have chosen to add support for XBM images
// These can be easily created with the free GIMP software.

// The process of creating these images is a little bit involved.
// Please see the tutorial at:

// https://github.com/todd-herbert/heltec-eink-modules/blob/main/docs/XBitmapTutorial/README.md


#include "heltec-eink-modules.h"

// Here we are including the xbm image file (chess.h or similar). 
// In this example, for convenience, an appropriate image for you display has been automatically selected. (See above)
#include CHESS_H

DISPLAY_CLASS display(DC_PIN, CS_PIN, BUSY_PIN);

void setup() {
    display.setRotation(PINS_LEFT);   // Don't forget to set the rotation, so your image fits how you intended

    DRAW (display) {
        display.drawXBitmap(0, 0, chess_bits, chess_width, chess_height, BLACK);
    }
}

void loop() {

}