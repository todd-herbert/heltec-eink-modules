# Breaking changes
### Upgrading from v2.5.1 to v3.0.0


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