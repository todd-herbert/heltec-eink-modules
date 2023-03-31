//---------------------------------------------------------------------
//Which display are you using?  (uncomment one)

//#define   USING_DEPG0150BNS810
//#define   USING_QYEG0213RWS800
//#define   USING_DEPG0290BNS800


//Where is your display connected?

#define DC_PIN 8
#define CS_PIN 10
#define BUSY_PIN 7


//(Example automatically picks the correct class and sample image)
#if     defined USING_DEPG0150BNS810
            #define     PANEL_CLASS     DEPG0150BNS810    
#elif   defined USING_QYEG0213RWS800
            #define     PANEL_CLASS     QYEG0213RWS800    
#elif   defined USING_DEPG0290BNS800
            #define     PANEL_CLASS     DEPG0290BNS800    
#endif
//----------------------------------------------------------------------


//DEMO: Shapes  - Kandinsky would be proud
//================================================
//        This example shows some basic functionality
//        A small demonstration of one way it is possible to work with the library


#include "heltec-eink-modules.h"


PANEL_CLASS display(DC_PIN, CS_PIN, BUSY_PIN);

//Lets make some shortcuts to save typing
//===========================================
PANEL_CLASS::Bounds::Full b = display.bounds.full;                //Dimension information about fullscreen panel
PANEL_CLASS::ColorList c = display.colors;                                         //Quick access to different colors



void setup() {
  display.begin();
  display.setRotation(3); //Alternatively, display.orientation.PINS_RIGHT
  

   //Pick colors that will work on your panel
  //=============================================
  static uint16_t BGCOLOR;
  static uint16_t ACCENT1;
  static uint16_t ACCENT2;

  #if     defined USING_DEPG0150BNS810
              BGCOLOR = c.BLACK;
              ACCENT1 = c.WHITE;
              ACCENT2 = c.WHITE;
  #elif   defined USING_QYEG0213RWS800
              BGCOLOR = c.RED;
              ACCENT1 = c.WHITE;
              ACCENT2 = c.BLACK;  
  #elif   defined USING_DEPG0290BNS800
              BGCOLOR = c.BLACK;
              ACCENT1 = c.WHITE;
              ACCENT2 = c.WHITE;    
  #endif
  //============================================

  display.setDefaultColor(BGCOLOR);

  while( display.calculating() ) {
  
      display.drawRoundRect(120, 20, 80, 60, 10, ACCENT1); //Hollow
      display.fillRoundRect(130, 30, 85, 65, 10, ACCENT1); //Filled

      display.fillRect(160, 50, 30, 30, BGCOLOR); //Drawing with our background color can help "erase" things

      display.fillCircle(40, -10, 25, ACCENT2);   //Drawing out of bounds is allowed
      display.drawLine(40, -10, 300, 500, ACCENT1); // <-- !!! But don't go crazy as every pixel gets processed, even if most of them are offscreen

      display.fillTriangle(0,0, 30, b.bottom(), 60, b.bottom(), ACCENT2);  //Handy functions like bottom() make drawing easier
      display.fillCircle(b.centerX(), b.centerY(), 20, ACCENT2);  //Right in the center
      display.drawCircle(b.centerX(), b.centerY(), 21, BGCOLOR);  //just a bit bigger (draw an outline)
  }

  display.update();   //The display will only begin to change once update() is called
}

void loop() {}
