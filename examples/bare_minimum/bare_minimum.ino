#include "heltec-eink-modules.h"

// Define your pins:
// ------------------

// ( DO NOT connect pins directly to display )
// See https://github.com/todd-herbert/heltec-eink-modules#wiring

	#define PIN_BUSY    7
	#define PIN_CS      10
	#define PIN_DC      8


// Pick your panel:	(uncomment one)
// ---------------------------------

	// DEPG0150BNS810 display( PIN_DC, PIN_CS, PIN_BUSY );		// 1.54" V2 - BW
	// DEPG0154BNS800 display( PIN_DC, PIN_CS, PIN_BUSY);		// 1.54" V2 - BW
	// QYEG0213RWS800 display( PIN_DC, PIN_CS, PIN_BUSY );		// 2.13" V2 - BWR
	// DEPG0290BNS75A display( PIN_DC, PIN_CS, PIN_BUSY );		// 2.9"  V2 - BW


// DEMO: A bare minimum example - one big ol' spot 
// ------------------------------------------------

void setup() {

	display.begin();

	while ( display.calculating() ) {
		// 50px from left, 100px from top, draw a black circle with 20px radius
		display.fillCircle(50, 100, 20, display.colors.BLACK);
	}

	display.update();
}

void loop() {}
