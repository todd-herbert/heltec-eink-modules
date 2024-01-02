#ifdef __AVR_ATmega1280__

#include "M1280.h"

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