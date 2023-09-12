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
    // DEPG0290BNS75A display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.9"  V2 - BW - Red Tab
    // DEPG0290BNS800 display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.9"  V2 - BW - Red Tab
    // GDE029A1 display( PIN_DC, PIN_CS, PIN_BUSY );            // 2.9"  V2 - BW - Blue Tab


// DEMO: Fast Mode
// ------------------
    // Some panels have the ability to perform a "fast update",
    // The technical term for this feature is "partial refresh".

    // If your panel supports this, you can select it with setFastmode()

// "Loading icon" images
// --------------------
#include "hourglass_1.h"
#include "hourglass_2.h"
#include "hourglass_3.h"
const unsigned char* hourglasses[] = {hourglass_1_bits, hourglass_2_bits, hourglass_3_bits};


// Shortcuts to save typing

FullBounds f = display.bounds.full;
WindowBounds w = display.bounds.window;

// Pre-calculate postition for "loading icon"

int ICON_L = f.centerX() - (hourglass_1_width / 2);
int ICON_T = f.centerY() - (hourglass_1_height / 2) - 15;  // Slightly towards screen top


void setup() {
    // Make sure we're starting with a blank screen
    display.clear();

    // Bigger characters
    display.setTextSize(2);

    // Enable fastmode
    display.fastmodeOn();

    // Label text, screen bottom
    // -----------------------------------------
    DRAW (display) {
        display.setCursor(0, f.bottom() - 30);
        display.println("Fastmode:");
        display.println("On");
    }

    // Play loading animation, and countdown in corner
    // ------------------------------------------------
    display.setTextColor(WHITE);
    display.setWindow( f.left(), f.top(), f.width(), f.height() - 30 ); // Don't overwrite the bottom 30px

    for (int demo = 0; demo <= 5; demo++) { // 5 times in total

        DRAW (display) {
            // Draw the next "loading icon" in sequence, from hourglasses[]
            display.drawXBitmap(ICON_L, ICON_T, hourglasses[demo % 3], hourglass_1_width, hourglass_1_height, BLACK);

            // Draw a square in the corner with a digit
            display.fillRect(0, 0, 30, 30, BLACK);
            display.setCursor(10, 10);
            display.print(demo);
        }

    }

    // Pause here
    delay(4000);

    // Back to normal mode (full refresh)
    display.fastmodeOff();

    // Change the label text
    // ----------------------
    display.setTextColor(BLACK);
    display.setWindow ( f.left(), f.bottom() - 30, f.width(), 30 ); // Only write to the bottom 30px

    DRAW (display) {
        display.setCursor(0, f.bottom() - 30);
        display.println("Fastmode:");
        display.println("Off");
    }

}

void loop() {}
