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
#elif   defined USING_Heltec_213Red_V2
            #define     PANEL_CLASS     Heltec_213Red_V2    
#elif   defined USING_Heltec_290_V2
            #define     PANEL_CLASS     Heltec_290_V2    
#endif

//----------------------------------------------------------------------

//DEMO: Using fonts
//================================================

#include "heltec-eink-modules.h"

//Include the font you want from the Fonts folder. I believe that they take up a bit of memory, so maybe don't include them all
#include "Fonts/FreeSerifBold12pt7b.h"

PANEL_CLASS display(DC_PIN, CS_PIN, BUSY_PIN);

void setup() {
  display.begin();
  display.setRotation(display.orientation.PINS_RIGHT); //Landscape, text fits better that way (Header PINS to RIGHT of the display)

  display.setFont( &FreeSerifBold12pt7b );   //Pass (the address of) the font to the library
  display.setTextColor(display.colors.BLACK);

  while( display.calculating() ) {

    display.setCursor(10, 50);            //Set the (word-processor-like) cursor to the abritrary position of x=30, y=50          
    display.print("Fancy fonty text.");

  } //Note: setCursor needs to run inside of the calculating() loop, as it moves along with each letter typed.
    //This means we need to shunt it back to the start again when we recalculate the next section of the screen

  display.update();   //The display will only begin to change once update() is called.
}

void loop() { }
