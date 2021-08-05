//---------------------------------------------------------------------
//Which panel are you using?  (uncomment one)

//#define   USING_Heltec_154_V2
//#define   USING_Heltec_213Red_V2
//#define   USING_Heltec_290_V2


//Where is your panel connected?

#define DC_PIN 8
#define CS_PIN 10
#define BUSY_PIN 7


//(Example automatically picks the correct class and sample image)
#if     defined USING_Heltec_154_V2
            #define     PANEL_CLASS     Heltec_154_V2    
            #define     CHESS_H    "images/chess_200x200.h"
#elif   defined USING_Heltec_213Red_V2
            #define     PANEL_CLASS     Heltec_213Red_V2    
            #define     CHESS_H    "images/chess_250x122.h"
#elif   defined USING_Heltec_290_V2
            #define     PANEL_CLASS     Heltec_290_V2    
            #define     CHESS_H    "images/chess_296x128.h"
#endif

//----------------------------------------------------------------------


//DEMO: Black & White XBitmap Images
//=================================
    //XBitmap is an old image file format from the early days of the internet
    //It was very inefficient as the imagedata was stored more or less as human readable C code
    //This, however, serves our purposes very well. As such, Adafruit have chosen to add support for XBM images
    //These can be easily created with the free GIMP software.

    //The process of creating these images is a little bit involved.
    //Please see the tutorial at:

    // https://github.com/todd-herbert/Heltec-213R-V2/blob/main/docs/XBitmapTutorial/xbitmap-tutorial.md

#include "heltec-eink-modules.h"

//Here we are including the xbm image file (chess.h or similar). In this example, for convenience, an appropriate image for you display has been automatically selected. (See above)
#include CHESS_H


PANEL_CLASS display(DC_PIN, CS_PIN, BUSY_PIN);

void setup() {
  display.begin();
  display.setRotation(display.orientation.PINS_LEFT);   //Don't forget to set the orientation, so your image fits how you intended

  while( display.calculating() ) {
    //This while loop is important; it allows the display to update piece by piece, saving resources
    display.drawXBitmap(0, 0, chess_bits, chess_width, chess_height, display.colors.BLACK);
  }

  display.update();   //The display will only begin to change once update() is called
}

void loop() {}