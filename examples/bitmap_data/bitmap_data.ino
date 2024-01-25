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
    #define     PENCILS_H           "pencils_200x200.h"
#elif   defined USING_DEPG0154BNS800
    #define     DISPLAY_CLASS       DEPG0154BNS800
    #define     PENCILS_H           "pencils_152x152.h"
#elif   defined USING_GDEP015OC1
    #define     DISPLAY_CLASS       GDEP015OC1
    #define     PENCILS_H           "pencils_200x200.h"
#elif   defined USING_DEPG0213RWS800
    #define     DISPLAY_CLASS       QYEG0213RWS800    
    #define     PENCILS_H           "pencils_250x122.h"    
#elif   defined USING_QYEG0213RWS800
    #define     DISPLAY_CLASS       QYEG0213RWS800    
    #define     PENCILS_H           "pencils_250x122.h"
#elif   defined USING_DEPG0290BNS75A
    #define     DISPLAY_CLASS       DEPG0290BNS75A    
    #define     PENCILS_H           "pencils_296x128.h"
#elif   defined USING_DEPG0290BNS800
    #define     DISPLAY_CLASS       DEPG0290BNS800   
    #define     PENCILS_H           "pencils_296x128.h"
#elif   defined USING_GDE029A1
    #define     DISPLAY_CLASS       GDE029A1    
    #define     PENCILS_H           "pencils_296x128.h"
#elif   defined USING_DEPG0213BNS800
    #define     DISPLAY_CLASS       DEPG0213BNS800
    #define     PENCILS_H           "pencils_250x122.h"
#elif   defined USING_LCMEN2R13EFC1
    #define     DISPLAY_CLASS       LCMEN2R13EFC1  
    #define     PENCILS_H           "pencils_250x122.h"  
#endif


// DEMO: Bitmap Data
// -----------------
// You may sometime have the need to draw raw bitmap data to the screen
// This is is possible with drawBitmap()
// One possible application here is that drawBitmap accepts data from SRAM, where as drawXBitmap will only draw from PROGMEM


#include <heltec-eink-modules.h>

// Sample set of raw bitmap data
#include PENCILS_H


// Create the display
// (Example auto-picks correct style)

#ifdef WIRELESS_PAPER
    // For "Wireless Paper" boards, no need to set pins.
    DISPLAY_CLASS display;
#else
    // For SPI displays, you would normally set your pins here
    DISPLAY_CLASS display(DC_PIN, CS_PIN, BUSY_PIN);
#endif


void setup() {
    display.setRotation(PINS_LEFT);   // Don't forget to set the correct rotation, so your image fits how you intended

    // Bitmap image data comes in all sorts of weird formats. 
    // To get it to work, you might have to play with the settings.

    display.setFlip(NONE);                  // If your image comes out flipped, change this
    display.setBackgroundColor(BLACK);      // If you get a negative of your image, try setting the background to black, and drawing the data as white

    DRAW (display) {
        display.drawBitmap(0, 0, pencils, pencils_width, pencils_height, WHITE);
    }

}

void loop() {
    
}



// "That was confusing!"
// Okay, look, here it is without all the tricky stuff to get the example to run with different displays

/*

#include <heltec-eink-modules.h>
#include "pencils_200x200.h"

DEPGDEPG0150BNS810 display(2, 4, 5);

void setup() {

    // Options to suit our bitmap data
    display.setRotation(PINS_LEFT);
    display.setFlip(NONE);            
    display.setBackgroundColor(BLACK);

    DRAW (display) {
        display.drawBitmap(0, 0, pencils, pencils_width, pencils_height, WHITE);
    }
}

void loop() {}

*/