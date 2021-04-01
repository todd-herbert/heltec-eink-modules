#include <Arduino.h>
#include <SPI.h>
#include "GFX_Root/GFX.h"

///Heltec 1.54" V2
///Declaration: EGH_154_V2(  d/c pin  , cs pin , busy pin )
class EGH_154_V2 : public GFX {

    //Consts
    //===================
    private:
        //These are correct for the Heltec 1.54" V2, but are still defined here for easy access
        const SPISettings spi_settings = SPISettings(200000, MSBFIRST, SPI_MODE0);
        const uint16_t panel_width = 200;
        const uint16_t panel_height = 200;
        const int16_t drawing_width = 200;  //Panel needs 128 * 250 bytes of data, however the useful drawing area is slightly smaller
        const int16_t drawing_height = 200;

    //Consts for user config
    //==================
    public:
        enum Colors{BLACK = 0, WHITE = 1};
        struct PageProfile {
            uint16_t height;
            uint16_t count;
        };
        //TODO: calculate profiles for 154black
        const PageProfile   PAGESIZE_TINY      {.height = 4, .count = 50};      //100kb of SRAM, 5% of total (Arduino UNO)
        const PageProfile   PAGESIZE_SMALL     {.height = 10, .count = 20};     //250kb of SRAM, 12.5% of total (Arduino UNO)
        const PageProfile   PAGESIZE_MEDIUM    {.height = 20, .count = 10};     //500kb of SRAM, 25% of total (Arduino UNO)
        const PageProfile   PAGESIZE_LARGE     {.height = 40, .count = 5};      //1000kb of SRAM, 50% of total (Arduino UNO)
        //Feel free to add any other profiles you wish. The only requirement is that ".height" * count = panel height (200px)



    //Methods
    //=============================================================================
    public:
        //Constructor
        //Have to initialize because of GFX class
        EGH_154_V2( uint8_t pin_dc, uint8_t pin_cs, uint8_t pin_busy) : GFX(panel_width, panel_height),
                                                                                pin_dc(pin_dc), 
                                                                                pin_cs(pin_cs), 
                                                                                pin_busy(pin_busy)
                                                                                {}
        //Graphics overloads and config methods                                                                
        void drawPixel(int16_t x, int16_t y, uint16_t color);
        void setDefaultColor(uint16_t bgcolor);
        enum Flip {FLIP_NONE, FLIP_HEIGHT, FLIP_WIDTH, FLIP_WIDTH_AND_HEIGHT};
        void setFlip(Flip flip);

        //Paging and Hardware methods
        void begin() {begin(PAGESIZE_MEDIUM);}
        void begin(PageProfile page_size, void (*wake_callback)(void) = NULL, void (*sleep_callback)(void) = NULL);
        bool calculating() {return calculating(true);}
        bool calculating(bool blocking);
        bool busy() {return digitalRead(pin_busy);}
        void clear();

        //Added drawing tool methods
        int16_t height(void) const {return rotation % 2 ? drawing_width : drawing_height;}
        int16_t width(void) const {return rotation % 2 ? drawing_height : drawing_width;}
        int16_t right(void) const {return width() - 1;}
        int16_t bottom(void) const {return height() - 1;}
        int16_t centerX(void) const {return (width() / 2) - 1;}
        int16_t centerY(void) const {return (height() / 2) - 1;}
        void setCursorCorner( char* text, uint16_t x, uint16_t y);

    private:    //Hardware methods
        void sendCommand(uint8_t command);
        void sendData(uint8_t data);
        void wake();
        void wait();
        void update(bool blocking = true);
        void clearPage(uint16_t bgcolor);
        void writePage();

    private:    //Deleted methods
        using GFX::drawGrayscaleBitmap;
        using GFX::drawRGBBitmap;

    //Members
    //=========================================================================================
    private:
        uint8_t pin_dc, pin_cs, pin_busy;

        void (*wake_callback)(void);
        void (*sleep_callback)(void);
        
        PageProfile page_profile;
        uint16_t page_bytecount;
        uint8_t *page_black;

        uint8_t page_cursor = 0;
        uint8_t page_top, page_bottom;  //Counters

        uint16_t default_color = WHITE;
        Flip img_flip;  //Which axes are flipped
};