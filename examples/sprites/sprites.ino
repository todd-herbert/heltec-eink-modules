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


// DEMO: Sprites
// -------------
    // XBitmaps are well suited for storing graphic elements that can be pre-rendered and then placed where needed


// Here we are including a small image of a ball
#include "ball.h"


void setup() {
    display.setRotation(90);

    // Useful drawing aides
    unsigned int CENTER_X   = display.centerX();
    unsigned int CENTER_Y   = display.centerY();

    unsigned int ball_offset = 53;

    DRAW (display) {
        // First draw a ball in the background, top centre
        display.drawXBitmap(    CENTER_X - (ball_width / 2),                        // Left
                                CENTER_Y - (ball_height / 2) - ball_offset,         // Top
                                ball_bits,                                          // Image Data
                                ball_width,                                         // Width
                                ball_height,                                        // Height
                                BLACK   );                                          // Color

        // ball in the bottom left
        // Note that the XBitmap only specifies location of one color. This allows transparency
        display.drawXBitmap(    CENTER_X - (ball_width / 2) - ball_offset, 
                                CENTER_Y - (ball_height / 2), 
                                ball_bits, 
                                ball_width, 
                                ball_height, 
                                BLACK   );
        
        // Another ball in the bottom right
        // To prevent a transparency effect, you will need either a second xbitmap, or to write a background of white pixels underneath 
        display.fillCircle(     CENTER_X + ball_offset, 
                                CENTER_Y, ball_height / 2, 
                                WHITE   );

        display.drawXBitmap(    CENTER_X - (ball_width / 2) + ball_offset, 
                                CENTER_Y - (ball_height / 2), ball_bits, 
                                ball_width, 
                                ball_height, 
                                BLACK   );
        
        // End of DRAW(), display will now update
    }

}

void loop() {
    
}
