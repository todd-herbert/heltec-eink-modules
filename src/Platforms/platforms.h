// All platforms, as one header

#ifndef __PLATFORMS_H__
#define __PLATFORMS_H__

#include <Arduino.h>

// Supported
#include "Platforms/M328P/M328P.h"
#include "Platforms/ESP32/ESP32.h"
#include "Platforms/ESP8266/ESP8266.h"
#include "Platforms/M2560/M2560.h"
#include "Platforms/SAMD21G18A/SAMD21G18A.h"

// Untested, but *should* work
// #include "Platforms/M1280/M1280.h"

// Fallback
#include "Platforms/fallback/fallback.h"

#endif