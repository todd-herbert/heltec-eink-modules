// Which panel are you using?   -   https://github.com/todd-herbert/heltec-eink-modules#identifying-your-display
// --------------------------
    // #define  USING_DEPG0150BNS810        // 1.54" V2 - BW - Red Tab
    // #define  USING_DEPG0154BNS800        // 1.54" V2 - BW - Red Tab
    // #define  USING_GDEP015OC1            // 1.54" V2 - BW - Blue Tab
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
#elif   defined USING_DEPG0290BNS75A
    #define     PANEL_CLASS     DEPG0290BNS75A
#elif   defined USING_DEPG0290BNS800
    #define     PANEL_CLASS     DEPG0290BNS800   
#elif   defined USING_GDE029A1
    #define     PANEL_CLASS     GDE029A1
#endif


// DEMO: Fast Mode
// ------------------
        // Some panels have the ability to perform a "fast update",
        // The technical term for this feature is "partial refresh".

        // If your panel supports fastmode, you can select it with setFastmode()
        // For more information, see https://github.com/todd-herbert/heltec-eink-modules#fast-mode-partial-refresh

#include "heltec-eink-modules.h"

// Loading icon images
// --------------------
#include "hourglass_1.h"
#include "hourglass_2.h"
#include "hourglass_3.h"
const unsigned char* hourglasses[] = {hourglass_1_bits, hourglass_2_bits, hourglass_3_bits};

PANEL_CLASS display(DC_PIN, CS_PIN, BUSY_PIN);  // PANEL_CLASS is a shortcut for your display; Line 13

// Shortcuts to save typing
// https://github.com/todd-herbert/heltec-eink-modules#code-readability
// -------------------------
PANEL_CLASS::Bounds::Full f = display.bounds.full;
PANEL_CLASS::Bounds::Window w = display.bounds.window;
PANEL_CLASS::ColorList c = display.colors;

const uint16_t ICON_L = f.centerX() - (hourglass_1_width / 2);
const uint16_t ICON_T = f.centerY() - (hourglass_1_height / 2) - 15;  // Slightly towards screen top

void setup() {
    display.setDefaultColor(c.WHITE);
    display.setTextSize(2);
    display.clear();

    // A nice little label, not yet in fast-mode
    // -----------------------------------------
    while(display.calculating()) {
        display.setCursor(0, f.bottom() - 30);
        display.println("fastmode");
        display.print(".ON");
    }
    display.update();


    // Play loading animation, and countdown in corner
    // ------------------------------------------------
    display.setTextColor(c.WHITE);
    display.setWindow( f.left(), f.top(), f.width(), f.height() - 30 ); // Don't overwrite the bottom 30px
    display.setFastmode( display.fastmode.ON );

    for (uint8_t demo = 0; demo <= 9; demo++) { // 10 times in total

        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
        // To exit fast-mode, you must set to fastmode.FINALIZE

        if (demo == 9)
            display.setFastmode( display.fastmode.FINALIZE );

        // This takes slightly longer than fastmode.ON, but preserves the image when reconfiguring.
        // Display automatically returns to fastmode.OFF after finalize is complete
        // Should also be called when changing window dimensions
        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

        // Drawing operations
        // --------------------
        while (display.calculating()) {
            // Draw a new loading icon from hourglasses[]
            display.drawXBitmap(  ICON_L, ICON_T, hourglasses[demo % 3], hourglass_1_width, hourglass_1_height, c.BLACK);

            // Draw a square in the corner with a digit
            display.fillRect(0, 0, 30, 30, c.BLACK);
            display.setCursor(10, 10);
            display.print(demo);
        }
        // update() is called automatically during fast-mode
    }

    // Change the label text
    // ----------------------
    display.setTextColor(c.BLACK);
    display.setWindow ( f.left(), f.bottom() - 30, f.width(), 30 ); // Only write to the bottom 30px

    // Straight to FINALIZE
    // If there was more drawing to do, we might use fastmode.ON, but this is the final operation.
    // Do not stay in fast-mode longer than required; it may damage the display.

    display.setFastmode( display.fastmode.FINALIZE );

    while(display.calculating()) {
        display.setCursor(0, f.bottom() - 30);
        display.println("fastmode");
        display.print(".FINALIZE");
    }

    // Pause here, and redraw in detail
    // --------------------------------
    delay(4000);

    while(display.calculating()) {
        display.setCursor(0, f.bottom() - 30);
        display.println("fastmode");
        display.print(".OFF");
    }

    display.fullscreen();   // Unconvential use of fullscreen() / setWindow(). Tell display we want the WHOLE SCREEN refreshed.
    display.update();
}

void loop() {}
