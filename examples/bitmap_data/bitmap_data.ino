// Pick your panel  -  https://github.com/todd-herbert/heltec-eink-modules
// ---------------

    // All-in-one boards
    // ---------------------------------------

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


// DEMO: Bitmap Data
// -----------------
// It is generally easier to work with XBitmaps, than with raw bitmap data
// *however*, you may sometime need to use raw bitmap data (this example)
// This is is possible with drawBitmap()
// One possible application here is that drawBitmap accepts data from SRAM, where as drawXBitmap will only draw from PROGMEM

#include <heltec-eink-modules.h>
#include "example_resources.h"

// Sample set of raw bitmap data
#include PENCILS_H

// Create the display
// (Example auto-picks correct style)

#if ALL_IN_ONE
    // For "Wireless Paper" and "Vision Master" boards, no need to set pins.
    DISPLAY_CLASS display;
#else
    // For SPI displays, you would normally set your pins here
    DISPLAY_CLASS display(PIN_DC, PIN_CS, PIN_BUSY);
#endif

// Instead of all this "auto-picking" stuff:
//  #include "pencils_200x200.h"
//  DEPG0150BNS810 display(2, 4, 5);    // Pins for DC, CS, BUSY


void setup() {
    display.setRotation(90);   // Don't forget to set the correct rotation, so your image fits how you intended

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

DEPG0150BNS810 display(2, 4, 5);

void setup() {

    // Options to suit our bitmap data
    display.setRotation(90);
    display.setFlip(NONE);            
    display.setBackgroundColor(BLACK);

    DRAW (display) {
        display.drawBitmap(0, 0, pencils, pencils_width, pencils_height, WHITE);
    }
}

void loop() {}

*/