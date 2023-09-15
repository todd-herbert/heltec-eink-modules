#include "heltec-eink-modules.h"

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


// DEMO: setRotation()
// --------------------------------------------------------

    // For the sake of readability, rotation can be set with either an integer, or in reference to the "header pins" on the panel:
    //      PINS_ABOVE = 0
    //      PINS_LEFT  = 1
    //      PINS_BELOW = 2
    //      PINS_RIGHT = 3


void setup() {

    DRAW (display) {
        
        display.setRotation(PINS_ABOVE);
        display.setCursor(10, 10);
        display.print("Pins Above (0)");

        display.setRotation(PINS_LEFT);
        display.setCursor(10, 10);
        display.print("Pins Left (1)");

        display.setRotation(PINS_BELOW);
        display.setCursor(10, 10);
        display.print("Pins Below (2)");

        display.setRotation(3);         // PINS_RIGHT
        display.setCursor(10, 10);
        display.print("Pins on Right (3)");
        
    }

}

void loop() { }
