#include <Arduino.h>
#include <SPI.h>
#include "GFX_Root/GFX.h"

/// Heltec 2.9" V2
/// Declaration: HTE029A1(  d/c pin  , cs pin , busy pin )
class HTE029A1 : public GFX {

    // Consts
    // ===================
    private:
        // These are correct for the Heltec 2.9" V2, but are still defined here for easy access
        const SPISettings spi_settings = SPISettings(200000, MSBFIRST, SPI_MODE0);
        static const int16_t panel_width = 128;
        static const int16_t panel_height = 296;
        static const int16_t drawing_width = 128;   // Redundant for this display, handles odd resolutions. 
        static const int16_t drawing_height = 296;

        // From Heltec. Tricky electronic setting stuff, about how to make the screen change color.
        const unsigned char lut_full[30] = {
            0x50, 0xAA, 0x55, 0xAA, 0x11, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0xFF, 0xFF, 0x1F, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        };
        const unsigned char lut_partial[30] = {
            0x10, 0x18, 0x18, 0x08, 0x18, 0x18,
            0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x13, 0x14, 0x44, 0x12,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        };	

    // Consts for user config
    // ------------------------
    public:
        static struct FlipList{enum Flip{NONE = 0, HORIZONTAL=1, VERTICAL=2}; } flip;
        static struct ColorList{enum Colors{BLACK = 0, WHITE = 1}; } colors;
        static struct FastmodeList{enum Fastmode{OFF = 0, ON = 1, FINALIZE = 2}; } fastmode;
        static struct RotationList {enum Rotations{PINS_ABOVE = 0, PINS_LEFT=1, PINS_BELOW = 2, PINS_RIGHT = 3};} orientation;  // NB: member is "orientation", as GFX::rotation already exists // TODO:rename
  
        struct PageProfile {
            uint16_t height;
            uint16_t count;
        };

        struct PageProfileList {
            const PageProfile   TINY      {.height = 4, .count = 50};      // 100kb of SRAM, 5% of total (Arduino UNO)
            const PageProfile   SMALL     {.height = 10, .count = 20};     // 250kb of SRAM, 12.5% of total (Arduino UNO)
            const PageProfile   MEDIUM    {.height = 20, .count = 10};     // 500kb of SRAM, 25% of total (Arduino UNO)
            const PageProfile   LARGE     {.height = 40, .count = 5};      // 1000kb of SRAM, 50% of total (Arduino UNO)
            // Feel free to add any other profiles you wish. The only requirement is that ".height" * count = panel height (200px)
        } pageSize;
  



    // Methods
    // =============================================================================
    public:
        // Constructor
        // Have to initialize because of GFX class
        HTE029A1( uint8_t pin_dc, uint8_t pin_cs, uint8_t pin_busy) : GFX(panel_width, panel_height),
                                                                                pin_dc(pin_dc), 
                                                                                pin_cs(pin_cs), 
                                                                                pin_busy(pin_busy)
                                                                        { // Pass references to nested classes
                                                                            this->bounds = Bounds(  &winrot_top, 
                                                                                                    &winrot_right, 
                                                                                                    &winrot_bottom, 
                                                                                                    &winrot_left, 
                                                                                                    &rotation); }
        // Graphics overloads and config methods                                                                
        void drawPixel(int16_t x, int16_t y, uint16_t color);
        void setDefaultColor(uint16_t bgcolor);
        size_t write(uint8_t c);
        void charBounds(unsigned char c, int16_t *x, int16_t *y, int16_t *minx, int16_t *miny, int16_t *maxx, int16_t *maxy);

        // Paging and Hardware methods
        void begin() {begin(pageSize.MEDIUM);}
        void begin(PageProfile page_size);
        void fullscreen();
        void setWindow(uint16_t left, uint16_t top, uint16_t width, uint16_t height);
        void setFastmode(FastmodeList::Fastmode mode);
        bool calculating();
        void update() { update(false); }
        bool busy() {return digitalRead(pin_busy);}
        void clear();
        void wait();
        void deepSleep(uint16_t pause = 50);

    private:    // Hardware methods
        void grabPageMemory();
        void freePageMemory();

        void sendCommand(uint8_t command);
        void sendData(uint8_t data);
        void reset();
        void update(bool override_checks);
        void clearPage(uint16_t bgcolor);
        void writePage();

    private:    // Deleted methods
        using GFX::drawGrayscaleBitmap;
        using GFX::drawRGBBitmap;

    // Supplementary Drawing Methods
    // ========================================================================================

    // ==================================
    //  Messy, here is current structure:
    //      setFlip
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
    // ==================================

    public:

        void setFlip(FlipList::Flip flip);
        void setCursorTopLeft(const char* text, uint16_t x, uint16_t y);
        uint16_t getTextWidth(const char* text);
        uint16_t getTextHeight(const char* text);

        class Bounds { 
            public:
                    // Reference dimensions for windows
                    class Window {
                        public:
                            // TODO: calculate window boundaries early to facilitate user layout calculation
                            //  --- problematic interplay with setRotation() method

                            // TODO: Bounds.Window subclass with info about "Requested Bounds" vs "Actual Bounds"

                            uint16_t top();
                            uint16_t right();
                            uint16_t bottom();
                            uint16_t left();

                            uint16_t width() {return right() - left() + 1;}
                            uint16_t height() {return bottom() - top() + 1;}

                            uint16_t centerX() {return right() - (width() / 2);}
                            uint16_t centerY() {return bottom() - (height() / 2);}

                            Window(uint16_t *top, uint16_t *right, uint16_t *bottom, uint16_t *left, uint8_t *arg_rotation) {
                                                                                                                            edges[T] = top;
                                                                                                                            edges[R] = right;
                                                                                                                            edges[B] = bottom;
                                                                                                                            edges[L] = left;
                                                                                                                            m_rotation = arg_rotation;
                                                                                                                        }  // Called in setup
                            Window() = delete;  // Please use a pointer instead 
                        private:
                            uint16_t *edges[4];   // t, r, b, l
                            uint8_t *m_rotation;    // NB: "rotation" is already used as member
                            enum side{T=0, R=1, B=2, L=3};
                        };
                        Window window = Window(nullptr, nullptr, nullptr, nullptr, nullptr);    // Prevent user instantiating class without due care

                    // Reference dimensions for fullscreen
                    class Full {
                        public:
                            uint16_t left() {return 0;}
                            uint16_t right() {return width() - 1;}   
                            uint16_t top() {return 0;}
                            uint16_t bottom() {return height() - 1;}

                            uint16_t width() {return ((*rotation % 2) ? drawing_height : drawing_width);} // Width if portrait, height if landscape
                            uint16_t height() {return ((*rotation % 2) ? drawing_width : drawing_height);}

                            uint16_t centerX() {return (right() / 2);}
                            uint16_t centerY() {return (bottom() / 2);}

                            Full(uint8_t *arg_rotation) : rotation(arg_rotation) {}
                            Full() = delete;    // Please use a pointer instead
                        private:
                            uint8_t *rotation;
                    };
                    Full full = Full(nullptr);  // Prevent untintentional instantiation

                    Bounds() = delete;  // Please use a pointer instead
                    Bounds(uint16_t *top, uint16_t *right, uint16_t *bottom, uint16_t *left, uint8_t *arg_rotation) {
                                                                                                                    window = Window(top, right, bottom, left, arg_rotation);
                                                                                                                    full = Full(arg_rotation);
                                                                                                                }      
                    };
        Bounds bounds = Bounds(nullptr, nullptr, nullptr, nullptr, nullptr);

    // Members
    // =========================================================================================
    private:
        uint8_t pin_dc, pin_cs, pin_busy;

        uint16_t default_color = colors.WHITE;
        FlipList::Flip imgflip = FlipList::NONE;
        FastmodeList::Fastmode mode = FastmodeList::OFF;

        // Paging
        PageProfile page_profile;
        uint16_t page_bytecount;
        uint8_t *page_black;
        uint16_t pagefile_length = 0;   // Used for windowed memory ops

        uint16_t page_cursor = 0;
        uint16_t page_top, page_bottom;  // Counters

        // Mode settings
        enum Region{FULLSCREEN = 0, WINDOWED = 1} region=FULLSCREEN;
        uint16_t window_left, window_top, window_right, window_bottom;
        uint16_t winrot_left, winrot_top, winrot_right, winrot_bottom;   // Window boundaries in reference frame of rotation(0)
        bool first_pass = true;
};