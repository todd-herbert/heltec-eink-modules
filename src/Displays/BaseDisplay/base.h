/* 
    File: base.h

        - Base class, from which all displays derive
*/

#ifndef __BASE_DISPLAY_H__
#define __BASE_DISPLAY_H__

#include <Arduino.h>
#include <SPI.h>

#include "optimization.h"   // Compile-time size reduction, configurable

#include "GFX_Root/GFX.h"
#include "SDWrapper/sd_wrapper.h"

#include "Platforms/platforms.h"
#include "Bounds/bounds.h"
#include "Displays/BaseDisplay/enums.h"

class BaseDisplay: public GFX {

    public:
        // Constructor
        BaseDisplay ( uint8_t pin_dc, uint8_t pin_cs, uint8_t pin_busy, uint8_t pin_sdi, uint8_t pin_clk, int16_t page_height );

        // Destructor
        ~BaseDisplay() {
            freePageMemory();
        }

        void begin();                                               // Called from derived-class' constructor: gets access to derived-class parameters, and runs hardware init                              


        // Drawing params & AdafruitGFX overrides                                                    
        void drawPixel(int16_t x, int16_t y, uint16_t color);       // Where pixel output of AdafruitGFX is intercepted
        void setBackgroundColor(uint16_t bgcolor);                  // Set default background color for drawing
        void setRotation(int16_t r);                                // Store rotation val, and recalculate window dimensions
        void landscape() { setRotation(3); }                        // Alias for setRotation(3) - ideal orientation for wireless paper
        void portrait() { setRotation(0); }                         // Alias for setRotation(0)
        void setCursor(int16_t x, int16_t y);                       // Hijack the values, then pass through
        void setDefaultColor(uint16_t bgcolor) { setBackgroundColor(bgcolor); }     // DEPRECATED


        // Fastmode (partial refresh)
        enum Fastmode : int8_t {OFF, ON, TURBO, NOT_SET = -1};      // Different display update techniques. Enum for internal use only
        void fastmodeOff();                                         // Use full refresh
        virtual void fastmodeOn();                                  // Use Partial refresh, double pass. Deletable by derived class
        virtual void fastmodeTurbo();                               // Use Partial refresh, single pass. Deletable by derived class


        // Window (only important when paging)
        void fullscreen();                                                                  // Use whole screen area for drawing
        void setWindow(uint16_t left, uint16_t top, uint16_t width, uint16_t height);       // Specify a section of screen for drawing
        

        // Power saving 
        void useCustomPowerSwitch(uint8_t pin, SwitchType type);    // Store the config for user's power switching circuit
        void customPowerOff(uint16_t pause = 500);                  // "Power off" signal to user's power circuit, and set logic pins appropriately
        void customPowerOn();                                       // "Power on" signal to user's circuit, then re-init display
        #define usePowerSwitching(pin, type) useCustomPowerSwitch(pin, type)        // DEPRECATION
        #define externalPowerOff customPowerOff                                     // DEPRECATION
        #define externalPowerOn customPowerOn                                       // DEPRECATION


        // Paging and Refresh
        void clear();                                               // Public clear() method. Obligatory refresh
        bool calculating();                                         // Main method controlling paging. while( calculating() )
        #define DRAW(display) while(display.calculating())          // Macro to call while(.calculating())
        #if PRESERVE_IMAGE
            void update();                                          // Non-paged: display the result of drawing.
            void clearMemory();                                     // Non-paged: clear the pagefile (which is full screen-height)
            void overwrite()        { update(); }                   // DEPRECATION
            void startOver()        { clearMemory(); }              // DEPRECATION
        #else
            // If MCU not capable, tell the user to DRAW() instead
            /* --- Error: Microcontroller doesn't have enough RAM. Use a DRAW() loop instead --- */       void update() = delete;
            /* --- Error: Microcontroller doesn't have enough RAM. Use a DRAW() loop instead --- */       void clearMemory() = delete;
            /* --- Error: Microcontroller doesn't have enough RAM. Use a DRAW() loop instead --- */       void overwrite() = delete;        // DEPRECATION
            /* --- Error: Microcontroller doesn't have enough RAM. Use a DRAW() loop instead --- */       void startOver() = delete;        // DEPRECATION
        #endif


        // SD card
        // ----------------------------
        #ifndef DISABLE_SDCARD  // optimization.h, WirelessPaper.h

            void useSD(uint8_t pin_cs_card);                                                                                            // Store the config needed to use SD Card
            bool SDCardFound();                                                                                                         // Check if card is connected
            bool SDFileExists(const char* filename);                                                                                    // Check if file exists on SD card                                         
            bool SDCanvasExists(uint16_t number);                                                                                       // Check if file exists, by "canvas number"
            bool SDCanvasExists(const char* filename);                                                                                  // Synonym for SDFileExists()
            bool SDCanvasValid(uint16_t number, bool purge = false);                                                                    // Check for corruption in a canvas .bmp, by "canvas number"
            bool SDCanvasValid(const char* filename, bool purge = false);                                                               // Check for corruption in a canvas .bmp
            void drawMonoBitmapFile(int16_t left, int16_t top, const char* filename, Color color);                                      // Draw a mono bitmap from SD Card
            void drawMonoBitmapFile(int16_t left, int16_t top, const char* filename, Color foreground_color, Color background_color);   // Draw a mono bitmap from SD Card, with background
            void loadCanvas(const char* filename);                                                                                      // Draw canvas from SD card, direct to screen
            void loadCanvas(uint16_t number);                                                                                           // Draw canvas (numbered) from SD, direct to screen 
            void loadFullscreenBitmap(const char* filename)       { loadCanvas(filename); }                                             // Load and display a full-size bitmap. Wrapper for loadCanvas
            uint16_t getBMPWidth(const char* filename);                                                                                 // Read image width from .bmp header, sd card
            uint16_t getBMPHeight(const char* filename);                                                                                // Read image height from .bmp header, sd card        
            #define SAVE_CANVAS(display, canvas) while(display.savingCanvas(canvas))                                                   // Macro to call while.savingCanvas()
            #define WRITE_CANVAS(display, canvas) while(display.savingCanvas(canvas))                                                  // DEPRECATED


            // Configure the SD card reader
            #if CAN_MOVE_SPI_PINS
                void useSD(uint8_t pin_cs_card, uint8_t pin_miso);
            #else
                /* --- Error: This model of microcontroller can't move SPI pins around --- */       void useSD(uint8_t pin_cs_card, uint8_t pin_miso) = delete;
            #endif


            // Draw 24bit bitmap from SD
            #ifndef __AVR_ATmega328P__
                void draw24bitBitmapFile(int16_t left, int16_t top, const char* filename);
                void draw24bitBitmapFile(int16_t left, int16_t top, const char* filename, Color mask);
                void draw24bitBitmapFile(int16_t left, int16_t top, const char* filename, uint8_t mask_r, uint8_t mask_g, uint8_t mask_b, bool apply_mask = true);
            #else
                /* --- Error: Not enough RAM, use drawMonoBitmapFile() instead  --- */              void draw24bitBitmapFile(int16_t left, int16_t top, const char* filename) = delete;
                /* --- Error: Not enough RAM, use drawMonoBitmapFile() instead  --- */              void draw24bitBitmapFile(int16_t left, int16_t top, const char* filename, Color transparency) = delete;            
                /* --- Error: Not enough RAM, use drawMonoBitmapFile() instead  --- */              void draw24bitBitmapFile(int16_t left, int16_t top, const char* filename, uint8_t mask_r, uint8_t mask_g, uint8_t mask_b, bool apply_mask = true) = delete;            
            
            #endif


            // SD write: Potentially disabled by optimization.h
            #if !defined(__AVR_ATmega328P__) || defined(UNO_ENABLE_SDWRITE)
                bool savingCanvas(const char* filename);                                                                                   // Non-paged: write memory to canvas (numbered)
                bool savingCanvas(uint16_t number);                                                                                        // Non-paged: write memory to canvas 
            #else
                /* --- Error: SD Write disabled by config in optimization.h --- */                  bool savingCanvas(const char* filename) = delete;
                /* --- Error: SD Write disabled by config in optimization.h --- */                  bool savingCanvas(uint16_t number) = delete;
            #endif
            

            // Non-paged: write canvas to SD card
            #if PRESERVE_IMAGE
                void saveCanvas(const char* filename);
                void saveCanvas(uint16_t number);
            #else
                /* --- Error: Not enough RAM, use SAVE_CANVAS() instead --- */         void saveCanvas(const char* filename) = delete;
                /* --- Error: Not enough RAM, use SAVE_CANVAS() instead --- */         void saveCanvas(uint16_t number) = delete;
            #endif

        #endif  // ! DISABLE_SDCARD
        // ---------------

        // Drawing helpers
        Bounds bounds;                                                          // Dimension info about screen and window
        bool supportsColor(Color c);                                            // Does display support given color
        uint16_t getTextWidth(const char* text);                                // Width of text, when rendered
        uint16_t getTextWidth(const String &text);                  
        uint16_t getTextHeight(const char* text);                               // Height of text, when rendered
        uint16_t getTextHeight(const String &text);         
        uint16_t getTextCenterX(const char* text);                              // X co-ord required to horizontally center text
        uint16_t getTextCenterX(const String &text);            
        uint16_t getTextCenterY(const char* text);                              // Y co-ord required to vertically center text
        uint16_t getTextCenterY(const String &text);            
        void setFlip(Flip flip);                                                // Mirror the display along specified axis                                
        void setCursorTopLeft(const char* text, uint16_t x, uint16_t y);        // Place text by top-leftmost pixel  
        void setCursorTopLeft(const String &text, uint16_t x, uint16_t y);
        #if __INT_MAX__ != __INT16_MAX__
            // For platforms where int is not 16bit: Fix a parameter issue with AdafruitGFX
            void getTextBounds(const char *str, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h);
            void getTextBounds(const String & str, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h);
            void getTextBounds(const __FlashStringHelper * str, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h);
            void getTextBounds(const char *str, int x, int y, int *x1, int *y1, unsigned int *w, unsigned int *h);
            void getTextBounds(const String & str, int x, int y, int *x1, int *y1, unsigned int *w, unsigned int *h);
            void getTextBounds(const __FlashStringHelper * str, int x, int y, int *x1, int *y1, unsigned int *w, unsigned int *h);  
        #endif


    protected:
        // Initial setup
        void instantiateBounds();                       // Called by derived class constructor, asap, so globals can be initialized with bounds() info
        void initDrawingParams();                       // Set drawing config early: if placed in begin(), may be over-written by user's early config


        // Display interaction
        virtual void reset();                           // Reset the display. Overriden for Fitipower ICs
        virtual void wait();                            // Pause until the display can accept new commands. Overriden for Fitipower ICs
        void sendCommand(uint8_t command);              // Send SPI Command to display (see datasheets)
        void sendData(uint8_t data);                    // Send SPI data to display
        virtual void sendImageData();                   // Send image over SPI to display's memory. Overriden for Fitipower ICs
        virtual void sendBlankImageData();              // Send a full frame of black data over SPI to display's memory. Overriden for Fitipower ICs


        // Paging and Refresh
        void grabPageMemory();                                                                              // Allocate dynamic memory to the pagefile(s) (image buffer)
        void freePageMemory();                                                                              // Release pagefile memory
        void setWindow(uint16_t left, uint16_t top, uint16_t width, uint16_t height, bool clear_page);      // (hide final parameter from user)
        virtual void setMemoryArea(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey);                     // Inform the display of selected memory area. Overriden if no "partial window" support
        void writePage();                                                                                   // Send image data to display memory (no refresh)
        virtual void clearPage(uint16_t bgcolor);                                                           // Fill the pagefile(s) with default_color. Overriden if no "partial window" support
        virtual void clearPageWindow();                                                                     // Clear page area where new window-data will go. Overriden if no "partial window" support
        void clear(bool refresh);                                                                           // Clear display memory, with optional update
 

        // SD card
        #ifndef DISABLE_SDCARD  // optimization.h, WirelessPaper.h
            void send24BitBMP(Color target);                                    // Feed .bmp into sendData()
            Color parseColor(uint8_t B, uint8_t G, uint8_t R);                  // Get a Color enum. from a 24bit bgr pixel
            void initCanvas(const char* filename);                               // Write a template .bmp to sd card
            void writePageToCanvas();                                           // Write one page to the canvas file
        #endif


        // AdafruitGFX virtual: modified to fix text wrapping                                    
        size_t write(uint8_t c);            
        void charBounds(unsigned char c, int16_t *x, int16_t *y, int16_t *minx, int16_t *miny, int16_t *maxx, int16_t *maxy);


        // Derived class: config for specific display models
        virtual void calculateMemoryArea( int16_t &sx, int16_t &sy, int16_t &ex, int16_t &ey ) = 0;                 // Calculate area of display memory to accept data
        virtual void configPartial() {};                                                                            // Load display specific settings for partial refresh
        virtual void configFull() {};                                                                               // Load display specific settings for full refresh
        virtual void activate() = 0;                                                                                // Perform the display update, "master activation"
        virtual void calculatePixelPageOffset(uint16_t x, uint16_t y, uint16_t &byte_offset, uint8_t &bit_offset); // Calculate byte location of pixel in pagefile. Overriden if no "partial window" support


        // Config received in constructor
        uint8_t pin_dc;                                             // Display / Command
        uint8_t pin_cs;                                             // Chip Select
        uint8_t pin_busy;                                           // Can display accept new commands
        uint8_t pin_sdi;                                            // "MOSI". Unless CAN_MOVE_SPI_PINS, value is -1
        uint8_t pin_clk;                                            // "SCK". Unless CAN_MOVE_SPI_PINS, value is -1
        uint16_t pagefile_height;                                   // How many vertical lines per page
        uint16_t panel_width, panel_height;                         // True dimensions
        uint16_t drawing_width, drawing_height;                     // Usable dimensions
        Color supported_colors;                                     // Colors supported by the display


        // SPI
        SPIClass *display_spi;                                                          // SPI instance is platform specific
        const SPISettings spi_settings = SPISettings(200000, MSBFIRST, SPI_MODE0);
        bool begun = false;                                                             // Has BaseDisplay::begin run once?


        // SD
        SDWrapper* sd;                                              // Dynamically allocated SD instance
        uint8_t pin_miso = MISO;                                    // Set in useSD(). Relevant to SAMD21 pin muxing
        uint8_t pin_cs_card = -1;                                   // Set in useSD()
        bool saving_canvas = false;                                 // Are drawing operations currently diverted into a bmp file?
        const char* canvas_filename;                                // Pass filename to writePageToCanvas()


        // External power switch
        uint8_t pin_power = -1;                                     // Pin connected to switch / transistor gate
        SwitchType switch_type = PNP;                               // Type of switch / transistor
        bool just_restarted = false;                                // Track whether display memory was lost (re: fastmodeON)


        // Drawing parameters
        uint16_t default_color = WHITE;                             // Background color of the canvas, before drawing           
        Flip imgflip = NONE;                                        // Along which Axes to mirror the display
        int16_t cursor_placed_x = 0;                                // X value of last setCursor() call (re: println, text wrapping)


        // Paging
        uint16_t page_bytecount;                                    // Size of each pagefile (image buffer)
        uint16_t pagefile_length = 0;                               // Amount of pagefile utilized (by current window)
        uint16_t page_cursor = 0;                                   // How many pages processed so far. Each update resets.
        uint16_t page_top, page_bottom;                             // Which rows to be considered when drawing on current page
        uint8_t *page_black;                                        // Dynamic memory which stores black image bits
        uint8_t *page_red;                                          // Dynamic memory which stores red image bits (if required)


        // Fastmode
        Fastmode fastmode_state = NOT_SET;                          // Which update technique is in use (Full, Partial, Partial "double pass")
        bool fastmode_secondpass = false;                           // Is this pass the first or second? Relevant when Fastmode::ON
        bool display_cleared = false;                               // Whether display is clear, hopefully. (re: customPowerOn)


        // Window
        uint16_t window_left, window_top, window_right, window_bottom;      // Window boundaries: reference frame of current retation
        uint16_t winrot_left, winrot_top, winrot_right, winrot_bottom;      // Window boundaries in reference frame of rotation(0)


    private:
        // Disabled AdafruitGFX methods
        using GFX::availableForWrite;
        using GFX::clearWriteError;
        using GFX::drawGrayscaleBitmap;
        using GFX::drawRGBBitmap;
        using GFX::flush;
        using GFX::getWriteError;
        using GFX::GFX;
        using GFX::invertDisplay;
        using GFX::write;
};

#endif