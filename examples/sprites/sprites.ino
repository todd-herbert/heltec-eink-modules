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



// DEMO: Sprites
// -------------
    // XBitmaps are well suited for storing graphic elements that can be prerendered and then placed where neeeded


// Here we are including a small image of a ball
#include "ball.h"


void setup() {
    display.setRotation(display.orientation.PINS_LEFT);

    // Useful drawing aides
    static uint16_t TOP = 0;
    static uint16_t BOTTOM = display.bounds.full.bottom();
    static uint16_t LEFT = 0;
    static uint16_t RIGHT = display.bounds.full.bottom();
    static uint16_t CENTER_X = display.bounds.full.centerX();
    static uint16_t CENTER_Y = display.bounds.full.centerY();

    static uint16_t ball_offset = 53;

    while( display.calculating() ) {
        // First draw a ball in the background, top centre
        display.drawXBitmap(CENTER_X - (ball_width / 2), CENTER_Y - (ball_width / 2) - ball_offset, ball_bits, ball_width, ball_height, display.colors.BLACK);

        // ball in the bottom left
        // Note that the XBitmap only specifies location of one color. This allows transparency
        display.drawXBitmap(CENTER_X - (ball_width / 2) - ball_offset, CENTER_Y - (ball_width / 2), ball_bits, ball_width, ball_height, display.colors.BLACK);
        
        // Another ball in the bottom right
        // To prevent a transparency effect, you will need either a second xbitmap, or to write a background of white pixels underneath 
        display.fillCircle(CENTER_X + ball_offset, CENTER_Y, ball_width / 2, display.colors.WHITE);
        display.drawXBitmap(CENTER_X - (ball_width / 2) + ball_offset, CENTER_Y - (ball_width / 2), ball_bits, ball_width, ball_height, display.colors.BLACK);
    }

    display.update();   // The display will only begin to change once update() is called

}

void loop() {}
