#include "heltec-eink-modules.h"

// Find your wiring  -  https://github.com/todd-herbert/heltec-eink-modules#wiring
// ----------------

    #define PIN_DC      2
    #define PIN_CS      4
    #define PIN_BUSY    5

    // Card Adapter 
    #define PIN_CS_CARD ?


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


// DEMO: Canvas  -  load and save screen image (canvas) using SD card
// -------------------------------------------------------------------

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


    // Write a "canvas" image to SD card - just like drawing to screen

    WRITE_CANVAS (display, "canvas001.bmp") {
        // 50px from left, 100px from top, draw a black circle with 20px radius
        display.fillCircle(50, 100, 20, BLACK);
    }


    // The canvas with the spot is saved to SD. We are free to use the display

    DRAW (display) {
        display.setCursor(5, 10);
        display.println("Look ma,");
        display.print("No spot!");
    }

    delay(4000);


    // Now, lets load the saved canvas - with the spot
    display.loadCanvas("canvas001.bmp");

    delay(4000);


    // Lets add a window to the saved canvas

    display.setRotation(PINS_LEFT);             // Rotation: landscape, with pins on screen left

    WindowBounds w = display.bounds.window;     // (saves typing)
    int height = 30;
    int width = 100;
    int left = w.centerX() - (width / 2);
    int top = w.centerY() - (height / 2);

    display.setWindow(left, top, width, height);

    WRITE_CANVAS(display, "canvas001.bmp") {
        display.drawRect(w.left(), w.top(), w.width(), w.height(), BLACK);     // Black border around window

        display.setCursor(w.left() + 5, w.top() + 10);
        display.println("old canvas,");
        display.println("new window");
    }

    // Clear the screen, we don't need it.
    // Image data is saved in canvas001.bmp

    display.clear();

    delay(2000);


    // Load the canvas, with the spot, and now the window
    // Note: because we used the special filename "canvas***.bmp"
    // We can refer to our canvas by number

    display.loadCanvas(1);


    // Connect the SD card to your computer, and you will find the canvas001.bmp image
}

void loop() {}
