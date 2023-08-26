#include <Arduino.h>
#include <SPI.h>
#include "GFX_Root/GFX.h"
#include "Enviros/enviros.h"

/// Heltec 2.13" Red V2
/// Declaration: QYEG0213RWS800(  d/c pin  , cs pin , busy pin )
class QYEG0213RWS800 : public GFX {

    // Consts
    // ===================
    private:
        // These are correct for the Heltect 2.13" Red V2, but are still defined here for easy access
        const SPISettings spi_settings = SPISettings(200000, MSBFIRST, SPI_MODE0);
        static const uint16_t panel_width = 128;
        static const uint16_t panel_height = 250;
        static const int16_t drawing_width = 122;  // Panel needs 128 * 250 bytes of data, however the useful drawing area is slightly smaller
        static const int16_t drawing_height = 250;

    // Consts for user config
    // ======================
    public:
        static struct FlipList{enum Flip{NONE = 0, HORIZONTAL=1, VERTICAL=2, HORIZONTAL_WINDOW=5, VERTICAL_WINDOW=6}; } flip;
        static struct ColorList{enum Colors{BLACK = 0, WHITE = 1, RED = 3}; } colors;
        static struct RotationList {enum Rotations{PINS_ABOVE = 0, PINS_LEFT=1, PINS_BELOW = 2, PINS_RIGHT = 3};} orientation;  // NB: member is "orientation", as GFX::rotation already exists
    
    // Methods
    // =============================================================================
    public:
        // Constructor
        QYEG0213RWS800( uint8_t pin_dc, uint8_t pin_cs, uint8_t pin_busy, uint16_t page_height = DEFAULT_PAGE_HEIGHT);
                                                                                
        // Graphics overrides and config methods                                                                
        void drawPixel(int16_t x, int16_t y, uint16_t color);
        void setDefaultColor(uint16_t bgcolor);
        void setRotation(uint8_t r);

        // Paging and Hardware methods
        void fullscreen();
        void setWindow(uint8_t left, uint8_t top, uint8_t width, uint8_t height);
        bool calculating();
        void update();
        void clear();
        void deepSleep(uint16_t pause = 500);

    private:    // Hardware methods
        void grabPageMemory();
        void freePageMemory();
        void sendCommand(uint8_t command);
        void sendData(uint8_t data);
        void reset();
        bool busy() {return digitalRead(pin_busy);}
        void wait();
        void clearPage(uint16_t bgcolor);
        void writePage();

        // Graphics overrides and config methods                                                                
        size_t write(uint8_t c);
        void charBounds(unsigned char c, int16_t *x, int16_t *y, int16_t *minx, int16_t *miny, int16_t *maxx, int16_t *maxy);

    private:    // Deleted methods
        using GFX::availableForWrite;
        using GFX::clearWriteError;
        using GFX::drawGrayscaleBitmap;
        using GFX::drawRGBBitmap;
        using GFX::flush;
        using GFX::getWriteError;
        using GFX::GFX;
        using GFX::invertDisplay;
        using GFX::write;

    // Supplementary Drawing Methods
    // ========================================================================================
    //
    //  Messy, here is current structure:
    //      setFlip
    //      setCursorTopLeft
    //      getTextWidth
    //      getTextHeight
    //      getTextCenterX
    //      getTextCenterY
    // 
    //      Bounds ->
    //          Window->
    //                  Top
    //                  Right
    //                  Bottom
    //                  Left
    //                  Width
    //                  Height
    //                  CenterX
    //                  CenterY
    //          Full->
    //                  Top
    //                  Right
    //                  Bottom
    //                  Left
    //                  Width
    //                  Height
    //                  CenterX
    //                  CenterY
    // ==================================

    public:
        void setFlip(FlipList::Flip flip);
        void setCursorTopLeft(const char* text, uint16_t x, uint16_t y);
        uint16_t getTextWidth(const char* text);
        uint16_t getTextHeight(const char* text);
        uint16_t getTextCenterX(const char* text);
        uint16_t getTextCenterY(const char* text);      

        // Nested Subclasses to provide dimensioning info
        class Bounds { 
            public:
                    // Reference dimensions for windows
                    class Window {
                        public:
                            // TODO: Bounds.Window subclass with info about "Requested Bounds" vs "Actual Bounds"
                            // TODO: calculate window boundaries early to facilitate user layout calculation

                            uint8_t top();
                            uint8_t right();
                            uint8_t bottom();
                            uint8_t left();

                            uint8_t width() {return right() - left() + 1;}
                            uint8_t height() {return bottom() - top() + 1;}

                            uint8_t centerX() {return right() - ((width() - 1) / 2);}
                            uint8_t centerY() {return bottom() - ((height() - 1) / 2);}

                            // Subclass constructor, receive references to display dimensions
                            Window(uint8_t *top, uint8_t *right, uint8_t *bottom, uint8_t *left, uint8_t *arg_rotation, FlipList::Flip *arg_imgflip) {
                                edges[T] = top;
                                edges[R] = right;
                                edges[B] = bottom;
                                edges[L] = left;
                                m_rotation = arg_rotation;
                                m_imgflip = arg_imgflip;
                            }
                            Window() = delete;  // User shouldn't instantiate this class
                        private:
                            uint8_t *edges[4];   // t, r, b, l
                            uint8_t *m_rotation;    // note: "rotation" is already used as member
                            FlipList::Flip *m_imgflip;
                            enum side{T=0, R=1, B=2, L=3};
                            uint8_t getWindowBounds(side request);  // backend function, does most of the work finding window dimensions
                    };
                    Window window = Window(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);    // Have to pretend-instantiate, because we deleted default constructor

                    // Reference dimensions for fullscreen
                    class Full {
                        public:
                            uint8_t left() {return 0;}
                            uint8_t right() {return width() - 1;}   
                            uint8_t top() {return 0;}
                            uint8_t bottom() {return height() - 1;}

                            uint8_t width() {return ((*rotation % 2) ? drawing_height : drawing_width);} // Width if portrait, height if landscape
                            uint8_t height() {return ((*rotation % 2) ? drawing_width : drawing_height);}

                            uint8_t centerX() {return (right() / 2);}
                            uint8_t centerY() {return (bottom() / 2);}

                            Full(uint8_t *arg_rotation) : rotation(arg_rotation) {}
                            Full() = delete;    // User shouldn't instantiate this class
                        private:
                            uint8_t *rotation;
                    };
                    Full full = Full(nullptr);  // Have to pretend-instantiate, because we deleted default constructor

                    // Subclass Constructor, receive the dimension references, to pass on to "window" and "full"
                    Bounds(uint8_t *top, uint8_t *right, uint8_t *bottom, uint8_t *left, uint8_t *arg_rotation, FlipList::Flip *arg_flip) {
                        window = Window(top, right, bottom, left, arg_rotation, arg_flip);
                        full = Full(arg_rotation);
                    }      
                    Bounds() = delete;  // User shouldn't instantiate this class
        };

        Bounds bounds = Bounds(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);   // Have to pretend-instantiate, because we deleted default constructor

    // Members
    // =========================================================================================

    private:
        uint8_t pin_dc, pin_cs, pin_busy;

        uint16_t default_color = colors.WHITE;
        FlipList::Flip imgflip = FlipList::NONE;
        
        // Paging
        uint8_t pagefile_height;
        uint16_t page_bytecount;
        uint8_t *page_black;
        uint8_t *page_red;
        uint16_t pagefile_length = 0;   // Marks the amount of data to be written from pagefile


        uint8_t page_cursor = 0;
        uint8_t page_top, page_bottom;  // Counters


        // Values defining windowed updated region
        uint8_t window_left, window_top, window_right, window_bottom;
        uint8_t winrot_left, winrot_top, winrot_right, winrot_bottom;   // Window boundaries in reference frame of rotation(0)
};