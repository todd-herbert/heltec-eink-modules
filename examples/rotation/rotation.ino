// Which panel are you using?  (uncomment one)
// --------------------------------------------
    // #define  USING_DEPG0150BNS810        // 1.54" V2 - BW - Red Tab
    // #define  USING_DEPG0154BNS800        // 1.54" V2 - BW - Red Tab
    // #define  USING_GDEP015OC1            // 1.54" V2 - BW - Blue Tab
    // #define  USING_QYEG0213RWS800        // 2.13" V2 - BWR - Red Tab
    // #define  USING_DEPG0290BNS75A        // 2.9" V2 - BW - Red Tab
    // #define  USING_DEPG0290BNS800        // 2.9" V2 - BW - Red Tab
    // #define  USING_GDE029A1              // 2.9" V2 - BW - Blue Tab


// Where is your panel connected?
// --------------------------------
    #define DC_PIN 8
    #define CS_PIN 10
    #define BUSY_PIN 7


// (Example automatically picks the correct class)
#if     defined USING_DEPG0150BNS810
    #define     PANEL_CLASS     DEPG0150BNS810
#elif   defined USING_DEPG0154BNS800
    #define     PANEL_CLASS     DEPG0154BNS800  
#elif   defined USING_GDEP015OC1
    #define     PANEL_CLASS     GDEP015OC1  
#elif   defined USING_QYEG0213RWS800
    #define     PANEL_CLASS     QYEG0213RWS800 
#elif   defined USING_DEPG0290BNS75A
    #define     PANEL_CLASS     DEPG0290BNS75A
#elif   defined USING_DEPG0290BNS800
    #define     PANEL_CLASS     DEPG0290BNS800       
#elif   defined USING_GDE029A1
    #define     PANEL_CLASS     GDE029A1    
#endif

// DEMO: setRotation() printing text different orientations
// --------------------------------------------------------
            // For the sake of readability, orientation can be set with either an integer, or in reference to the "header pins" on the panel:
            //      display.orientation.PINS_ABOVE = 0
            //      display.orientation.PINS_LEFT  = 1
            //      display.orientation.PINS_BELOW = 2
            //      display.orientation.PINS_RIGHT = 3


#include "heltec-eink-modules.h"

PANEL_CLASS display(DC_PIN, CS_PIN, BUSY_PIN);

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

        display.setRotation(display.orientation.PINS_RIGHT);
        display.setCursor(10, 10);
        display.print("Pins on Right (3)");
        
    }

    display.update();   // The display will only begin to change once update() is called
}

void loop() { }
