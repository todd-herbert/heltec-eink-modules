# Breaking changes
### Upgrading from v2.5.1 to v3.0.0-alpha
This is an informal list of changes, maintained during development, to give a "heads up" on what to expect.

The list will grow and change.

### Just tell me already!

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