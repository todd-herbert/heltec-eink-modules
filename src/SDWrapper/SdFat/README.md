This is a bundled version of the SdFat library, v2.2.2

The `SdSpiArduinoDriver::begin()` and `SdSpiArduinoDriver::end()` methods have been modified, due to an issue with SPI pins assignment, on SAMD21G18A devices.

`.cpp` files are excluded by the preprocessor, for ESP8266, to prevent a library conflict.

https://github.com/greiman/SdFat