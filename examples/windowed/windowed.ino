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


//DEMO: Windows
//=================================
    //It is possible to redraw only a portion of the display, without disturbing the existing image

#include "heltec-eink-modules.h"

PANEL_CLASS display(DC_PIN, CS_PIN, BUSY_PIN);

const char* lorem = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. " 
                    "Suspendisse massa dui, rhoncus id varius faucibus, tempor quis nulla.";

//Shortcuts to save typing
PANEL_CLASS::Bounds::Full f = display.bounds.full;
PANEL_CLASS::Bounds::Window w = display.bounds.window;
PANEL_CLASS::ColorList c = display.colors;

void setup() {
  display.begin();

  //Lay down a background first
  //=============================
  display.setRotation(display.orientation.PINS_ABOVE);
  display.setTextSize(1);
  display.setTextWrap(true);

  while( display.calculating(display.region.FULLSCREEN) ) {
    display.setCursor(0, 0);
    for(int i = 0; i<30; i++)
      display.print(lorem);
  }

  display.update();   //Draw this mighty wall of text to cover the screen
  delay(1000);  //Pause for dramatic effect


  //Draw to only a small "window" of the display, leaving the rest undisturbed
  //===========================================================================
  display.setRotation(display.orientation.PINS_RIGHT);
  display.setTextSize(1);

  const char* proclamation = "Behold the mighty window";
  
  uint16_t W_LEFT = f.centerX() - (display.getTextWidth(proclamation) / 2) - 10;
  uint16_t W_TOP = 16;
  uint16_t W_WIDTH = display.getTextWidth(proclamation) + 20;
  uint16_t W_HEIGHT = display.getTextHeight(proclamation) + 20;

  while (display.calculating(display.region.WINDOWED,
                                                      W_LEFT,
                                                      W_TOP,
                                                      W_WIDTH,
                                                      W_HEIGHT))
  {
    display.drawRect(w.left(), w.top(), w.width(), w.height(), c.BLACK);  //Put a border around the very edge of the window
    display.setCursorTopLeft(proclamation, w.left() + 10, w.top() + 10);
    display.print(proclamation);
  }

  display.update(); //Draw the window
  delay(1000);  //Dramatic.. PAUSE

  //Draw another window, just to really make a point
  //===========================================================================
 
  #include "window_cartoon.h"

  display.setRotation(display.orientation.PINS_RIGHT);
  W_LEFT = f.centerX() - (window_cartoon_width / 2);
  W_TOP = f.centerY() - (window_cartoon_height / 2);
  W_WIDTH = window_cartoon_width;
  W_HEIGHT = window_cartoon_height;

  while (display.calculating(display.region.WINDOWED,
                                                      W_LEFT,
                                                      W_TOP,
                                                      W_WIDTH,
                                                      W_HEIGHT))
  {
    //Note the small gap between the border we draw, and the image which SHOULD fill the space
    //This is a hardware limitation of the display
    //Window regions must have a horizontal dimension which is a multiple of 8 (because bits -> bytes blah blah)
    display.drawRect(w.left(), w.top(), w.width(), w.height(), c.BLACK);  //Put a border around the very edge of the window
    display.drawXBitmap(w.centerX() - (window_cartoon_width / 2), w.centerY() - (window_cartoon_height / 2), window_cartoon_bits, window_cartoon_width, window_cartoon_height, c.BLACK);
  }

  display.update(); //Show the new window on the screen
}

void loop() {}
