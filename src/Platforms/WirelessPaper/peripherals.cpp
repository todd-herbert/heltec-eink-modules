// Functions for controlling the "Wireless Paper" All-in-one board.

#include "Platforms/platforms.h"

#ifdef WIRELESS_PAPER

namespace Platform {

    // Enable power to Wireless Paper's peripherals, including display
    void VExtOn() {
        if (digitalRead(PIN_PCB_VEXT) == HIGH) {    // Read, to avoid waiting unnecessariy for power to stabilize
        
            pinMode(PIN_PCB_VEXT, OUTPUT);
            digitalWrite(PIN_PCB_VEXT, LOW);        // Power on

            uint32_t start = millis();              // Non-blocking wait
            while (millis() - start < 50)
                yield();
        }
    }

    // Remove power from Wireless Paper's peripherals, include display
    void VExtOff() {
        pinMode(PIN_PCB_VEXT, OUTPUT);
        digitalWrite(PIN_PCB_VEXT, HIGH);
    }

    void toggleResetPin() {
        Serial.println("reset PIN going low");
        pinMode(PIN_PCB_RST, OUTPUT);
        digitalWrite(PIN_PCB_RST, LOW);
        
        uint32_t start = millis();              // Non-blocking wait for reset
        while (millis() - start < 10)
            yield();

        digitalWrite(PIN_PCB_RST, HIGH);
        Serial.println("reset PIN going high");
    }
}

#endif