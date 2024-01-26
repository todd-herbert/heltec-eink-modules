# Breaking changes

This file *attempts* to list any breaking changes to look out for.
It is certainly possible that I've missed something, sorry.
Also just, sorry in general.

### v4.0.0
* ATmega328P: SD Write disabled by default
    * Huge flash saving
    * Can be re-enabled in optimization.h, or with a build flag
  
*  "External Power" methods renamed to "Custom Power" - emphasize need for user to add hardware
    * `usePowerSwitching()` -> `useCustomPowerSwitch()`
    * `externalPowerOff()` -> `customPowerOff()`
    * `externalPowerOn()` -> `customPowerOn()`

*  "Write Canvas" renamed to "Save to SD"
    * `WRITE_CANVAS() {}` -> `SAVE_TO_SD() {}`
    * `writeCanvas()` -> `saveToSD()`

* `startOver()` renamed to `clearMemory()`

* `setDefaultColor()` renamed to `setBackgroundColor()`

* SD methods renamed
    * `draw24bitBitmapFile()` -> `draw24bitBMP()`
    * `drawMonoBitmapFile()` -> `drawMonoBMP()`
    * `SDCanvasValid()` -> `fullscreenBMPValid()`
    * `loadCanvas()` -> `loadFullscreenBMP()`
    * `SDCanvasExists()` -> `SDFileExists()`
    * Note: some methods which previously had a single "integer id" parameter, now require a prefix and an integer id


### v3.2.0
* `overwrite()` deprecated: term "overwrite" is misleading
    * Renamed to `update()`
    * `overwrite()` command remains as a synonym, for now
  
### v3.0.0

 * `update()` is gone
    * update happens automatically after paging
  
 * Enums have moved
    * `instance.colors.BLACK`-> `BLACK`
    * `instance.orientation.PIN_ABOVE` -> `PINS_ABOVE`
    * Etc.
  
* `setFastmode()` is gone
    * Replaced with:
        <nobr>
        * `setFastmode(instance.fastmode.OFF)` - > `fastmodeOff()`
        * `setFastmode(instance.fastmode.FINALIZING)` - > `fastmodeON()`
        * `setFastmode(instance.fastmode.ON)` - > `fastmodeTurbo()`
        </nobr>

* `deepSleep()` replaced with new  hardware-focussed methods:
    * `usingPowerSwitching(pin, switch_type)`
    * `externalPowerOff()`
    * `externalPowerOn()`