// Specific options for ATmega2560

#ifndef __M2560_H__
#define __M2560_H__

    // If building for ATmega2560
    #ifdef __AVR_ATmega2560__

        // Don't use fallback settings
        #define PLATFORM_SUPPORTED      true

        // SPI
        #define SPI_BEGIN()             ( SPI.begin() )
        #define CAN_SPECIFY_SPI_PINS    false
        #define DEFAULT_SDI             MOSI
        #define DEFAULT_CLK             SCK
        #define LATE_INIT               false

        // Paging
        #define DEFAULT_PAGE_HEIGHT     panel_height
        #define MAX_PAGE_HEIGHT         panel_height    // Size, in bytes: MAX_PAGE_HEIGHT * (width / 8)
        #define PRESERVE_IMAGE          true            // No clearing of page file between updates

    #endif

#endif