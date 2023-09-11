// Specific options for ATmega2560

#ifndef __M2560_H__
#define __M2560_H__

    // If building for ATmega2560
    #ifdef __AVR_ATmega2560__

        // Short Name
        #define PLATFORM_NAME           ATMEGA2560

        // SPI
        #define SPI_BEGIN()             ( SPI.begin() )
        #define CAN_SPECIFY_SPI_PINS    false
        #define DEFAULT_SDI             MOSI
        #define DEFAULT_CLK             SCK

        // Paging
        #define DEFAULT_PAGE_HEIGHT     panel_height
        #define MAX_PAGE_HEIGHT         panel_height    // Size, in bytes: MAX_PAGE_HEIGHT * (width / 8)
        #define PRESERVE_IMAGE          true            // No clearing of page file between updates

    #endif

#endif