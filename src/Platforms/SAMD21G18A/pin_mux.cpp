/*
    File: pin_mux.cpp

        - Configure SAMD21 SERCOMs, to give requested SPI pinout
*/

#ifdef __SAMD21G18A__

#include "pin_mux.h"

// Find and set a pin muxing for SAMD21 SPI
void PinMux::setSPIPins(uint8_t sdi, uint8_t clk) {

    // For every valid mux
    for( uint8_t s = 0; s < sizeof(valid_muxs) / sizeof(Mux); s++ ) {

        // Try all mux options
        Mux sdi_mux = valid_muxs[s];
    
        // Wrong SDI pin, not considered
        if (sdi_mux.pin != sdi)
            continue;

        // Re-check aganst the mux, array, looking for clk
        for( uint8_t c = 0; c < sizeof(valid_muxs) / sizeof(Mux); c++ ) {
            Mux clk_mux = valid_muxs[c];

            // If wrong clk pin, not considered
            if (clk_mux.pin != clk)
                continue;

            // Non-matching sercom, not considered
            if (sdi_mux.sercom != clk_mux.sercom)
                continue;

            // Both pins exist on the same sercom
            // Now, check if the pads will work

            SercomSpiTXPad tx_pad;
            SercomRXPad rx_pad;

            if (sdi_mux.pad == 0 && clk_mux.pad == 1) 
                { tx_pad = SPI_PAD_0_SCK_1; rx_pad = SERCOM_RX_PAD_2; }

            else if(sdi_mux.pad == 2 && clk_mux.pad == 3)
                { tx_pad = SPI_PAD_2_SCK_3; rx_pad = SERCOM_RX_PAD_1; }

            else if(sdi_mux.pad == 3 && clk_mux.pad == 1)
                { tx_pad = SPI_PAD_3_SCK_1; rx_pad = SERCOM_RX_PAD_2; }

            else if(sdi_mux.pad == 0 && clk_mux.pad == 3)
                { tx_pad = SPI_PAD_0_SCK_3; rx_pad = SERCOM_RX_PAD_2; }

            else    // No suitable pad setting
                continue;

            // Supposedly, we have a viable config now

            // Reconfigure SPI
            SPI = SPIClassSAMD(clk_mux.sercom, -1, clk, sdi, tx_pad, rx_pad);
            pinPeripheral(sdi, sdi_mux.type);
            pinPeripheral(clk, clk_mux.type);
            return;

        }   // End of loop- find matching clk

    }   // End of loop - find sdi pin

    // SPI pinout not possible - Blink SOS on LED_BUILTIN
    SOS();
};


// Blink out SOS
void PinMux::SOS() {
    pinMode(LED_BUILTIN, OUTPUT);

    while (true) {
        for(uint8_t s = 0; s < 3; s++) {
            digitalWrite(LED_BUILTIN, HIGH);
            delay(100);
            digitalWrite(LED_BUILTIN, LOW);
            delay(300);
        }

        delay(100);
        

        for(uint8_t s = 0; s < 3; s++) {
            digitalWrite(LED_BUILTIN, HIGH);
            delay(500);
            digitalWrite(LED_BUILTIN, LOW);
            delay(400);
        }

        delay(100);

        for(uint8_t s = 0; s < 3; s++) {
            digitalWrite(LED_BUILTIN, HIGH);
            delay(100);
            digitalWrite(LED_BUILTIN, LOW);
            delay(300);
        }

        delay(2000);
    }
}

#endif  // Platform is SAMD21G18A
