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


// DEMO: Save to SD  -  save and load fullscreen .bmp images using SD card
// ------------------------------------------------------------------------
// NOTE: SD write is disabled for Arduino UNO (huge saving in Flash Memory)
// To re-enable it, edit optimization.h in the library's folder


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


    // Write a .bmp image to SD card - just like drawing to screen
    // Save with prefix "DemoIMG", and identifier: 1

    SAVE_TO_SD (display, "Demo", 1) {
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
    display.loadFullscreenBMP("Demo", 1);

    delay(4000);


    // Lets add a window to the saved canvas

    display.setRotation(PINS_LEFT);             // Rotation: landscape, with pins on screen left

    WindowBounds w = display.window;     // (shortcut, saves typing)
    int height = 30;
    int width = 100;
    int left = w.centerX() - (width / 2);
    int top = w.centerY() - (height / 2);

    display.setWindow(left, top, width, height);

    // Notice that because we setWindow(), most of the old image is preserved

    SAVE_TO_SD(display, "Demo", 1) {
        display.drawRect(w.left(), w.top(), w.width(), w.height(), BLACK);     // Black border around window

        display.setCursor(w.left() + 5, w.top() + 10);
        display.println("old canvas,");
        display.println("new window");
    }

    // Clear the screen, we don't need it.
    // Image data is saved in Demo0001.bmp

    display.clear();

    delay(2000);


    // Load the saved image, with the spot, and now the window
    // Note that we can also specify the filename manually

    display.loadFullscreenBMP("Demo0001.bmp");


    // Connect the SD card to your computer, and you will find the Demo0001.bmp image
}

void loop() {
    
}
