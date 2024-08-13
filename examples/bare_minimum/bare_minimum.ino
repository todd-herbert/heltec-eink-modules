#include <heltec-eink-modules.h>

// Display model and wiring
DEPG0290BNS800 display(2 /*DC*/, 4 /*CS*/, 5 /*BUSY*/);

void setup() {

    // DRAW supports old platforms (Arduino UNO)
    // See "update" example for newer devices

    DRAW (display) {
        // Graphics code here, for example: 
        display.fillCircle(50, 100, 20, BLACK);
    }

}

void loop() {
    
}
