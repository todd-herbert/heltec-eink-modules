// Specific options for ATmega328P

#ifndef __M328P_H__
#define __M328P_H__

    // If building for ATmega328P (UNO, or compatible)
    #ifdef __AVR_ATmega328P__

        // Short Name
        #define ATMEGA328P

        // SPI
        #define SPI_BEGIN() ( SPI.begin() )
        #define CAN_SPECIFY_SPI_PINS    false
        #define DEFAULT_SDI             -1
        #define DEFAULT_CLK             -1

        // Paging
        #define DEFAULT_PAGE_HEIGHT     20
        #define MAX_PAGE_HEIGHT         50      // Size, in bytes: MAX_PAGE_HEIGHT * (width / 8)

    #endif

#endif