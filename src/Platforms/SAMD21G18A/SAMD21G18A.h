// Specific options for SAMD21G18A

#ifndef __PLATFORM_FALLBACK_H__
#define __PLATFORM_FALLBACK_H__

    // Check if not otherwise handled
    #ifdef __SAMD21G18A__

        #include "pin_mux.h"

        // Don't use fallback settigs
        // Don't use fallback settigs
        #define PLATFORM_SUPPORTED      true

        // SPI
        
        #define SPI_BEGIN()             ( SPI.begin() )
        #define CAN_SPECIFY_SPI_PINS    true
        #define DEFAULT_SDI             MOSI
        #define DEFAULT_CLK             SCK
        #define LATE_INIT               true

        // Paging
        #define DEFAULT_PAGE_HEIGHT     panel_height
        #define MAX_PAGE_HEIGHT         panel_height    // Size, in bytes: MAX_PAGE_HEIGHT * (width / 8)
        #define PRESERVE_IMAGE          true            // Allow the profile to preserve image

    #endif

#endif