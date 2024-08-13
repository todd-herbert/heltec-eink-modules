#include <heltec-eink-modules.h>

// Pick your panel  -  https://github.com/todd-herbert/heltec-eink-modules
// ---------------

    // EInkDisplay_VisionMasterE213 display;
    // EInkDisplay_VisionMasterE290 display;

// DEMO: Vision Master - Basic
// --------------------
// Most of the examples are written to support older hardware.
// This example shows a more direct way to write display code. It is only for Heltec's "Vision Master" all-in-one boards.

#include "Fonts/FreeSans9pt7b.h"
#include "Fonts/FreeSansBold9pt7b.h"

void setup() {
    display.print("Hello, world!");
    display.update();
    
    delay(4000);
    display.clearMemory();  // Start a new drawing

    display.landscape();
    display.setFont( &FreeSans9pt7b );
    display.printCenter("In the middle.");
    display.update();

    delay(4000);
    display.clearMemory();  // Start a new drawing

    display.setCursor(5, 20);   // Text Cursor - x:5 y:20
    display.println("Here's a normal update.");
    display.update();

    delay(2000);    // Pause to read

    display.fastmodeOn();
    display.println("Here's fastmode,");
    display.update();
    display.println("aka Partial Refresh.");
    display.update();

    delay(2000);    // Pause to read
    
    display.fastmodeOff();
    display.setFont( &FreeSansBold9pt7b );  // Change to bold font
    display.println();
    display.println("Don't use too often!");
    display.update();

    delay(4000);
    display.clear();    // Physically clear the screen

    display.fastmodeOn();
    display.setFont( NULL ); // Default Font
    display.printCenter("How about a dot?", 0, -40);   // 40px above center
    display.update();

    delay(2000);

    display.fastmodeOff();
    display.fillCircle(
        display.centerX(),  // X: center screen
        display.centerY(),  // Y: center screen
        10,                             // Radius: 10px
        BLACK                           // Color: black
        );
    display.update();

    delay(2000);
    
    display.fillCircle(display.centerX(), display.centerY(), 5, WHITE);   // Draw a smaller white circle inside, giving a "ring" shape
    display.update();

    delay(10000);
    display.clear();    // Physically clear the screen, ready for your next masterpiece
}

void loop() {

}