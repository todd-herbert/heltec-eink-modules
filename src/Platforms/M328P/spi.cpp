#ifdef __AVR_ATmega328P__

#include "M328P.h"

namespace Platform {

    // Create SPI
    SPIClass* getSPI() {
        return &SPI;
    }

    // Call SPI.begin
    void beginSPI(SPIClass *spi, uint8_t pin_mosi, uint8_t pin_miso, uint8_t pin_clk) {
        spi->begin();
    }

}

#endif