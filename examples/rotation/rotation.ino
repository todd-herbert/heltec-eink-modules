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


// DEMO: setRotation() printing text different orientations
// --------------------------------------------------------

    // For the sake of readability, orientation can be set with either an integer, or in reference to the "header pins" on the panel:
    //      display.orientation.PINS_ABOVE = 0
    //      display.orientation.PINS_LEFT  = 1
    //      display.orientation.PINS_BELOW = 2
    //      display.orientation.PINS_RIGHT = 3


void setup() {
    display.setTextSize(1);

    while( display.calculating() ) {
        
        display.setRotation(display.orientation.PINS_ABOVE);
        display.setCursor(10, 10);
        display.print("Pins Above (0)");

        display.setRotation(display.orientation.PINS_LEFT);
        display.setCursor(10, 10);
        display.print("Pins Left (1)");

        display.setRotation(display.orientation.PINS_BELOW);
        display.setCursor(10, 10);
        display.print("Pins Below (2)");

        display.setRotation(3); // display.orientation.PINS_RIGHT
        display.setCursor(10, 10);
        display.print("Pins on Right (3)");
        
    }

    display.update();   // The display will only begin to change once update() is called
}

void loop() { }
