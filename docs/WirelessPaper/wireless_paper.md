# Heltec E-Ink Modules - Wireless Paper

![](promo.jpg)

In addition to the line of SPI E-Ink displays, Heltec sell an all-in-one board, "Wireless Paper".

#### Features:
  * ESP32 Microcontroller
  * 2.13" Black and White E-Ink display
  * WiFi, Bluetooth & LoRa connectivity

Only the board's E-Ink display falls within the scope of this library.

- [Getting Started](#getting-started)
  - [Arduino IDE](#arduino-ide)
  - [PlatformIO](#platformio)
- [Using the library](#using-the-library)
- [Things to know](#things-to-know)
  - [`VExtOn()`](#vexton)
  - [Deep Sleep](#deep-sleep)


## Getting Started

### Arduino IDE

1. Open preferences 

    ![](ArduinoIDE/prefs.jpg)

2. Open "Additional board manager URLs"

    ![](ArduinoIDE/urls1.jpg)

3. Add the URL: `https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series/releases/latest/download/package_heltec_esp32_index.json`

    ![](ArduinoIDE/urls2.jpg)

4. Open the Board Manager, search for Heltec, and install the latest version of `Heltec ESP32 Series Dev-boards`. <br />
This may take some time.

    ![](ArduinoIDE/board_manager.jpg)

5. With your "Wireless Paper" connected, open the board selection drop-dowm, search for "paper", then select Wireless Paper, and your board's serial port.

    ![](ArduinoIDE/select_board.jpg)

### PlatformIO

Add the following entry to your `platformio.ini` file

```
[env:wireless_paper]
platform = espressif32
board = heltec_wifi_lora_32_V3
framework = arduino
lib_deps = https://github.com/todd-herbert/heltec-eink-modules
```

## Using the library

Check out the examples, such as *File > Examples > heltec-eink-modules > WirelessPaper > basic* <br />
Make sure to select your [display model](/docs/README.md#wireless-paper) first, at the top of the sketch.

The upload process will be slow when compiling for the first time. Saving your sketch allows the IDE to re-use much of the old code, without recompiling.

**Here's a rough idea:**
```cpp
#include <heltec-eink-modules.h>

// Pick your display model:

// DEPG0213BNS800 display;     // (Red Tab)
// LCMEN2R13EFC1 display;      // (Green Tab, V1.1)

void setup() {
    display.landscape();

    display.print("Hello, World!");
    display.update();

    delay(2000);
    
    display.clearMemory();
    display.printCenter("Centered Text");
    display.update();

    delay(2000);

    display.clear();
}

void loop() {

}
```

## Things to know

### `VExtOn()`
The display, and wireless hardware, have an ACTIVE LOW power switch on GPIO45. 
The *heltec-eink-modules* libary will switch this on when first required.

If needed, you can manually power on the hardware with `Platform::VExtOn()`.

### Deep Sleep
In order to achieve the promised 18uA deep sleep current, a number of config steps must take place.

Calling `Platform::prepareToSleep()` will hopefully take care of this for you.

```cpp
// Configure hardware for low-power
Platform::prepareToSleep();

// How long until restart
esp_sleep_enable_timer_wakeup( SLEEP_TIME_IN_MICROSECONDS );

// Sleep now
esp_deep_sleep_start();
```

The 18uA current is only achievable when powering with the battery connector. When USB is connected, an orange LED remains on.
