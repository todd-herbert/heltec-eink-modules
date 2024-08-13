#include <heltec-eink-modules.h>

// Pick your panel  -  https://github.com/todd-herbert/heltec-eink-modules
// ---------------

    // "All-in-one" boards
    // --------------------------------------

        // EInkDisplay_WirelessPaperV1 display;
        // EInkDisplay_WirelessPaperV1_1 display
        // EInkDisplay_VisionMasterE213 display;
        // EInkDisplay_VisionMasterE290 display;


    // SPI Displays
    // --------------------------------------

        // Wiring (SPI Displays only)
        #define PIN_DC   2
        #define PIN_CS   4
        #define PIN_BUSY 5

        // DEPG0150BNS810 display( PIN_DC, PIN_CS, PIN_BUSY );      // 1.54" - Mono 
        // DEPG0154BNS800 display( PIN_DC, PIN_CS, PIN_BUSY);       // 1.54" - Mono 
        // GDEP015OC1 display( PIN_DC, PIN_CS, PIN_BUSY);           // 1.54" - Mono 
        // DEPG0213RWS800 display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.13" - 3 Color Red
        // QYEG0213RWS800 display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.13" - 3 Color Red
        // DEPG0290BNS75A display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.9"  - Mono 
        // DEPG0290BNS800 display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.9"  - Mono 
        // GDE029A1 display( PIN_DC, PIN_CS, PIN_BUSY );            // 2.9"  - Mono 


void setup() {
    display.setRotation(-90);     // 90 degrees counter-clockwise

    // Picks colors that will work on your panel
    // =============================================
    Color BGCOLOR;
    byte ACCENT1;       // The colors are really just bytes.
    uint8_t ACCENT2;    // (aka 8 bit numbers)

    // Demo colors for 3-Color displays
    if ( display.supportsColor(RED) ) {
        BGCOLOR = RED;
        ACCENT1 = WHITE;
        ACCENT2 = BLACK;
    }

    // Demo colors on mono displays
    else {
        BGCOLOR = BLACK;
        ACCENT1 = WHITE;
        ACCENT2 = WHITE;
    }

    // ============================================

    display.setBackgroundColor(BGCOLOR);

    DRAW (display) {
    
            display.drawRoundRect(120, 20, 80, 60, 10, ACCENT1); // Hollow
            display.fillRoundRect(130, 30, 85, 65, 10, ACCENT1); // Filled

            display.fillRect(160, 50, 30, 30, BGCOLOR); // Drawing with our background color can help "erase" things

            display.fillCircle(40, -10, 25, ACCENT2);   // Drawing out of bounds is allowed
            display.drawLine(40, -10, 300, 500, ACCENT1); // <-- !!! But don't go crazy as every pixel gets processed, even if most of them are offscreen

            display.fillTriangle(0,0, 30, display.bottom(), 60, display.bottom(), ACCENT2);  // Handy functions like bottom() make drawing easier
            display.fillCircle(display.centerX(), display.centerY(), 20 + 1, BGCOLOR);  // (draw an outline for next circle)
            display.fillCircle(display.centerX(), display.centerY(), 20, ACCENT2);  // Right in the center
    }

}

void loop() {

}
