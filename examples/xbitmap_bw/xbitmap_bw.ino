// Which panel are you using?  (uncomment one)
// --------------------------------------------
    // #define	USING_DEPG0150BNS810		// 1.54" V2 - BW - Reb Tab
    // #define	USING_DEPG0154BNS800		// 1.54" V2 - BW - Red Tab
    // #define	USING_GDEP015OC1			// 1.54" V2 - BW - Blue Tab
    // #define	USING_QYEG0213RWS800		// 2.13" V2 - BWR - Red Tab
    // #define	USING_DEPG0290BNS75A		// 2.9" V2 - BW - Red Tab
    // #define  USING_DEPG0290BNS800        // 2.9" V2 - BW - Red Tab
    // #define	USING_HTE029A1              // 2.9" V2 - BW - Blue Tab


// Where is your panel connected?
// --------------------------------
    #define DC_PIN 8
    #define CS_PIN 10
    #define BUSY_PIN 7


// (Example automatically picks the correct class and sample image)
#if     defined USING_DEPG0150BNS810
    #define     PANEL_CLASS     DEPG0150BNS810    
    #define     CHESS_H    "chess_200x200.h"
#elif   defined USING_DEPG0154BNS800
    #define     PANEL_CLASS     DEPG0154BNS800    
    #define     CHESS_H    "chess_152x152.h"
#elif	defined	USING_GDEP015OC1
    #define		PANEL_CLASS		GDEP015OC1
    #define     CHESS_H    "chess_200x200.h"	
#elif   defined USING_QYEG0213RWS800
    #define     PANEL_CLASS     QYEG0213RWS800    
    #define     CHESS_H    "chess_250x122.h"
#elif   defined USING_DEPG0290BNS75A
    #define     PANEL_CLASS     DEPG0290BNS75A    
    #define     CHESS_H    "chess_296x128.h"
#elif   defined USING_DEPG0290BNS800
    #define     PANEL_CLASS     DEPG0290BNS800
    #define     CHESS_H    "chess_296x128.h"
#elif   defined USING_HTE029A1
    #define		PANEL_CLASS     HTE029A1    
    #define     CHESS_H    "chess_296x128.h"    
#endif


// DEMO: Black & White XBitmap Images
// -----------------------------------
    // XBitmap is an old image file format from the early days of the internet
    // It was very inefficient as the imagedata was stored more or less as human readable C code
    // This, however, serves our purposes very well. As such, Adafruit have chosen to add support for XBM images
    // These can be easily created with the free GIMP software.

    // The process of creating these images is a little bit involved.
    // Please see the tutorial at:

    // https://github.com/todd-herbert/heltec-eink-modules/blob/main/docs/XBitmapTutorial/README.md

#include "heltec-eink-modules.h"

// Here we are including the xbm image file (chess.h or similar). In this example, for convenience, an appropriate image for you display has been automatically selected. (See above)
#include CHESS_H


PANEL_CLASS display(DC_PIN, CS_PIN, BUSY_PIN);

void setup() {
    display.begin();
    display.setRotation(display.orientation.PINS_LEFT);   // Don't forget to set the orientation, so your image fits how you intended

    while( display.calculating() ) {
        // This while loop is important; it allows the display to update piece by piece, saving resources
        display.drawXBitmap(0, 0, chess_bits, chess_width, chess_height, display.colors.BLACK);
    }

    display.update();   // The display will only begin to change once update() is called
}

void loop() {}