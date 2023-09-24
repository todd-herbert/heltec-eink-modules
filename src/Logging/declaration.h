/*
    File: declaration.h

        - Enum of possible log messages

        - Extern declaration of log methods
            - Defined in heltec-eink-modules.h, after use has had a chance to #define LOGGING

        - Macros for accessing log methods
*/

#ifndef __LOGGING_DECLARATION_H__
#define __LOGGING_DECLARATION_H__

// Enum of possible log messages
// Correspond with a switch case in definition.h
// ifndef LOGGING, the switch is removed by the preprocessor, along with all its string literals 

enum LogMsg : uint16_t {
    LATEINIT_START,
    LATEINIT_SAMD21_PINMUX,
    PRINT_MOSI,
    PRINT_SCK,
    WRITE_PAGE,
    CLEAR_MEM,
    PAGING_REQUIRED,
    CALCULATING_START,
    SPI_HAS_BEGUN,
    INIT_COMPLETE,
    LATEINIT_COMPLETE,
    ACTIVATE_START,
    ACTIVATE_END
};


// Functions from definition.h
// ifndef LOGGING, swapped out for dummy routine by the preproccesor

extern void __SERLOG_PROCESS(LogMsg lm);
extern void __SERLOG_PROCESS(LogMsg lm, int16_t val);


// The INFO and ERROR versions are interchangable
// 2 versions maintained only for code readability
// INFO vs ERROR is determined in __SERLOG_PROCESS()

#define _INFO(msg_type) __SERLOG_PROCESS(msg_type)
#define _INFO_DETAILED(msg_type, val) __SERLOG_PROCESS(msg_type, val)
#define _ERROR(msg_type) __SERLOG_PROCESS(msg_type)
#define _ERROR_DETAILED(msg_type, val) __SERLOG_PROCESS(msg_type, val)

#endif
