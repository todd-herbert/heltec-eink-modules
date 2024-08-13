# Heltec E-ink Modules
## Suggested Wiring: Vision Master E290
### (Optional) MicroSD card module
**✅ Device uses 3.3V logic. It can connect directly to a microSD module.**

 Micro SD Module    | ESP32
 -------------------|-------
 VCC                | 3.3V
 CS                 | GPIO 40 (suggested)
 MOSI               | GPIO 1
 SCK                | GPIO 2
 MISO               | GPIO 41 (suggested) 
 GND                | GND

MISO and CS pins may be adjusted, but take care. Many of the available GPIOs on the header have default behaviors which interfere with SD card function. Consult [the board schematic](/docs/Datasheets/HTVME290Schematic.pdf).

 ```cpp
void setup() {
    // Set CS and MISO pins for MicroSD
    display.useSD(40, 41);
}
```