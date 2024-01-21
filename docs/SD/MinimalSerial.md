# Heltec E-ink Modules - Minimal Serial

There is a known issue, where HardwareSerial (`Serial.print()` etc) cannot be used after  `SAVE_CANVAS()` is enabled for Arduino UNO (in optimization.h).

As a workaround, the `MinimalSerial` class is available (part of the bundled SdFat library)

```cpp
#include <heltec-eink-modules.h>

// Create the replacement serial instance
MinimalSerial s;

void setup() {

    // It "should" work pretty much the same as HardwareSerial (UART on Pins 0 and 1)

    s.begin(9600);
    s.println("Hello, World!");

}

void loop() {

}

```