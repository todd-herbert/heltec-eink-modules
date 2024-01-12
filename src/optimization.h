/* 
    File: optimization.h

        This is a user-editable config file.
        This file contains macros which can be used to disable features of the library at compile-time.
        The aim is to reduce the size of the sketch in flash memory, for Uno in particular.

        PlatformIO users: these macros can instead be set as build_flags in platformio.ini

        TODO: document use of this file in API.md and README.md
        TODO: mark this as a breaking change
*/

// Enable SAVE_CANVAS() on Uno / Nano
// ------------------------------------------------------
//  Leaving this disabled can save ~20% flash, if *no* SD methods are used.
//  Disabled by default: SAVE_CANVAS() is a niche method

    // #define UNO_ENABLE_SDWRITE