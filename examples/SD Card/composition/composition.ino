#include <heltec-eink-modules.h>

// Find your wiring  -  https://github.com/todd-herbert/heltec-eink-modules#wiring
// ----------------

    #define PIN_DC      2
    #define PIN_CS      4
    #define PIN_BUSY    5

    // Card Adapter 
    #define PIN_CS_CARD ?


// Pick your panel  -  https://github.com/todd-herbert/heltec-eink-modules#supported-displays
// ---------------

    // DEPG0150BNS810 display( PIN_DC, PIN_CS, PIN_BUSY );      // 1.54" - Mono 
    // DEPG0154BNS800 display( PIN_DC, PIN_CS, PIN_BUSY);       // 1.54" - Mono 
    // GDEP015OC1 display( PIN_DC, PIN_CS, PIN_BUSY);           // 1.54" - Mono 
    // DEPG0213RWS800 display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.13" - 3 Color Red
    // QYEG0213RWS800 display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.13" - 3 Color Red
    // DEPG0290BNS75A display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.9"  - Mono 
    // DEPG0290BNS800 display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.9"  - Mono 
    // GDE029A1 display( PIN_DC, PIN_CS, PIN_BUSY );            // 2.9"  - Mono 


// DEMO: Composition - draw using .bmp image resources from SD card
// -----------------------------------------------------------------------
// Before running this example, you need to extract example_images.zip
// to the root of your SD card.
//
// https://github.com/todd-herbert/heltec-eink-modules/raw/main/docs/SD/example_images.zip


void setup() {

    // Use an SD card adapter; set adapter's CS pin
    display.useSD(PIN_CS_CARD);

    // Check if the card is usable
    if ( !display.SDCardFound() ) {

        // Not found - error message to display
        DRAW(display) {
            display.setCursor(5, 10);
            display.print("Error: no card");
        }

        return;     // Skip the rest of the example
    }


    // --- Found the card! ---

    display.setRotation(PINS_LEFT);

    // Align bottom edge of snowy.bmp with bottom edge of screen
    int snowy_align = display.bounds.full.height() - display.getBMPHeight("snowy.bmp");

    // Draw the base image - a snowy field
    DRAW(display) {
        display.drawMonoBMP(0, snowy_align, "snowy.bmp", BLACK);
    }

    delay(4000);


    // Same trick as above - align bottom
    int tree_align = display.bounds.full.height() - display.getBMPHeight("lil_tree.bmp");

    // Draw another tree, top left
    DRAW(display) {
        display.drawMonoBMP(0, snowy_align, "snowy.bmp", BLACK);
        display.drawMonoBMP(0, tree_align - 50, "lil_tree.bmp", BLACK);  // Lift the new tree 50px from bottom

        // You can also draw 3-Color images with a pair of RED and Black mono bitmaps
        // See the XBitmap example
    }

    delay(4000);


    // If you are using
    //  - ATmega328P (Arduino Uno, Nano, etc)
    //  - ATmega2560 (Arduino Mega 2560) WITH a 3-Color display
    //
    //  then you are out of RAM, and this is your stop.
    //  Sorry.

    // -------------------------------------
    #if __AVR_ATmega2560__
        if (display.supportsColor(RED))
            return;
    #endif
    #if !defined(__AVR_ATmega328P__) 

        // Big boards: carry on then..
            
        // Same trick as above - align bottom
        int sled_align = display.bounds.full.height() - display.getBMPHeight("sled.bmp");

        // This section is only for powerful boards, so we don't need the DRAW loop anymore.
        // We also don't need to redraw the whole scene. Just the new parts.

        display.draw24bitBMP(5, sled_align + 15, "sled.bmp", WHITE);   // Slightly off screen edges, treating WHITE source pixels as transparent
        display.update();

        // On a 3-Color display, the sled will appear as RED
        // Otherwise, the red pixels will be interpretted as black

    #endif
}

void loop() {}
