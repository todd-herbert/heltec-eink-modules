#include <heltec-eink-modules.h>

// Pick your panel  -  https://github.com/todd-herbert/heltec-eink-modules
// ---------------

    // "All-in-one" boards
    // --------------------------------------

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


// DEMO: Load from SD - display fullscreen .bmp files from card
// -----------------------------------------------------------------------
// Before running this example, you need to extract example_images.zip
// to the root of your SD card.
//
// https://github.com/todd-herbert/heltec-eink-modules/raw/main/docs/SD/example_images.zip
//
// This example demonstrates loadFullscreenBMP() 
// Only a specific type of .bmp image is accepted:
//     * 24bit .bmp file
//     * Portrait, not landscape
//     * Dimensions: full screen width x height
//  
// To work with images of a different size, see the "composition.ino" example sketch


void setup() {

    // Use an SD card adapter; set adapter's CS pin (optionally: MISO pin also)

    display.useSD(/*CS*/);
    // display.useSD(/*CS*/, /*MISO*/);

    // Pick which image fits this display
    switch(display.width()) {
        
        // 152px x 152px
        case 152:
            display.loadFullscreenBMP("fullscreen/152x152.bmp");
            break;

        // 200px x 200px
        case 200:
            display.loadFullscreenBMP("fullscreen/200x200.bmp");
            break;

        // 122px x 250px
        case 122:
            if (display.supportsColor(RED))
                display.loadFullscreenBMP("fullscreen/122x250-red.bmp");
            else
                display.loadFullscreenBMP("fullscreen/122x250.bmp");                
            break;

        // 128px x 296px
        case 128:
            display.loadFullscreenBMP("fullscreen/128x296.bmp");
            break;
    }

}

void loop() {

}
