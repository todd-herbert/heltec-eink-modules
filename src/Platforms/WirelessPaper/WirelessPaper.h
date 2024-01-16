#include <Arduino.h>
#include <SPI.h>

// Specific options for "Wireless Paper" all-in-one boards

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

        // Optimization
        #define DISABLE_SDCARD          // Nobody is going to solder an SD Card reader onto these boards.. right?
        
        // Paging
        #define DEFAULT_PAGE_HEIGHT     panel_height    // On this platform, these defaults are fixed: there is currently no support for paging
        #define MAX_PAGE_HEIGHT         panel_height
        #define PRESERVE_IMAGE          true

        // PCB Wiring
        #define PIN_PCB_DC              5
        #define PIN_PCB_CS              4
        #define PIN_PCB_BUSY            7
        #define PIN_PCB_RST             6
        #define PIN_PCB_VEXT            45              // Power to all peripherals on PCB, active LOW
        
        // PCB Wiring - LoRa, only used for forceSleep()
        #define PIN_PCB_RADIO_DIO_1     14
        #define PIN_PCB_RADIO_NSS       8
        #define PIN_PCB_RADIO_RESET     12
        #define PIN_PCB_RADIO_BUSY      13
        #define PIN_PCB_LORA_CS         8
        #define PIN_PCB_LORA_CLK        9
        #define PIN_PCB_LORA_MISO       11
        #define PIN_PCB_LORA_MOSI       10

        // Platform-specific methods
        namespace Platform {
            extern SPIClass* getSPI();                                                                      // Pass the correct SPI bus to display class
            extern void beginSPI(SPIClass *spi, uint8_t pin_mosi, uint8_t pin_miso, uint8_t pin_clk);       // Call the appropriate SPI begin method
            extern void VExtOn();                                                                           // Enable power to peripherals
            extern void VExtOff();                                                                          // Disable power to perpiherals
            extern void toggleResetPin();                                                                   // Trigger the displays' reset pin
            extern void forceSleep();                                                                       // Configure the board and peripherals for deep sleep (18μA)
        }

    #endif

#endif