#ifdef ESP32

#include "ESP32.h"

namespace Platform {

    // Create SPI
    SPIClass* getSPI() {
        return &SPI;
    }

    // Call SPI.begin
    void beginSPI(SPIClass *spi, uint8_t pin_mosi, uint8_t pin_miso, uint8_t pin_clk) {
        spi->begin(pin_clk, pin_miso, pin_mosi, -1);     // CS handled manually
    }

}

#endif