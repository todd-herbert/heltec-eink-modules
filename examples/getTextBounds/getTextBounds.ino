#include <heltec-eink-modules.h>

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
    // LCMEN2R13EFC1 display;       // (Green Tab, V1.1)

    
// DEMO: Placing text accurately with getTextBounds()
// ---------------------------------------------------
// NOTE:    Text printed with custom fonts sits nicely *on* the cursor line (this example)
//          Text printed with the default font sits below the cursor line. 
//          
//          To place the default font upon the line, use an offset with setCursor().
//          To place a custom font below the line, use either an offset, or setCursorTopLeft()


#include "Fonts/FreeSerifBoldItalic9pt7b.h"   // Include the particular font


void setup() {
    display.setRotation(90);  // Landscape - 90 deg clockwise

    display.setFont( & FreeSerifBoldItalic9pt7b );   // Pass (the address of) the font to the library
    const char text[] = "Fancy font.";

    // Precisely place our text using getTextBounds()
    // -----------------------------------------------


    int text_top_edge = 0;          // These will receive information about how much space our text will take up 
    int text_left_edge = 0;         // Remember to initialize them as 0, or else..
    unsigned int text_width = 0;
    unsigned int text_height = 0;
    
    // This will tell us where the bounds of the text would be, if we setCursor(0,0) and then print(text)
    // Note that the variables are passed by reference (with &)
    display.getTextBounds(text, 0, 0, &text_left_edge, &text_top_edge, &text_width, &text_height);

    // We can use this information in our loop to help place the string
    // We'll show off and align our text right
    // setCursor()'s Y value is the imaginary line that the characters sit on. In this case, slightly above the base of the screen
    unsigned int cursor_demo_x = display.right() - text_width - 5;  // 5px safety margin
    unsigned int cursor_demo_y = display.bottom() - 30;



    // Graphics GO!
    // -------------

    DRAW ( display ) {

        display.setCursor(cursor_demo_x, cursor_demo_y);          
        display.print(text);

        // Lets draw a line across the screen at cursor height, to really make the point clear
        display.drawLine(0, cursor_demo_y, display.right(), cursor_demo_y, BLACK);
        
    }

}

void loop() {

}

// =========================================================================
// Note: other methods to help with text-placement include:
//      setCursorTopLeft()  -   Put text by top / left
//      getTextWidth()
//      getTextHeight()
//      getTextCenterX()    -   Find where to put cursor for centered text
//      getTextCenterY()
// =========================================================================