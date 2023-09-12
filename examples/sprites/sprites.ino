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


// DEMO: Sprites
// -------------
    // XBitmaps are well suited for storing graphic elements that can be prerendered and then placed where neeeded


// Here we are including a small image of a ball
#include "ball.h"


void setup() {
    display.setRotation(PINS_LEFT);

    // Useful drawing aides
    unsigned int CENTER_X   = display.bounds.full.centerX();
    unsigned int CENTER_Y   = display.bounds.full.centerY();

    unsigned int ball_offset = 53;

    DRAW (display) {
        // First draw a ball in the background, top centre
        display.drawXBitmap(    CENTER_X - (ball_width / 2),                        // Left
                                CENTER_Y - (ball_width / 2) - ball_offset,          // Top
                                ball_bits,                                          // Image Data
                                ball_width,                                         // Width
                                ball_height,                                        // Height
                                BLACK   );                                          // Color

        // ball in the bottom left
        // Note that the XBitmap only specifies location of one color. This allows transparency
        display.drawXBitmap(    CENTER_X - (ball_width / 2) - ball_offset, 
                                CENTER_Y - (ball_width / 2), 
                                ball_bits, 
                                ball_width, 
                                ball_height, 
                                BLACK   );
        
        // Another ball in the bottom right
        // To prevent a transparency effect, you will need either a second xbitmap, or to write a background of white pixels underneath 
        display.fillCircle(     CENTER_X + ball_offset, 
                                CENTER_Y, ball_width / 2, 
                                WHITE   );

        display.drawXBitmap(    CENTER_X - (ball_width / 2) + ball_offset, 
                                CENTER_Y - (ball_width / 2), ball_bits, 
                                ball_width, 
                                ball_height, 
                                BLACK   );
        
        // End of DRAW(), display will now update
    }

}

void loop() {}
