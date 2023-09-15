// Specific options for ESP32

#ifndef __ESP32_H__
#define __ESP32_H__

    // If building for ESP32
    #ifdef ESP32

        // Redefine macros with AVR version
        #define min(a,b) ((a)<(b)?(a):(b))
        #define max(a,b) ((a)>(b)?(a):(b))
        #define abs(x) ((x)>0?(x):-(x))
        #define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

        // Don't use fallback settings
        #define PLATFORM_SUPPORTED      true

        // SPI
        #define SPI_BEGIN()             ( SPI.begin(pin_clk, -1, pin_sdi, -1) )
        #define CAN_SPECIFY_SPI_PINS    true
        #define DEFAULT_SDI             MOSI
        #define DEFAULT_CLK             SCK
        #define LATE_INIT                false

        // Paging
        #define DEFAULT_PAGE_HEIGHT     panel_height    // Indicate that we want the full display 
        #define MAX_PAGE_HEIGHT         panel_height    // (Largest supported panel)
        #define PRESERVE_IMAGE          true            // No clearing of page file between updates

    #endif

#endif