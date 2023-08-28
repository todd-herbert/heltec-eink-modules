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

        // Name
        #define ENVIRONMENT             ESP32

        // SPI
        #define SPI_BEGIN() ( SPI.begin(pin_clk, -1, pin_sdi, -1) )
        #define CAN_SPECIFY_SPI_PINS    true
        #define DEFAULT_SDI             MOSI
        #define DEFAULT_CLK             SCK

        // Paging
        #define DEFAULT_PAGE_HEIGHT     panel_height    // Full screen at once
        #define MAX_PAGE_HEIGHT         296             // (Largest supported panel)

    #endif

#endif