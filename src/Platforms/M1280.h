// Specific options for ATmega2560

#ifndef __M1280_H__
#define __M1280_H__

    // If building for ATmega1280
    #ifdef __AVR_ATmega1280__

        #warning - ATmega1280 support is untested.

        // Short Name
        #define PLATFORM_NAME           ATMEGA1280

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