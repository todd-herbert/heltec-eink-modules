//---------------------------------------------------------------------
//Which display are you using?  (uncomment one)

//#define   USING_Heltec_154_V2
//#define   USING_Heltec_213Red_V2
//#define   USING_Heltec_290_V2


//Where is your display connected?

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


//DEMO: setRotation() printing text different orientations
//=========================================================
      //For the sake of readability, orientation can be set with either an integer, or in reference to the "header pins" on the panel:
      //      display.orientation.PINS_ABOVE = 0
      //      display.orientation.PINS_LEFT  = 1
      //      display.orientation.PINS_BELOW = 2
      //      display.orientation.PINS_RIGHT = 3


#include "heltec-eink-modules.h"

PANEL_CLASS display(DC_PIN, CS_PIN, BUSY_PIN);

void setup() {
  display.begin();
  display.setTextSize(1);

  while( display.calculating() ) {
    
    display.setRotation(display.orientation.PINS_ABOVE);
    display.setCursor(10, 10);
    display.print("Pins Above (0)");

    display.setRotation(display.orientation.PINS_LEFT);
    display.setCursor(10, 10);
    display.print("Pins Left (1)");

    display.setRotation(display.orientation.PINS_BELOW);
    display.setCursor(10, 10);
    display.print("Pins Below (2)");

    display.setRotation(display.orientation.PINS_RIGHT);
    display.setCursor(10, 10);
    display.print("Pins on Right (3)");
    
  }

  display.update();   //The display will only begin to change once update() is called
}

void loop() { }
