/*
    File: pin_mux.h

        - Configure SAMD21 SERCOMs, to give requested SPI pinout
*/

#ifndef __SAMD21_PIN_MUX_H__
#define __SAMD21_PIN_MUX_H__

#include <Arduino.h>
#include <SPI.h>
#include <wiring_private.h>     // Lower-level pin manipulation

#ifdef __SAMD21G18A__

namespace Platform {
    extern uint8_t setSPIPins(uint8_t sdi, uint8_t clk);
    extern uint8_t setSPIPins(uint8_t sdi, uint8_t clk, uint8_t miso);     // If useSD() has been called
}

#endif  // End - Platform SAMD21G18A
#endif  // Include guard