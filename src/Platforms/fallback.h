// Fallback options

#ifndef __PLATFORM_FALLBACK_H__
#define __PLATFORM_FALLBACK_H__

    // Check if not otherwise handled
    #ifndef PLATFORM_SUPPORTED

        #define PLATFORM_SUPPORTED      false

        // SPI
        #define SPI_BEGIN()             ( SPI.begin() )
        #define CAN_SPECIFY_SPI_PINS    false
        #define DEFAULT_SDI             -1
        #define DEFAULT_CLK             -1
        #define LATE_INIT                true

        // Paging
        #define DEFAULT_PAGE_HEIGHT     5
        #define MAX_PAGE_HEIGHT         panel_height    // Size, in bytes: MAX_PAGE_HEIGHT * (width / 8)
        #define PRESERVE_IMAGE          true            // Potentially, allow the profile to preserve image
    #endif

#endif