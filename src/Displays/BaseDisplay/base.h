/* 
    File: base.h

        - Base class, from which all displays derive
*/

#ifndef __BASE_DISPLAY_H__
#define __BASE_DISPLAY_H__

#include <Arduino.h>
#include <SPI.h>

#include "GFX_Root/GFX.h"

#include "Environments/environments.h"
#include "Bounds/bounds.h"
#include "Displays/BaseDisplay/enums.h"

class BaseDisplay: public GFX {

    public:
        // Constructor
        BaseDisplay (   uint8_t pin_dc, 
                        uint8_t pin_cs, 
                        uint8_t pin_busy, 
                        uint8_t pin_sdi, 
                        uint8_t pin_clk,
                        int16_t page_height );

        // Destructor
        ~BaseDisplay() {
            Serial.println("destructor called");
        }

        // Virtual methods from AdafruitGFX base                                                               
        void drawPixel(int16_t x, int16_t y, uint16_t color);       // Where pixel output of AdafruitGFX is intercepted
        void setDefaultColor(uint16_t bgcolor);                     // Set default background color for drawing
        void setRotation(uint8_t r);                                // Store rotation val, and recalculate window dimensions

        enum Fastmode : int8_t {OFF, ON, TURBO, NOT_SET = -1};      // Different display update techniques. Enum for internal use only
        void fastmodeOff();                                         // Use full refresh
        virtual void fastmodeOn();                                  // Use Partial refresh, double pass. Deletable by derived class
        virtual void fastmodeTurbo();                               // Use Partial refresh, single pass. Deletable by derived class

        void fullscreen();                                          // Use whole screen area for drawing
        void setWindow(uint16_t left, uint16_t top, uint16_t width, uint16_t height);       // Specify a section of screen for drawing

        void clear();                                               // Public clear() method. Obligatory refresh
        void deepSleep(uint16_t pause = 500);                       // Enter power-saving mode. Display requires power-cycle to wake
        bool calculating();                                         // Main method controlling paging. while( calculating() )
        #define DRAW(display) while(display.calculating())          // Macro to call while(.calculating())

        #if PRESERVE_IMAGE
            void overwrite();
        #else
            /* --- Error: Microcontroller doesn't have enough RAM. Use a DRAW() loop instead --- */       void overwrite() = delete;
        #endif


    protected:
        void init();
        void grabPageMemory();                                      // Allocate dynamic memory to the pagefile(s) (image buffer)
        void freePageMemory();                                      // Release pagefile memory
        void sendCommand(uint8_t command);                          // Send SPI Command to display (see datasheets)
        void sendData(uint8_t data);                                // Send SPI data to display
     
        void clear(bool refresh);                                   // Clear display memory, with optional update
        void clearPage(uint16_t bgcolor);                           // Fill the pagefile(s) with default_color
        void writePage();                                           // Send image data to display memory (no refresh)

        void reset();                                               // Soft-reset the dispaly
        void wait();                                                // Pause until the display can accept new commands

        // Virtual methods from AdafruitGFX base
        // Overriden to implement text-wrapping in window                                                       
        size_t write(uint8_t c);            
        void charBounds(unsigned char c, 
                        int16_t *x, int16_t *y, 
                        int16_t *minx, int16_t *miny, 
                        int16_t *maxx, int16_t *maxy);


    // Defined in derived class
    protected:
        virtual void specifyMemoryArea( int16_t &sx, int16_t &sy, int16_t &ex, int16_t &ey ) = 0;   // Area of display memory to accept data
        virtual void configFull() {};                               // Load display specific settings for full refresh
        virtual void configPartial() {};                            // Load display specific settings for partial refresh
        virtual void activate() = 0;                                // Perform the display update, "master activation"


    // Drawing helpers
    public:
        bool supportsColor(Color c);                                // Does display support given color
        uint16_t getTextWidth(const char* text);                    // Width of text, when rendered
        uint16_t getTextHeight(const char* text);                   // Height of text, when rendered
        uint16_t getTextCenterX(const char* text);                  // X co-ord required to horizontally center text
        uint16_t getTextCenterY(const char* text);                  // Y co-ord required to vertically center text
        void setFlip(Flip flip);                                    // Mirror the display along specified axis                                
        void setCursorTopLeft(const char* text, uint16_t x, uint16_t y);        // Place text by top-leftmost pixel                     
        
        // Subclass. Information about screen and window
        Bounds bounds;


    // Disabled AdafruitGFX methods
    private:
        using GFX::availableForWrite;
        using GFX::clearWriteError;
        using GFX::drawGrayscaleBitmap;
        using GFX::drawRGBBitmap;
        using GFX::flush;
        using GFX::getWriteError;
        using GFX::GFX;
        using GFX::invertDisplay;
        using GFX::write;


    // Members
    protected:
        // Config received in constructor
        // -------------------------------
        uint8_t pin_dc;                                             // Display / Command
        uint8_t pin_cs;                                             // Chip Select
        uint8_t pin_busy;                                           // Can display accept new commands
        uint8_t pin_sdi;                                            // "MOSI". Unless CAN_SPECIFY_SPI_PINS, value is -1
        uint8_t pin_clk;                                            // "SCK". Unless CAN_SPECIFY_SPI_PINS, value is -1
        uint16_t pagefile_height;                                   // How many vertical lines per page
        uint16_t panel_width, panel_height;                         // True dimensions
        uint16_t drawing_width, drawing_height;                     // Usable dimensions
        Color supported_colors;                                     // Colors supported by the display
        // --------------------------------

        // SPI
        const SPISettings spi_settings = SPISettings(200000, MSBFIRST, SPI_MODE0);

        // Drawing parameters
        uint16_t default_color = WHITE;                             // Background color of the canvas, before drawing           
        Flip imgflip = NONE;                                        // Along which Axes to mirror the display
        Fastmode fastmode_state = NOT_SET;                          // Which update technique is in use (Full, Partial, Partial "double pass")

        // Paging
        uint16_t page_bytecount;                                    // Size of each pagefile (image buffer)
        uint16_t pagefile_length = 0;                               // Amount of pagefile utilized (by current window)

        uint16_t page_cursor = 0;                                   // How many pages processed so far. Each update resets.
        uint16_t page_top, page_bottom;                             // Which rows to be considered when drawing on current page

        uint8_t *page_black;                                        // Dynamic memory which stores black image bits
        uint8_t *page_red;                                          // Dynamic memory which stores red image bits (if required)

        bool fastmode_secondpass = true;                            // Is this pass the first or second? Relevant when Fastmode::ON

        // Mode settings
        uint16_t window_left, window_top, window_right, window_bottom;      // Window boundaries: reference frame of current retation
        uint16_t winrot_left, winrot_top, winrot_right, winrot_bottom;      // Window boundaries in reference frame of rotation(0)
};

#endif