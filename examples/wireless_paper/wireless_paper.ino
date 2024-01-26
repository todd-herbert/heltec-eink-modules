#include <heltec-eink-modules.h>

// Pick your panel  -  https://github.com/todd-herbert/heltec-eink-modules#supported-displays
// ---------------

    // -- "Wireless Paper" boards only --

    // DEPG0213BNS800 display;      // (Red Tab)
    // LCMEN2R13EFC1 display;       // (Green Tab)


// Enable LoRa demo?
// ------------------
// If you want run the LoRa test, include the RadioLib library

    // #include <RadioLib.h>
  

// DEMO: Wireless Paper
// --------------------
// This example is only for Heltec's "Wireless Paper" all-in-one boards.
// A basic demonstration that the onboard hardware does work with this display library.
//
// This example does not demonstrate *good technique* for using the wireless hardware.
// Please refer to each libraries own documentation before using them in your project.


// For Wifi Demo
#include <WiFi.h>

// For BLE Demo
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

// Image resources
#include "image_radiolib_guide1.h"
#include "image_radiolib_guide2.h"
#include "image_radiolib_guide3.h"
#include "image_board_inverse.h"
#include "image_arrow_hooked.h"
#include "image_chess_250x122.h"

// Fonts
#include "Fonts/FreeSansBold12pt7b.h"
#include "Fonts/FreeSans9pt7b.h"

// These are just for the sketch's reference - the library does not require them
const Color DEFAULT_TEXT_COLOR = BLACK;
const GFXfont *DEFAULT_FONT = &FreeSans9pt7b;
const int textbox_padding = 5;                  // How much padding inside textBox() - used by installGuide()
FullBounds f = display.bounds.full;             // Quick access to dimensions of full-screen

// Reusable text-formatting code
#include "graphical_elements.h"

// Demo code (separated for tidiness)
#include "intro_outro.h"
#include "wifi_demo.h"
#include "ble_demo.h"
#include "lora_demo_install.h"
#include "sleep_demo.h"
#include "led_button_demo.h"

void setup() {
    // Set default drawing params
    display.landscape();
    display.setTextWrap(false); 
    display.setTextColor(DEFAULT_TEXT_COLOR);
    display.setFont(DEFAULT_FONT);

    // First set of Demos
    if (esp_sleep_get_wakeup_cause() != ESP_SLEEP_WAKEUP_TIMER) {
        intro();
        wifiDemo();
        BLEDemo();
        
        // Only run LoRa demo if the RadioLib library is installed
        // Otherwise - show an install guide
        #ifdef _RADIOLIB_H
            LoRaDemo();
        #else
            installRadioLibGuide();
        #endif

        sleepDemo();
        // System enters deep sleep now
        // After wake (10 seconds), will run the second set of demos
    }

    // Second set of Demos - after the sleep demo reboots

    LEDDemo();
    buttonDemo();
    outro();
    
    // Example finished, enter a low-power state
    Platform::prepareToSleep();
    esp_deep_sleep_start();
}

void loop() {

}