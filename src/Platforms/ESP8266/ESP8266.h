// Specific options for ESP8266

#ifndef __ESP8266_H__
#define __ESP8266_H__

    // If building for ESP32
    #ifdef ESP8266

        #include <Arduino.h>
        #include <SPI.h>

        // Redefine macros with AVR version
        #define min(a,b) ((a)<(b)?(a):(b))
        #define max(a,b) ((a)>(b)?(a):(b))
        #define abs(x) ((x)>0?(x):-(x))
        #define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

        // Don't use fallback settings
        #define PLATFORM_SUPPORTED

        // SPI
        #define CAN_MOVE_SPI_PINS       false
        #define DEFAULT_SDI             -1
        #define DEFAULT_CLK             -1

        // Paging
        #define DEFAULT_PAGE_HEIGHT     panel_height    // Indicate that we want the full display 
        #define MAX_PAGE_HEIGHT         296             // (Largest supported panel)
        #define PRESERVE_IMAGE          true            // No clearing of page file between updates

        // Platform-specific methods
        namespace Platform{
            extern SPIClass* getSPI();                                                                      // Pass the correct SPI bus to display class
            extern void beginSPI(SPIClass *spi, uint8_t pin_mosi, uint8_t pin_miso, uint8_t pin_clk);       // Call the appropriate SPI begin method                        // SAMD21G18A: move spi, if useSD() has been called
        }

    #endif

#endif