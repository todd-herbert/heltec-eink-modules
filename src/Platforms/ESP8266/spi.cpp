#ifdef ESP8266

#include "ESP8266.h"

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