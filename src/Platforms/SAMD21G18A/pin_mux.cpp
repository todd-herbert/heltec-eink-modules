/*
    File: pin_mux.cpp

        - Configure SAMD21 SERCOMs, to give requested SPI pinout
*/

#ifdef __SAMD21G18A__

#include "pin_mux.h"

// Find and set SDI and CLK pin muxing for SAMD21 SPI. Returns the automatic MISO pin selection (sercom assigned, but pinmode not set)
uint8_t PinMux::setSPIPins(uint8_t sdi, uint8_t clk) {
    // Pass down
    return setSPIPins(sdi, clk, -1);
}

// Find and set pin muxing for SAMD21 SPI. Returns the selected MISO pin, incase it was auto-assigned. (assigned, but not enabled)
uint8_t PinMux::setSPIPins(uint8_t sdi, uint8_t clk, uint8_t miso) {

    // For every option in list of available pin configs
    for( uint8_t s = 0; s < sizeof(available_options) / sizeof(MuxOption); s++ ) {

        // Inspect as potential SDI config
        MuxOption sdi_conf = available_options[s];
    
        // Wrong SDI pin, not considered
        if (sdi_conf.pin != sdi)
            continue;

        // Re-check aganst the options list: find a suitable CLK option
        for( uint8_t c = 0; c < sizeof(available_options) / sizeof(MuxOption); c++ ) {

            // Inspect as potential CLK config
            MuxOption clk_conf = available_options[c];

            // CLK pin number wrong, not considered
            if (clk_conf.pin != clk)
                continue;

            // CLK option uses different sercom to SDI option, not considered
            if (sdi_conf.sercom != clk_conf.sercom)
                continue;

            // Duplicate entry, not considered (re: ICSP pins)
            if (sdi_conf.pad == clk_conf.pad)
                continue;

            // Both pin options use the same sercom
            // Now, check if the pads will work

            SercomSpiTXPad tx_pad;
            SercomRXPad rx_pad;

            if (sdi_conf.pad == 0 && clk_conf.pad == 1) 
                tx_pad = SPI_PAD_0_SCK_1; 

            else if(sdi_conf.pad == 2 && clk_conf.pad == 3)
                tx_pad = SPI_PAD_2_SCK_3;

            else if(sdi_conf.pad == 3 && clk_conf.pad == 1)
                tx_pad = SPI_PAD_3_SCK_1;

            else if(sdi_conf.pad == 0 && clk_conf.pad == 3)
                tx_pad = SPI_PAD_0_SCK_3;

            else    // No suitable pad setting (for user resquested pins)
                continue;

            // Check list of options for a valid MISO config
            for( uint8_t m = 0; m < sizeof(available_options) / sizeof(MuxOption); m++ ) {

                // Inspect as potential MISO config
                MuxOption miso_conf = available_options[m];

                // If user specified a MISO pin, and this doesn't match: not considered
                if (miso != 0xFF && miso_conf.pin != miso)
                    continue;

                // Different SERCOM to SDI and CLK, not considered
                if (miso_conf.sercom != clk_conf.sercom)
                    continue;
                
                // Reject if it's a duplicate (A1 - ICSP MOSI)
                if (miso_conf.pad == sdi_conf.pad || miso_conf.pad == clk_conf.pad)
                    continue;

                // Set the RX pad, for the SPI constructor
                rx_pad = (SercomRXPad)miso_conf.pad;


                // We have all three pins, time to reconfigure SPI
                SPI = SPIClassSAMD(clk_conf.sercom, miso, clk, sdi, tx_pad, rx_pad);
                pinPeripheral(sdi, sdi_conf.type);
                pinPeripheral(clk, clk_conf.type);

                // Also set MISO, if the user requested a pin for it
                if (miso != 0xFF) {
                    pinPeripheral(MISO, PIO_INPUT); // Unset original MISO pin - seems necessary
                    pinPeripheral(miso_conf.pin, miso_conf.type);
                }

                return miso_conf.pin;    // Pass miso back to BaseDisplay, incase it was auto-assigned here (unnecessary?)

            }   // End of loop - find MISO

        }   // End of loop - find CLK

    }   // End of loop - find SDI

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
