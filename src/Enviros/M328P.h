// Platform specific options for ATmega328P

#ifndef __M328P_H__
#define __M328P_H__

    // If building for ATmega328P (UNO, or compatible)
    #ifdef __AVR_ATmega328P__

        // SPI
        #define SPI_BEGIN() ( SPI.begin() )

        // Paging
        #define DEFAULT_PAGE_HEIGHT     20
        #define MAX_PAGE_HEIGHT         50      // Size, in bytes: MAX_PAGE_HEIGHT * (width / 8)

        #define RELEASE_PAGE_MEM        true    // Re-allocate before each paging operation     

    #endif

#endif