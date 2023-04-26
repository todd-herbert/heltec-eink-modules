// Which panel are you using?  (uncomment one)
// --------------------------------------------
	// #define   USING_DEPG0150BNS810		// 1.54" V2 - BW
	// #define   USING_QYEG0213RWS800		// 2.13" V2 - BWR
	// #define   USING_DEPG0290BNS75A		// 2.9"  V2 - BW


// Where is your panel connected?
// -------------------------------

	#define DC_PIN 8
	#define CS_PIN 10
	#define BUSY_PIN 7


// (Example automatically picks the correct class and sample image)
#if     defined USING_DEPG0150BNS810
	#define     PANEL_CLASS     DEPG0150BNS810    
	#define     PENCILS_H    "pencils_200x200.h"
#elif   defined USING_QYEG0213RWS800
	#define     PANEL_CLASS     QYEG0213RWS800    
	#define     PENCILS_H    "pencils_250x122.h"
#elif   defined USING_DEPG0290BNS75A
	#define     PANEL_CLASS     DEPG0290BNS75A    
	#define     PENCILS_H    "pencils_296x128.h"
#endif

// DEMO: Bitmap Data
// -----------------
		// You may sometime have the need to draw raw bitmap data to the screen
		// This is is possible with drawBitmap()
		// One possible application here is that drawBitmap accepts data from SRAM, where as drawXBitmap will only draw from PROGMEM

#include "heltec-eink-modules.h"

// Sample set of raw bitmap data
#include PENCILS_H

PANEL_CLASS display(DC_PIN, CS_PIN, BUSY_PIN);

void setup() {
	display.begin();

	display.setRotation(display.orientation.PINS_LEFT);   // Don't forget to set the correct orientation, so your image fits how you intended

	// Bitmap image data comes in all sorts of weird formats. To get it to work, you might have to play with the settings.
	display.setFlip(display.flip.NONE);  				// If your image comes out flipped, change this
	display.setDefaultColor(display.colors.BLACK);		// If you get a negative of your image, try setting the background to black, and drawing the data as white

	while( display.calculating() ) {
		display.drawBitmap(0, 0, pencils, pencils_width, pencils_height, display.colors.WHITE);
	}

	display.update();	// The display will only begin to change once update() is called
}

void loop() {}
