#include <heltec-eink-modules.h>

// -- Example will not run on Arduino Uno / Nano
// -- Example *may* run on Arduino Mega

// Find your wiring  -  https://github.com/todd-herbert/heltec-eink-modules#wiring
// ----------------

    #define PIN_DC      2
    #define PIN_CS      4
    #define PIN_BUSY    5

    // "Wireless Paper" boards: skip this, your wiring is pre-set


// Pick your panel  -  https://github.com/todd-herbert/heltec-eink-modules#supported-displays
// ---------------

    // -- SPI Displays --

    // DEPG0150BNS810 display( PIN_DC, PIN_CS, PIN_BUSY );      // 1.54" - Mono 
    // DEPG0154BNS800 display( PIN_DC, PIN_CS, PIN_BUSY);       // 1.54" - Mono 
    // GDEP015OC1 display( PIN_DC, PIN_CS, PIN_BUSY);           // 1.54" - Mono 
    // DEPG0213RWS800 display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.13" - 3 Color Red
    // QYEG0213RWS800 display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.13" - 3 Color Red
    // DEPG0290BNS75A display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.9"  - Mono 
    // DEPG0290BNS800 display( PIN_DC, PIN_CS, PIN_BUSY );      // 2.9"  - Mono 
    // GDE029A1 display( PIN_DC, PIN_CS, PIN_BUSY );            // 2.9"  - Mono 

    // -- "Wireless Paper" --

    // DEPG0213BNS800 display;      // (Red Tab)
    // LCMEN2R13EFC1 display;       // (Green Tab)


// DEMO: update()
// ------------------------------------------------
// Larger microcontrollers have enough RAM to hold the full screen image at once: they do not need paging.
// These devices do not need to use the DRAW() loop, drawing commands can be issued almost anywhere.
// Call update() to show the result the display.


void setup() {

    // Print two lines of text

    display.setCursor(10, 10);
    display.print("First line.");

    display.setCursor(10, 40);
    display.print("Second line.");

    // Update the display
    display.update();


    display.drawTriangle(   10, 50,     // Point 1 x, y
                            20, 5,      // Point 2 x, y
                            70, 45,     // Point 3 x, y
                            BLACK   );  // Color

    // Update the display, drawing over-top the last image
    display.update();

    delay(5000);

    // Display image remains; but memory is wiped clean
    // "A blank slate"
    display.clearMemory();

    display.setCursor(10, 60);
    display.println("clearMemory()");
    display.print("a blank canvas");

    display.update();
}

void loop() {
    
}
