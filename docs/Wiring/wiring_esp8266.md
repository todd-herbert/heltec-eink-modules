# Heltec E-ink Modules
## Wiring: ESP8266

**✅ ESP8266 uses 3.3V logic. It can connect directly to the display.**

Note: labels are for the "GPIO" pins, not the "D1, D2, etc." labels printed on the board.


Display | ESP8266
--------|--------
 VCC    | 3.3V
 GND    | GND
 D/C    | GPIO 2 *
 SDI    | GPIO 13
 CS     | GPIO 4 *
 CLK    | GPIO 14
 BUSY   | GPIO 5 *

\* Can be set in constructor. Take care to avoid "iffy" pins on the ESP8266.

### (Optional) Suggested additional wiring, for power saving

```cpp
void setup() {
    // GPIO 0, PNP transistor
    display.useCustomPowerSwitch(0, PNP);

    //Later, when required:
    display.customPowerOff();
    display.customPowerOn();
}
```

![schematic of display connected to ESP8266, using PNP transistor as a switch](ESP8266_power_switching.png)

### (Optional) Additional wiring: MicroSD card module
**✅ ESP8266 uses 3.3V logic. It can connect directly to microSD module.**
```cpp
void setup() {
    // Set MicroSD CS pin
    display.useSD(15);
}
```

 Micro SD Module    | ESP8266
 -------------------|-------
 VCC                | 3.3V
 CS                 | GPIO 15
 MOSI               | GPIO 13
 SCK                | GPIO 14
 MISO               | GPIO 12
 GND                | GND

 Some pins are shared with the display.

*CS* pin (card) must be set with `useSD(cs)`