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


// DEMO: Text
// ------------------
// A few examples of text, to get you started

// Include a font (for later)
#include "Fonts/FreeSerif9pt7b.h"

void setup() {

    // Nothing fancy
    DRAW (display) {
        display.print("Hello, World!");
    }

    // Pause to read
    delay(4000);

    // --------------------------------

    display.setRotation(90);                // Rotate 90deg clocklwise - more room
    display.setFont( & FreeSerif9pt7b );    // Set font - pass the address (&) of the font 
    display.setBackgroundColor(BLACK);      // Background: BLACK
    display.setTextColor(WHITE);            // Text: WHITE
    display.setCursor(5, 20);               // Cursor to x:5 y:20 - think "word processor"

    DRAW (display) {
        display.println("black");
        display.println("on");
        display.println("white");
    }

    // Pause to read
    delay(4000);

    // --------------------------------

    display.setFont( NULL );            // Font: back to default
    display.setBackgroundColor(WHITE);  // Background: WHITE
    display.setTextColor(BLACK);        // Text: BLACK
    
    DRAW (display) {
        display.setTextSize(3);
        display.printCenter("Big");   // Centered

        display.setTextSize(1);
        display.printCenter("Small", 0, 30);    // 30px below center
    }

    // Pause to read
    delay(4000);

    // --------------------------------

    // Let's use the nice font again
    display.setFont( &FreeSerif9pt7b );

    char sample_text[] = "Measure!";
    
    int offset_left;
    int offset_top;
    unsigned int text_width;
    unsigned int text_height;

    // If the cursor were placed at 0, 0:
    // Where would the left and top edges be? (negative)
    // How wide and how tall would the text be?
    // Don't blame me, this is an AdafruitGFX method
    display.getTextBounds(sample_text, 0, 0, &offset_left, &offset_top, &text_width, &text_height);

    // Where to place cursor: for align bottom-right
    unsigned int cursor_right = display.right() - (text_width + offset_left);
    unsigned int cursor_bottom = display.bottom() - (text_height + offset_top);

    // Where to place cursor: for align top-left
    unsigned int cursor_left = 0 - offset_left;
    unsigned int cursor_top = 0 - offset_top;

    DRAW(display) {
        // Move to bottom right, print text
        display.setCursor(cursor_right, cursor_bottom);
        display.print(sample_text);

        // Move to top left, print text
        display.setCursor(cursor_left, cursor_top);
        display.print(sample_text);
    }

    // Pause
    delay(4000);

    // --------------------------------

    // If you just want to align top-left, these is a lazier way:

    char sample_text2[] = "Easier";
    
    DRAW (display) {
        display.setCursorTopLeft(sample_text2, 0, 0);
        display.print(sample_text2);
    }

    delay(4000);
    display.clear();
}

void loop() {

}