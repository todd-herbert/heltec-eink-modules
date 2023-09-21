/*
    File: pin_mux.cpp

        - Configure SAMD21 SERCOMs, to give requested SPI pinout
*/

#ifdef __SAMD21G18A__

#include "pin_mux.h"

// Find and set SDI and CLK pin muxings for SAMD21 SPI. Returns the automatic MISO pin selection
uint8_t PinMux::setSPIPins(uint8_t sdi, uint8_t clk) {
    // Pass down
    return setSPIPins(sdi, clk, -1);
}

// Find and set a pin muxing for SAMD21 SPI. Returns the selected MISO pin, incase it was auto-assigned
uint8_t PinMux::setSPIPins(uint8_t sdi, uint8_t clk, uint8_t miso) {

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

            // Duplicate entry, not considered (re: ICSP pins)
            if (sdi_mux.pad == clk_mux.pad)
                continue;

            // Both pins exist on the same sercom
            // Now, check if the pads will work

            SercomSpiTXPad tx_pad;
            SercomRXPad rx_pad;

            if (sdi_mux.pad == 0 && clk_mux.pad == 1) 
                tx_pad = SPI_PAD_0_SCK_1; 

            else if(sdi_mux.pad == 2 && clk_mux.pad == 3)
                tx_pad = SPI_PAD_2_SCK_3;

            else if(sdi_mux.pad == 3 && clk_mux.pad == 1)
                tx_pad = SPI_PAD_3_SCK_1;

            else if(sdi_mux.pad == 0 && clk_mux.pad == 3)
                tx_pad = SPI_PAD_0_SCK_3;

            else    // No suitable pad setting
                continue;



            // Lets go hunting for a MISO muxing
            for( uint8_t m = 0; m < sizeof(valid_muxs) / sizeof(Mux); m++ ) {
                Mux miso_mux = valid_muxs[m];

                // If use has specified miso, and this doesn't match: not considered
                if (miso != 0xFF && miso_mux.pin != miso)
                    continue;

                // Non-matching sercom, not considered
                if (miso_mux.sercom != clk_mux.sercom)
                    continue;
                
                // Reject if it's a duplicate (A1 - ICSP MOSI)
                if (miso_mux.pad == sdi_mux.pad || miso_mux.pad == clk_mux.pad)
                    continue;

                // Set the RX pad, for the SPI constructor
                rx_pad = (SercomRXPad)miso_mux.pad;


                // We have all three pins, time to reconfigure SPI
                SPI = SPIClassSAMD(clk_mux.sercom, miso, clk, sdi, tx_pad, rx_pad);
                pinPeripheral(sdi, sdi_mux.type);
                pinPeripheral(clk, clk_mux.type);

                // Also set MISO, if the user requested a pin for it
                if (miso != 0xFF)
                    pinPeripheral(miso_mux.pin, miso_mux.type);

                return miso_mux.pin;    // Pass miso back to BaseDisplay, incase it was auto-assigned here 

            } // End of loop - find miso

        }   // End of loop- find matching clk

    }   // End of loop - find sdi pin

    // SPI pinout not possible - Blink SOS on LED_BUILTIN
    SOS();
    return -1; // Suppress warning
}


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
