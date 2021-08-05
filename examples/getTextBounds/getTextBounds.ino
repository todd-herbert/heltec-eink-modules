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

  
//DEMO: Placing text accurately with getTextBounds()
//================================================
      //NOTE: THIS FUNCTION DOES NOT APPEAR TO WORK CORRECTLY WITH THE BUILT-IN FALLBACK FONT
      //So be sure to use setFont()!
      //This is an error in GFX_Root and not an error with the Heltec_213R_V2 library

#include "heltec-eink-modules.h"

#include "Fonts/FreeSerifBoldItalic9pt7b.h"   //Include the particular font

PANEL_CLASS display(DC_PIN, CS_PIN, BUSY_PIN);

void setup() {
  display.begin();
  display.setRotation(display.orientation.PINS_RIGHT);  //Landscape

  display.setFont( &FreeSerifBoldItalic9pt7b );   //Pass (the address of) the font to the library
  const char *text = {"Fancy fonty text."};

  //Precisely place our text using getTextBounds()
  //================================================


  int16_t text_top_edge; //These will receive information about how much space our text will take up 
  int16_t text_left_edge;
  uint16_t text_width;
  uint16_t text_height;
  
  //This will tell us where the bounds of the text would be, if we setCursor(0,0) and then print(text)
  //Note that the variables are passed by reference
  display.getTextBounds(text, 0, 0, &text_left_edge, &text_top_edge, &text_width, &text_height);

  //We can use this information in our loop to help place the string
  //We'll show off and align our text right
  //setCursor()'s Y value is the imaginary line that the characters sit on. In this case, slightly above the base of the screen
  uint16_t cursor_demo_x = display.bounds.full.right() - text_width;
  uint16_t cursor_demo_y = display.bounds.full.bottom() - 30;



  //Graphics GO!
  //==============================================

  while( display.calculating() ) {

    display.setCursor(cursor_demo_x, cursor_demo_y);          
    display.print(text);

    //Lets draw a line across the screen at cursor height, to really make the point clear
    display.drawLine(0, cursor_demo_y, display.bounds.full.right(), cursor_demo_y, display.colors.BLACK);
    
  }

    display.update();   //The display will only begin to change once update() is called
}

void loop() { }

//===============================================================
//Note: other methods to help with text-placement include:
//      setCursorTopLeft()  -   Put text by top / left
//      getTextWidth()
//      getTextHeight()
//===============================================================