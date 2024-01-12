# Heltec E-ink Modules
## Wiring: ESP32

**✅ ESP32 uses 3.3V logic. It can connect directly to the display.**

Display | ESP32
--------|--------
 VCC    | 3.3V
 GND    | GND
 D/C    | GPIO 2
 SDI    | GPIO 23 (VSPI MOSI)
 CS     | GPIO 4
 CLK    | GPIO 18 (VSPI SCK)
 BUSY   | GPIO 5

All pins can be changed, using an extended constructor:
```cpp
DISPLAY_CLASS(DC_PIN, CS_PIN, BUSY_PIN, SDI_PIN, CLK_PIN); 
```

### (Optional) Suggested additional wiring, for power saving

```cpp
void setup() {
    // GPIO 15, PNP transistor
    display.useCustomPowerSwitch(15, PNP);

    //Later, when required:
    display.customPowerOff();
    display.customPowerOn();
}
```

![schematic of display connected to ESP32, using PNP transistor as a switch](ESP32_power_switching.png)

### (Optional) Additional wiring: MicroSD card module
**✅ ESP32 uses 3.3V logic. It can connect directly to microSD module.**
```cpp
void setup() {
    // Set MicroSD CS pin
    display.useSD(22);
}
```

 Micro SD Module    | ESP32
 -------------------|-------
 VCC                | 3.3V
 CS                 | GPIO 22
 MOSI               | GPIO 23 (VSPI MOSI)
 SCK                | GPIO 18 (VSPI SCK)
 MISO               | GPIO 19 (VSPI MISO)
 GND                | GND

 Some pins are shared with the display.

 *MOSI* and *SCK* pins can be changed in the display constructor (see above).

*CS* pin (card) must be set with `useSD(cs)`. Any suitable GPIO pin may be used.
Optionally, MISO may also be set, with `useSD(cs, miso)`