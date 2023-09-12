#include "heltec-eink-modules.h"

// -- Example will not run on Arduino Uno / Nano
// -- Example *may* run on Arduino Mega

// Find your wiring  -  https://github.com/todd-herbert/heltec-eink-modules#wiring
// ----------------

    #define PIN_DC      2
    #define PIN_CS      4
    #define PIN_BUSY    5


// Pick your panel  -  https://github.com/todd-herbert/heltec-eink-modules#supported-displays
// ---------------

    // DEPG0150BNS810 display( PIN_DC, PIN_CS, PIN_BUSY );      // 1.54" V2 - BW - Red Tab
    // DEPG0154BNS800 display( PIN_DC, PIN_CS, PIN_BUSY);       // 1.54" V2 - BW - Red Tab
    // GDEP015OC1 display( PIN_DC, PIN_CS, PIN_BUSY);           // 1.54" V2 - BW - Blue Tab
    // DEPG0213RWS800 display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.13" V2 - BWR - Red Tab
    // QYEG0213RWS800 display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.13" V2 - BWR - Red Tab
    // DEPG0290BNS75A display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.9"  V2 - BW - Red Tab
    // DEPG0290BNS800 display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.9"  V2 - BW - Red Tab
    // GDE029A1 display( PIN_DC, PIN_CS, PIN_BUSY );            // 2.9"  V2 - BW - Blue Tab


// DEMO: Overwrite
// ------------------------------------------------
    // Larger microcontrollers have enough RAM to hold the full screen image at once: they do not need paging.
    // These devices do not need to use the DRAW() loop, drawing commands can be issued almost anywhere.
    // Call overwrite() to update the display.

void setup() {

    // Print two lines of text

    display.setCursor(10, 10);
    display.print("First line.");

    display.setCursor(10, 40);
    display.print("Second line.");

    // Update the display
    display.overwrite();


    display.drawTriangle(   10, 50,     // Point 1 x, y
                            20, 5,      // Point 2 x, y
                            70, 45,     // Point 3 x, y
                            BLACK   );  // Color

    // Update the display, drawing over the last image
    display.overwrite();

}

void loop() {}
