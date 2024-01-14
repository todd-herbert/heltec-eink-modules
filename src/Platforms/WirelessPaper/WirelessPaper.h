#include <Arduino.h>
#include <SPI.h>

// Specific options for ESP32

#ifndef __WIRELESS_PAPER_H__
#define __WIRELESS_PAPER_H__

    // Catch outdated board definitions, or PlatformIO users 
    #if defined(ARDUINO_heltec_wifi_lora_32_V3) || defined(WIFI_LoRa_32_V3)
        #define WIRELESS_PAPER true
    #endif

    // If building for "Wireless Paper".
    #ifdef WIRELESS_PAPER 

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
        #define CAN_SPECIFY_SPI_PINS    false
        #define DEFAULT_SDI             2
        #define DEFAULT_CLK             3
        
        // Paging
        #define DEFAULT_PAGE_HEIGHT     panel_height    // Indicate that we want the full display 
        #define MAX_PAGE_HEIGHT         panel_height    // (Largest supported panel)
        #define PRESERVE_IMAGE          true            // No clearing of page file between updates

        // PCB Wiring - All in One
        #define PIN_PCB_DC              5
        #define PIN_PCB_CS              4
        #define PIN_PCB_BUSY            7
        #define PIN_PCB_RST             6
        #define PIN_PCB_VEXT            45              // Power to all peripherals on PCB, active LOW

        // Platform-specific methods
        namespace Platform {
            extern SPIClass* getSPI();                                                                      // Pass the correct SPI bus to display class
            extern void beginSPI(SPIClass *spi, uint8_t pin_mosi, uint8_t pin_miso, uint8_t pin_clk);       // Call the appropriate SPI begin method                        // SAMD21G18A: move spi, if useSD() has been called
            extern void interfacesOn();
            extern void interfacesOff();
            extern void toggleResetPin();
        }

    #endif

#endif