// This file contains the "deep sleep" demo

// Briefly enter a low-power state
void sleepDemo() {
    const char title_sleep[] = "Deep Sleep";
    drawTitle(title_sleep);
    
    display.setCursor(2, 50);
    display.print( \
        "Deep sleep current is\n" \
        "only 18 micro Amps.\n" \
        "\n"\
        "Demo will sleep for 10 seconds." \
    );

    display.update();

    delay(4000);

    display.fastmodeOn();

    display.clearMemory();
    drawTitle(title_sleep);
    display.setCursor(2, 50);
    display.print( \
        "Platform::prepareToSleep();\n" \
        "\n" \
        "Prepares display (and LoRa)\n" \
        "for ESP32 deep sleep." \
    );
    display.update();

    display.fastmodeOff();
    delay(500);    // Let the display settle just a bit

    // heltec-eink-modules: hopefully force the display {and LoRa radio) into a low power state
    // You may need to deal with LoRa yourself via RadioLib
    Platform::prepareToSleep();

    // Set the wakeup timer
    const uint8_t sleep_seconds = 10;
    esp_sleep_enable_timer_wakeup((uint64_t) 1000 * 1000 * sleep_seconds);  // Microseconds

    // Sleep now
    esp_deep_sleep_start();
    
}