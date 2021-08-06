//---------------------------------------------------------------------
//Which display are you using?  (uncomment one)
//(Only panels supporting fast mode are shown)

#define   USING_Heltec_154_V2

//Where is your display connected?

#define DC_PIN 8
#define CS_PIN 10
#define BUSY_PIN 7


//(Example automatically picks the correct class and sample image)
#if     defined USING_Heltec_154_V2
            #define     PANEL_CLASS     Heltec_154_V2      
#endif
//----------------------------------------------------------------------


//DEMO: Fast Update
//=================================
    //Some panels have the ability to perform a "fast update".
    //If your panel supports it, you can select is as a parameter when calling update()
    //This feature SHOULD be present in most panels, however is rarely implemented by Heltec
    //Hopefully future updates will bring wider support

#include "heltec-eink-modules.h"

//Loading icon images
#include "hourglass_1.h"
#include "hourglass_2.h"
#include "hourglass_3.h"
const unsigned char* hourglasses[] = {hourglass_1_bits, hourglass_2_bits, hourglass_3_bits};

PANEL_CLASS display(DC_PIN, CS_PIN, BUSY_PIN);

//Shortcuts to save typing
PANEL_CLASS::Bounds::Full f = display.bounds.full;
PANEL_CLASS::Bounds::Window w = display.bounds.window;
PANEL_CLASS::ColorList c = display.colors;

const uint16_t ICON_L = f.centerX() - (hourglass_1_width / 2);
const uint16_t ICON_T = f.centerY() - (hourglass_1_height / 2) - 15;  //Slightly towards screen top

const uint16_t SPOTS_W = 100;
const uint16_t SPOTS_H = 20;
const uint16_t SPOTS_L = f.centerX() - (SPOTS_W / 2);
const uint16_t SPOTS_R = f.centerX() + (SPOTS_W / 2);

void setup() {
  display.begin();
  display.setDefaultColor(c.WHITE);
  display.setTextSize(2);
  display.clear();

  //A nice little label
  //========================================
  while(display.calculating()) {
    display.setCursor(5, f.bottom() - 15);
    display.print("Quality: Fast");
  }
  display.update(display.quality.FAST);


  //Play loading animation, and countdown in corner
  //=================================
  display.setTextColor(c.WHITE);
  for (uint8_t demo = 0; demo < 10; demo++) { //10 times in total

      while(display.calculating(display.region.WINDOWED,  f.left(), f.top(), f.width(), f.height() - 50)) {
          //Draw a new loading icon from hourglasses[]
          display.drawXBitmap(  ICON_L, ICON_T, hourglasses[demo % 3], hourglass_1_width, hourglass_1_height, c.BLACK);

          //Draw a square in the corner with a digit
          display.fillRect(0, 0, 30, 30, c.BLACK);
          display.setCursor(10, 10);
          display.print(demo);
      }

      display.update(display.quality.FAST);
  }

  //Change the label text
  display.setTextColor(c.BLACK);
  while(display.calculating(display.region.WINDOWED,  f.left(), f.bottom() - 15, f.width(), 15)) {
    display.setCursor(5, f.bottom() - 15);
    display.print("Quality:Detailed");
  }
  display.update(display.quality.FAST); //We're drawing this with fast mode, but will "convert" it next


  //Now we will take the time to upgrade the whole display from FAST to DETAILED
  display.detail();
}

void loop() {}
