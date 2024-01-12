// Functions for controlling the "Wireless Paper" All-in-one board

#include "Platforms/platforms.h"

#ifdef WIRELESS_PAPER

namespace Platform {

    // Enable power to Wireless Paper's interfaces (Display + LoRa)
    void interfacesOn() {
        if (digitalRead(PIN_PCB_VEXT) == HIGH) {    // Read, to avoid waiting unnecessariy for power to stabilize
        
            pinMode(PIN_PCB_VEXT, OUTPUT);
            digitalWrite(PIN_PCB_VEXT, LOW);        // Power on (Active LOW)

            uint32_t start = millis();              // Non-blocking wait
            while (millis() - start < 50)           // 50 ms
                yield();
        }
    }

    // Remove power from Wireless Paper's interfaces (Display + LoRa)
    void interfacesOff() {
        pinMode(PIN_PCB_VEXT, OUTPUT);
        digitalWrite(PIN_PCB_VEXT, HIGH);
    }

    void toggleResetPin() {
        pinMode(PIN_PCB_RST, OUTPUT);
        digitalWrite(PIN_PCB_RST, LOW);
        
        uint32_t start = millis();              // Non-blocking wait for reset
        while (millis() - start < 10)           // 10 ms
            yield();

        digitalWrite(PIN_PCB_RST, HIGH);
    }
}

#endif