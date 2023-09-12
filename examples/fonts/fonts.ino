// Pick your panel  -  https://github.com/todd-herbert/heltec-eink-modules#supported-displays
// ---------------

    // #define  USING_DEPG0150BNS810        // 1.54" V2 - BW - Red Tab
    // #define  USING_DEPG0154BNS800        // 1.54" V2 - BW - Red Tab
    // #define  USING_GDEP015OC1            // 1.54" V2 - BW - Blue Tab
    // #define  USING_DEPG0213RWS800        // 2.13" V2 - BWR - Red Tab
    // #define  USING_QYEG0213RWS800        // 2.13" V2 - BWR - Red Tab
    // #define  USING_DEPG0290BNS75A        // 2.9" V2 - BW - Red Tab
    // #define  USING_DEPG0290BNS800        // 2.9" V2 - BW - Red Tab
    // #define  USING_GDE029A1              // 2.9" V2 - BW - Blue Tab


// Find your wiring  -  https://github.com/todd-herbert/heltec-eink-modules#wiring
// ----------------

    #define DC_PIN 2
    #define CS_PIN 4
    #define BUSY_PIN 5


// (Example automatically picks the correct class and sample text)
#if     defined USING_DEPG0150BNS810
    #define     PANEL_CLASS     DEPG0150BNS810
    #define     SAMPLE_TEXT     "Fancy fonty text."
#elif   defined USING_DEPG0154BNS800
    #define     PANEL_CLASS     DEPG0154BNS800  
    #define     SAMPLE_TEXT     "Fancy font."   // Display too small
#elif   defined USING_GDEP015OC1
    #define     PANEL_CLASS     GDEP015OC1
    #define     SAMPLE_TEXT     "Fancy fonty text."  
#elif   defined USING_DEPG0213RWS800
    #define     PANEL_CLASS     DEPG0213RWS800
    #define     SAMPLE_TEXT     "Fancy fonty text."  
#elif   defined USING_QYEG0213RWS800
    #define     PANEL_CLASS     QYEG0213RWS800
    #define     SAMPLE_TEXT     "Fancy fonty text."    
#elif   defined USING_DEPG0290BNS75A
    #define     PANEL_CLASS     DEPG0290BNS75A
    #define     SAMPLE_TEXT     "Fancy fonty text."
#elif   defined USING_DEPG0290BNS800
    #define     PANEL_CLASS     DEPG0290BNS800
    #define     SAMPLE_TEXT     "Fancy fonty text."   
#elif   defined USING_GDE029A1
    #define     PANEL_CLASS     GDE029A1
    #define     SAMPLE_TEXT     "Fancy fonty text."
#endif

// DEMO: Using fonts
// ------------------

#include "heltec-eink-modules.h"

// Include the font you want from the Fonts folder. 
// They take up a bit of memory; maybe don't include them all.

#include "Fonts/FreeSerifBold12pt7b.h"

// Display instance
PANEL_CLASS display(DC_PIN, CS_PIN, BUSY_PIN);

void setup() {
    display.setRotation(PINS_LEFT);             // Landscape, text fits better that way (Header PINS to LEFT of the display)

    display.setFont( & FreeSerifBold12pt7b );   // Pass (the address of) the font to the library

    DRAW (display) {
        display.setCursor(10, 50);              // Set the (word-processor-like) cursor to the abritrary position of x=10, y=50          
        display.print(SAMPLE_TEXT);
    }   
    
    // Note: setCursor needs to run inside of the DRAW() loop.
    // This way, it is shunted to the start if the DRAW() code needs to repeat, for paging.

}

void loop() { }
