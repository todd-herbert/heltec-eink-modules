# Transitioning to V2
Version 2 has been released. Since version 1.x there have been several breaking changes.

* Classes have been renamed
* quality.FAST is now set by calling ```setFastmode( CLASS_INSTANCE.fastmode.ON );```
* windows are set by calling ```display.setWindow( LEFT, TOP, WIDTH, HEIGHT )```
* No more sleep / wake callbacks, do it yourself, ya lazy
* No more non-blocking updates; they conflicted with partial refresh code. May be reintroduced as an update_async() method at a later date.
* A lot of general bug fixes.<br />
If you were aware of a bug, and went out of your way to work around it, that hack might have broken. And by broken, I mean fixed. Or rebroken. De-fixed. Something like that.

And that's just the issues I could think of.. <br />
Sorry, and good luck.