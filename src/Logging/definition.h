/*
    File: definition.h

        Preprocessor selects either:

        - Functions for printing logs to serial

        or

        - Dummy functions, with no string resources
*/

#ifndef __LOGGING_DEFINITION_H__
#define __LOGGING_DEFINITION_H__

#include <Arduino.h>
#include "Platforms/platforms.h"

// The LogMsg enum, and extern declarations
#include "declaration.h"

#ifdef LOGGING

    // Print a timestamp for log lines
    void __SERLOG_TIMESTAMP() {
        uint32_t now = millis() - LOGGING_INIT_DELAY;
        uint16_t ms = now % 1000;
        // Print whole seconds
        LOGGING_SERIAL.print(now / 1000); 
        LOGGING_SERIAL.print('.');

        // Print ms fragment
        if (ms < 100) 
            LOGGING_SERIAL.print(0);
        if (ms < 10)
            LOGGING_SERIAL.print(0);
        LOGGING_SERIAL.print(ms);

        LOGGING_SERIAL.print("s | ");
    }

    bool __SERLOG_BEGUN = false;

    // Init serial for logging
    void __SERLOG_BEGIN() {
        delay(LOGGING_INIT_DELAY);
        LOGGING_SERIAL.begin(9600);
        LOGGING_SERIAL.println();
        LOGGING_SERIAL.println();
        __SERLOG_TIMESTAMP();
        LOGGING_SERIAL.println("serial logging begins");
        __SERLOG_BEGUN = true;
    }

    // Print an info message
    void __SERLOG_INFO(const __FlashStringHelper* msg) {
        if(!__SERLOG_BEGUN) __SERLOG_BEGIN();

        __SERLOG_TIMESTAMP();
        LOGGING_SERIAL.println(msg);
    }

    // Print an info message, with additional data
    template <typename T>
    void __SERLOG_INFO(const __FlashStringHelper* msg, const __FlashStringHelper* var_name, T var_val) {
        if(!__SERLOG_BEGUN) __SERLOG_BEGIN();

        __SERLOG_TIMESTAMP();
        LOGGING_SERIAL.print(msg);
        LOGGING_SERIAL.print(" | ");
        LOGGING_SERIAL.print(var_name);
        LOGGING_SERIAL.print(": ");
        LOGGING_SERIAL.println(var_val);
    }

    // Print an error, then hang
    void __SERLOG_ERROR(const __FlashStringHelper* msg) {
        if(!__SERLOG_BEGUN) __SERLOG_BEGIN();

        __SERLOG_TIMESTAMP();
        LOGGING_SERIAL.print("ERROR | ");
        LOGGING_SERIAL.println(msg);
        
        LOGGING_SERIAL.println();
        LOGGING_SERIAL.println("Execution stopped.");

        while (true)
            yield();   
    }

    // Print an error, with additional data, then hang
    template <typename T>
    void __SERLOG_ERROR(const __FlashStringHelper* msg, const __FlashStringHelper* var_name, T var_val) {
        if(!__SERLOG_BEGUN) __SERLOG_BEGIN();

        __SERLOG_TIMESTAMP();
        LOGGING_SERIAL.print("ERROR | ");
        LOGGING_SERIAL.print(msg);
        LOGGING_SERIAL.print(" | ");
        LOGGING_SERIAL.print(var_name);
        LOGGING_SERIAL.print(": ");
        LOGGING_SERIAL.println(var_val);
        
        LOGGING_SERIAL.println();
        LOGGING_SERIAL.println("Execution stopped.");

        while (true)
            yield();   

    }

    // --------------------------------------------------------------------------------

    // Temporary macros to save typing
    #define _I(lm, txt)             case lm: \
                                        __SERLOG_INFO(F(txt)); \
                                        break;
    
    #define _ID(lm, txt, var_name)  case lm: \
                                        __SERLOG_INFO<T>(F(txt), F(var_name), val); \
                                        break;  
    #define _E(lm, txt)             case lm: \
                                        __SERLOG_ERROR(F(txt)); \
                                        break;
    
    #define _ED(lm, txt, var_name)  case lm: \
                                        __SERLOG_ERROR<T>(F(txt), F(var_name), val); \
                                        break;

    // --------------------------------------------------------------------------------

    // Handle messages

    template<typename T>
    void __SERLOG_PROCESS(LogMsg m, T val) {
        switch (m) {
                _I(LATEINIT_START, "start of lateInit() (hardware init for fussy platforms)")
                _I(LATEINIT_SAMD21_PINMUX, "SAMD21 - SPI pinout modified - MISO disabled")
                _ID(PRINT_MOSI, "pin", "MOSI")
                _ID(PRINT_SCK, "pin", "SCK")
                _ID(WRITE_PAGE, "writing display", "rows done")
                _I(LATEINIT_COMPLETE, "end of lateInit()")
                _I(INIT_COMPLETE, "end of init()")
                _E(PAGING_REQUIRED, "paging is enabled - Use a DRAW() loop")
                _I(CALCULATING_START, "start of DRAW() loop")
                _I(SPI_HAS_BEGUN, "SPI begin")
                _I(CLEAR_MEM, "display memory cleared")
                _I(ACTIVATE_START, "begin display refresh")
                _I(ACTIVATE_END, "display refresh complete")
        }
    }

    #undef _I
    #undef _ID
    #undef _E
    #undef _ED

    // These functions defined external elsewhere
    // It was easier to create these than to figure out extern templates..

    // No variables
    void __SERLOG_PROCESS(LogMsg lm) {
        __SERLOG_PROCESS<uint8_t>(lm, 0);
    }

    // Int variables
    void __SERLOG_PROCESS(LogMsg lm, int16_t val) {
        __SERLOG_PROCESS<int16_t>(lm, val);
    }

#else

    // If !LOGGING, present only these dummy routines to the compiler

    void __SERLOG_PROCESS(LogMsg lm) {}
    void __SERLOG_PROCESS(LogMsg lm, int16_t val) {}

#endif  // ifdef LOGGING
#endif  // Include guard