//---------------------------------------------------------------------
//Which panel are you using?  (uncomment one)
//(Only panels supported 3-color are shown)

#define   USING_Heltec_213Red_V2
//More panels to come?

//Where is your panel connected?

#define DC_PIN 8
#define CS_PIN 10
#define BUSY_PIN 7


//(Example automatically picks the correct class and sample image)
#if defined   USING_Heltec_213Red_V2
              #define     PANEL_CLASS       Heltec_213Red_V2    
              #define     APPLES_BLACK_H    "apples_black_250x122.h"
              #define     APPLES_RED_H      "apples_red_250x122.h"
#endif

//----------------------------------------------------------------------

//DEMO: Multicolor XBitmap Images
//=================================
    //XBitmap is an old image file format from the early days of the internet
    //It was very inefficient as the imagedata was stored more or less as human readable C code
    //This, however, serves our purposes very well. As such, Adafruit have chosen to add support for XBM images
    //These can be easily created with the free GIMP software.

    //The process of creating these images (especially multicolored) is a little bit involved.
    //Please see the tutorial at:

    //https://github.com/todd-herbert/heltec-eink-modules/blob/main/docs/XBitmapTutorial/xbitmap-tutorial.md

#include "heltec-eink-modules.h"

//Here we are including the two (slightly modified) xbm files that we created earlier, one for each of our display's colors.
//For convenience, in this example, these image files are automatically selected (see above)
#include APPLES_BLACK_H
#include APPLES_RED_H

PANEL_CLASS display(DC_PIN, CS_PIN, BUSY_PIN);


void setup() {
  display.begin();

  display.setRotation(display.orientation.PINS_RIGHT);   //Don't forget to set the orientation, so your image fits how you intended

  while( display.calculating() ) {
    //Draw each image to its destination color
    display.drawXBitmap(0, 0, apples_black_bits, apples_black_width, apples_black_height, display.colors.BLACK);
    display.drawXBitmap(0, 0, apples_red_bits, apples_red_width, apples_red_height, display.colors.RED);
  }

  display.update();   //The display will only begin to change once update() is called.
}

void loop() {}