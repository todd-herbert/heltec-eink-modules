// Functions controlling power and reset for  "Wireless Paper" All-in-one board

#include "Platforms/platforms.h"

#ifdef WIRELESS_PAPER

namespace Platform {

    // Enable power to Wireless Paper's interfaces (Display + LoRa)
    void VExtOn() {

        if (digitalRead(PIN_PCB_VEXT) == HIGH) {    // Read, to avoid waiting unnecessariy for power to stabilize
        
            pinMode(PIN_PCB_VEXT, OUTPUT);          // OUTPUT, incase this is the first call
            digitalWrite(PIN_PCB_VEXT, LOW);        // Power on (Active LOW)

            uint32_t start = millis();              // Non-blocking wait
            while (millis() - start < 50)           // 50 ms
                yield();
        }
    }

    // Remove power from Wireless Paper's interfaces (Display + LoRa)
    void VExtOff() {
        pinMode(PIN_PCB_VEXT, OUTPUT);
        digitalWrite(PIN_PCB_VEXT, HIGH);   // ACTIVE LOW
    }

    void toggleResetPin() {
        pinMode(PIN_DISPLAY_RST, OUTPUT);
        digitalWrite(PIN_DISPLAY_RST, LOW);
        
        uint32_t start = millis();              // Non-blocking wait for reset
        while (millis() - start < 10)           // 10 ms
            yield();

        digitalWrite(PIN_DISPLAY_RST, HIGH);
    }

    void forceSleep() {

        // Set SX1262 to SLEEP mode - Software SPI so we can "trample" stuff
        // -----------------------------------------------------------------

        // Default pin states
        digitalWrite(PIN_LORA_NSS, HIGH);
        digitalWrite(PIN_LORA_SCK, LOW);        // Mode 0 - Idle Low
        digitalWrite(PIN_LORA_MOSI, LOW);

        // Set pin modes
        pinMode(PIN_LORA_NSS, OUTPUT);
        pinMode(PIN_LORA_SCK, OUTPUT);
        pinMode(PIN_LORA_MOSI, OUTPUT);

        // CS LOW
        digitalWrite(PIN_LORA_NSS, LOW); 

        // TX data and params
        shiftOut(PIN_LORA_MOSI, PIN_LORA_SCK, MSBFIRST, 0x84);  // Command: Enter SLEEP mode
        shiftOut(PIN_LORA_MOSI, PIN_LORA_SCK, MSBFIRST, 0x04);  // Parameter: sleepConfig - maintain chip config while sleeping

        // CS HIGH - all done
        digitalWrite(PIN_LORA_NSS, HIGH);


        // Set the GPIOs for sleep
        // ------------------------

        VExtOff();

        // LoRa pins to high-impedence
        pinMode(PIN_LORA_NRST, ANALOG);
        pinMode(PIN_LORA_BUSY, ANALOG);
        pinMode(PIN_LORA_SCK, ANALOG);
        pinMode(PIN_LORA_MISO, ANALOG);
        pinMode(PIN_LORA_MOSI, ANALOG);

        // LoRa CS (RADIO_NSS) needs to stay HIGH, even during deep sleep
        pinMode(PIN_LORA_NSS, OUTPUT);
        digitalWrite(PIN_LORA_NSS, HIGH);
        gpio_hold_en((gpio_num_t) PIN_LORA_NSS);    // "stay where you're told"


        // Sleep the ESP32
        // ---------------

        esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_OFF);
        esp_deep_sleep_start();
    }

}   // End of namespace

#endif