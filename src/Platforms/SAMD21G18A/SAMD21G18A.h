// Specific options for SAMD21G18A

#ifndef __PLATFORM_SAMD21G18A_H__
#define __PLATFORM_SAMD21G18A_H__

    // If building for SAMD21G18A
    #ifdef __SAMD21G18A__

        #include "pin_mux.h"

        // Don't use fallback settings
        #define PLATFORM_SUPPORTED      true

        // SPI
        
        #define SPI_BEGIN()             ( SPI.begin() )
        #define CAN_MOVE_SPI_PINS       true
        #define DEFAULT_SDI             MOSI
        #define DEFAULT_CLK             SCK

        // Paging
        #define DEFAULT_PAGE_HEIGHT     panel_height
        #define MAX_PAGE_HEIGHT         panel_height    // Size, in bytes: MAX_PAGE_HEIGHT * (width / 8)
        #define PRESERVE_IMAGE          true            // Allow the profile to preserve image

    #endif

#endif