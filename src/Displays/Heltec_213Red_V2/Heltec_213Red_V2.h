#include <Arduino.h>
#include <SPI.h>
#include "GFX_Root/GFX.h"

///Heltec 2.13" Red V2
///Declaration: Heltec_213RED_V2(  d/c pin  , cs pin , busy pin )
class Heltec_213Red_V2 : public GFX {

    //Consts
    //===================
    private:
        //These are correct for the Heltect 2.13" Red V2, but are still defined here for easy access
        const SPISettings spi_settings = SPISettings(200000, MSBFIRST, SPI_MODE0);
        const uint16_t panel_width = 128;
        const uint16_t panel_height = 250;
        static const int16_t drawing_width = 122;  //Panel needs 128 * 250 bytes of data, however the useful drawing area is slightly smaller
        static const int16_t drawing_height = 250;

    //Consts for user config
    //==================
    public:
        static struct FlipList{enum Flip{NONE = 0, HORIZONTAL=1, VERTICAL=2}; } flip;
        static struct ColorList{enum Colors{BLACK = 0, WHITE = 1, RED = 3}; } colors;
        static struct RegionList {enum Region{FULLSCREEN = 0, WINDOWED = 1}; } region;
        static struct RotationList {enum Rotations{PINS_ABOVE = 0, PINS_LEFT=1, PINS_BELOW = 2, PINS_RIGHT = 3};} orientation;  //NB: member is "orientation", as GFX::rotation already exists
        struct PageProfile {
            uint16_t height;
            uint16_t count;
        };
        struct PageProfileList {
            const PageProfile   TINY       {.height = 2, .count = 250};    //64kb of SRAM, 4% of total (Arduino UNO)
            const PageProfile   SMALL      {.height = 5, .count = 50};     //160kb of SRAM, 8% of total (Arduino UNO)
            const PageProfile   MEDIUM     {.height = 10, .count = 25};    //320kb of SRAM, 16% of total (Arduino UNO)
            const PageProfile   LARGE      {.height = 25, .count = 10};    //800kb of SRAM, 40% of total (Arduino UNO)
            //Feel free to add any other profiles you wish. The only requirement is that ".height" * count = panel height (250px)
        } pageSize;
  

    //Methods
    //=============================================================================
    public:
        //Constructor
        //Have to initialize because of GFX class
        Heltec_213Red_V2( uint8_t pin_dc, uint8_t pin_cs, uint8_t pin_busy) : GFX(panel_width, panel_height),
                                                                                pin_dc(pin_dc), 
                                                                                pin_cs(pin_cs), 
                                                                                pin_busy(pin_busy)
                                                                        { //Pass references to nested classes
                                                                            this->bounds = Bounds(  &winrot_top, 
                                                                                                    &winrot_right, 
                                                                                                    &winrot_bottom, 
                                                                                                    &winrot_left, 
                                                                                                    &rotation); }
                                                                                
        //Graphics overloads and config methods                                                                
        void drawPixel(int16_t x, int16_t y, uint16_t color);
        void setDefaultColor(uint16_t bgcolor);
        size_t write(uint8_t c);
        void charBounds(unsigned char c, int16_t *x, int16_t *y, int16_t *minx, int16_t *miny, int16_t *maxx, int16_t *maxy);

        //Paging and Hardware methods
        void begin() {begin(pageSize.MEDIUM);}
        void begin(PageProfile page_size, void (*wake_callback)(void) = NULL, void (*sleep_callback)(void) = NULL);
        bool calculating(RegionList::Region update_region, uint8_t left, uint8_t top, uint8_t width, uint8_t height);
        bool calculating(RegionList::Region update_region = region.FULLSCREEN);
        void update(bool blocking = true);
        bool busy() {return digitalRead(pin_busy);}
        void clear();

    private:    //Hardware methods
        void grabPageMemory();
        void freePageMemory();

        void sendCommand(uint8_t command);
        void sendData(uint8_t data);
        void wake();
        void wait();
        void clearPage(uint16_t bgcolor);
        void writePage();

    private:
        private:   //Screen-mode specific methods
        bool calculating_Fullscreen();
        bool calculating_Windowed();

        void drawPixel_Fullscreen(int16_t x, int16_t y, uint16_t color);
        void drawPixel_Windowed(int16_t x, int16_t y, uint16_t color);

        void writePage_Fullscreen();
        void writePage_Windowed();

    private:    //Deleted methods
        using GFX::drawGrayscaleBitmap;
        using GFX::drawRGBBitmap;
        using GFX::invertDisplay;

    //Supplementary Drawing Methods
    //========================================================================================

    //==================================
    //  Messy, here is current structure:
    //      setCursorTopLeft
    //      getTextWidth
    //      getTextHeight
    //
    //      Bounds ->
    //          Window->
    //                  Left
    //                  Right
    //                  Top
    //                  Bottom
    //                  Width
    //                  Height
    //          Full->
    //                  Left
    //                  Right
    //                  Top
    //                  Bottom
    //                  Width
    //                  Height
    //==================================

    public:
        void setFlip(FlipList::Flip flip);
        void setCursorTopLeft(const char* text, uint16_t x, uint16_t y);
        uint16_t getTextWidth(const char* text);
        uint16_t getTextHeight(const char* text);

        class Bounds { 
            public:
                    //Reference dimensions for windows
                    class Window {
                        public:
                            uint8_t top();
                            uint8_t right();
                            uint8_t bottom();
                            uint8_t left();

                            uint8_t width() {return right() - left();}
                            uint8_t height() {return bottom() - top();}

                            uint8_t centerX() {return right() - (width() / 2);}
                            uint8_t centerY() {return bottom() - (height() / 2);}

                            Window(uint8_t *top, uint8_t *right, uint8_t *bottom, uint8_t *left, uint8_t *arg_rotation) {
                                                                                                                            edges[T] = top;
                                                                                                                            edges[R] = right;
                                                                                                                            edges[B] = bottom;
                                                                                                                            edges[L] = left;
                                                                                                                            m_rotation = arg_rotation;
                                                                                                                        }  //Called in setup
                            Window() = delete;  //Please use a pointer instead 
                        private:
                            uint8_t *edges[4];   //t, r, b, l
                            uint8_t *m_rotation;    //NB: "rotation" is already used as member
                            enum side{T=0, R=1, B=2, L=3};
                        };
                        Window window = Window(nullptr, nullptr, nullptr, nullptr, nullptr);    //Prevent user instantiating class without due care

                    //Reference dimensions for fullscreen
                    class Full {
                        public:
                            uint8_t left() {return 0;}
                            uint8_t right() {return ((*rotation % 2) ? drawing_height : drawing_width) - 1;}   //Width if portrait, height if landscape
                            uint8_t top() {return 0;}
                            uint8_t bottom() {return ((*rotation % 2) ? drawing_width : drawing_height) - 1;}  //Height if portrait, width if landscape

                            uint8_t width() {return right();}
                            uint8_t height() {return bottom();}

                            uint8_t centerX() {return (right() / 2);}
                            uint8_t centerY() {return (bottom() / 2);}

                            Full(uint8_t *arg_rotation) : rotation(arg_rotation) {}
                            Full() = delete;    //Please use a pointer instead
                        private:
                            uint8_t *rotation;
                    };
                    Full full = Full(nullptr);  //Prevent untintentional instantiation

                    Bounds() = delete;  //Please use a pointer instead
                    Bounds(uint8_t *top, uint8_t *right, uint8_t *bottom, uint8_t *left, uint8_t *arg_rotation) {
                                                                                                                    window = Window(top, right, bottom, left, arg_rotation);
                                                                                                                    full = Full(arg_rotation);
                                                                                                                }      
                    };
        Bounds bounds = Bounds(nullptr, nullptr, nullptr, nullptr, nullptr); 

    //Members
    //=========================================================================================

    private:
        uint8_t pin_dc, pin_cs, pin_busy;

        void (*wake_callback)(void);
        void (*sleep_callback)(void);
        
        PageProfile page_profile;
        uint16_t page_bytecount;
        uint16_t pagefile_length = 0;   //Marks the amount of data to be written from pagefile, in case of window
        uint8_t *page_black;
        uint8_t *page_red;
        uint8_t page_cursor = 0;
        uint8_t page_top, page_bottom;  //Counters

        uint16_t default_color = colors.WHITE;
        FlipList::Flip imgflip = FlipList::NONE;


        //Values defining windowed updated region
        RegionList::Region update_region;
        uint8_t window_left, window_top, window_right, window_bottom;
        uint8_t winrot_left, winrot_top, winrot_right, winrot_bottom;   //Window boundaries in reference frame of rotation(0)

};