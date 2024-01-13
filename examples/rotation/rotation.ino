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
// setRotation() will accept several different types of value
// It can be called before DRAW(), or during, with different effect.


void setup() {

    // Option 1: degrees

    DRAW (display) {       
        display.setRotation(0);             // 0 degrees (clockwise)
        display.setCursor(10, 10);
        display.print("0");

        display.setRotation(90);            // 90 degrees (clockwise)
        display.setCursor(10, 10);
        display.print("90");

        display.setRotation(180);           // 180 degrees
        display.setCursor(10, 10);
        display.print("180");

        display.setRotation(270);           // 270 degrees (clockwise)
        display.setCursor(10, 10);
        display.print("270");
    }

    delay(4000);    // Let user read the display


    // Option 2: clockwise turns

    DRAW (display) {       
        display.setRotation(0);             // No turn
        display.setCursor(10, 10);
        display.print("0");

        display.setRotation(1);             // 1 turn (90 deg. clockwise)
        display.setCursor(10, 10);
        display.print("1");

        display.setRotation(2);             // 2 turns (180 deg.)
        display.setCursor(10, 10);
        display.print("2");

        display.setRotation(3);             // 3 turns (270 deg.)
        display.setCursor(10, 10);
        display.print("3");
    }

    delay(4000);    // Let user read the display


    // Option 3: negatives

    DRAW (display) {       
        display.setRotation(0);             // No rotation
        display.setCursor(10, 10);
        display.print("0");

        display.setRotation(-90);           // 90 degrees counter-clockwise
        display.setCursor(10, 10);
        display.print("-90");

        display.setRotation(2);             // -180 degrees..
        display.setCursor(10, 10);
        display.print("-180");

        display.setRotation(-3);             // 3 turns counter-clockwise
        display.setCursor(10, 10);
        display.print("-3 turns");
    }

    delay(4000);    // Let user read the display


    // Option 4: landscape() and portrait() -  for the lazy

    DRAW (display) {       
        display.landscape();                // landscape()
        display.setCursor(10, 10);
        display.print("landscape()");

        display.portrait();                 // portrait()
        display.setCursor(10, 10);
        display.print("portrait()");
    }

    delay(4000);    // Let user read the display


    // If you are using a "Wireless Paper" all-in-one board:
    #ifdef WIRELESS_PAPER

        // Option 5: relative to Wireless Paper's USB port
        DRAW (display) {       
            display.setRotation(USB_ABOVE);     // Orient so that USB port is above the display
            display.setCursor(10, 10);
            display.print("USB_ABOVE");

            display.setRotation(USB_LEFT);      // Orient so that USB port is to left of the display
            display.setCursor(10, 10);
            display.print("USB_LEFT");

            display.setRotation(USB_BELOW);     // Orient so that USB port is below the display
            display.setCursor(10, 10);
            display.print("USB_BELOW");

            display.setRotation(USB_RIGHT);     // Orient so that USB port is to right of the display
            display.setCursor(10, 10);
            display.print("USB_RIGHT");
        }

    
    // If you are using a "Display Module"
    #else

        // Option 5: relative to display module's header pins
        DRAW (display) {       
            display.setRotation(PINS_ABOVE);    // Orient so that header pins are above the display
            display.setCursor(10, 10);
            display.print("PINS_ABOVE");

            display.setRotation(PINS_LEFT);     // Orient so that header pins are to left of the display
            display.setCursor(10, 10);
            display.print("PINS_LEFT");

            display.setRotation(PINS_BELOW);    // Orient so that header pins are below the display
            display.setCursor(10, 10);
            display.print("PINS_BELOW");

            display.setRotation(PINS_RIGHT);    // Orient so that header pins are to right of the display
            display.setCursor(10, 10);
            display.print("PINS_RIGHT");
        }

    #endif


}

void loop() { }
