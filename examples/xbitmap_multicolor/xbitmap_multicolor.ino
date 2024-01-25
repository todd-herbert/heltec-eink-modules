#include <heltec-eink-modules.h>

// Find your wiring  -  https://github.com/todd-herbert/heltec-eink-modules#wiring
// ----------------

    #define PIN_DC      2
    #define PIN_CS      4
    #define PIN_BUSY    5


// Pick your panel  -  https://github.com/todd-herbert/heltec-eink-modules#supported-displays
// ---------------

    // (Only supported panels with 3-color are shown)

    DEPG0213RWS800 display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.13" - 3 Color Red
    // QYEG0213RWS800 display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.13" - 3 Color Red


// DEMO: Multicolor XBitmap Images
// -------------------------------

// XBitmap is an old image file format from the early days of the internet
// It was very inefficient as the image data was stored more or less as human readable C code
// This, however, serves our purposes very well. As such, Adafruit have chosen to add support for XBM images
// These can be easily created with the free GIMP software.

// The process of creating these images (especially multicolored) is a little bit involved.
// Please see the tutorial at:

// https://github.com/todd-herbert/heltec-eink-modules/blob/main/docs/XBitmapTutorial/README.md


// Here we are including the two (slightly modified) xbm files that we created earlier, one for each of our display's colors.
#include "apples_black_250x122.h"
#include "apples_red_250x122.h"

void setup() {
    display.setRotation(PINS_LEFT);   // Don't forget to set the rotation, so your image fits how you intended

    DRAW (display) {
        // Draw each image to its destination color
        display.drawXBitmap(0, 0, apples_black_bits, apples_black_width, apples_black_height, BLACK);
        display.drawXBitmap(0, 0, apples_red_bits, apples_red_width, apples_red_height, RED);
    }

}

void loop() {

}