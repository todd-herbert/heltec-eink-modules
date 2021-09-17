# Heltec E-Ink Modules

Third-party Arduino Library for **Heltec E-Ink Module** displays.
Supports run-time graphics and text generation using Adafruit-GFX (via [ZinggJM/GFX_Root](https://github.com/ZinggJM/GFX_Root))

This is made possible with *"paging".*

[Huh? Paging?](#what-is-paging) <br />[Supported Displays](#supported-displays) <br />
[Wiring](#wiring) <br />
[Using the library](#using-the-library) <br />
[Configuration](#configuration-options) <br />
[Acknowledgements](#acknowledgements)  <br />




## What is paging?

I don't know. But we're going to use the word anyway.
In this context it means that the display is calculated and transmitted in several small pieces, rather than in one big memory-clogging lump. 

This means more calculations are performed, but less RAM is needed.
The resulting increase in calculation time ends up being insignificant, especially when compared to the slow refresh time of E-INK displays.

Most importantly, it is the what allows the *Arduino Uno* to work with these displays, which would otherwise overload its limited memory.



## Supported Displays

This list is likely to grow with time.

Be aware that Heltec seem to release multiple, incompatible versions of the same display, which can appear superficially similar.

Despite my best efforts I have been unable to source any of the older models, so if you have purchased your display in the last year or so, it would seem likely that you have a V2 display.

| Model                         | Identifying<br />Images                                      | Class Name         | Colors                                                  | Update Modes                             |
| ----------------------------- | :----------------------------------------------------------- | ------------------ | ------------------------------------------------------- | ---------------------------------------- |
| **Heltec 1.54" V2**<br />     | <a href="https://github.com/todd-herbert/heltec-eink-modules/blob/main/docs/SupportList/Heltec-154-V2-Front.jpg?raw=true">Front </a><br /><a href="https://raw.githubusercontent.com/todd-herbert/heltec-eink-modules/main/docs/SupportList/Heltec-154-V2-Rear.jpg">Rear</a> | `Heltec_154_V2`    | `.colors.BLACK`<br />`.colors.WHITE`                    | `.quality.FAST`<br />`.quality.DETAILED` |
| **Heltec 2.13" Red V2**<br /> | <a href="https://github.com/todd-herbert/heltec-eink-modules/blob/main/docs/SupportList/Heltec-213Red-V2-Front.png?raw=true">Front</a><br /><a href="https://raw.githubusercontent.com/todd-herbert/heltec-eink-modules/main/docs/SupportList/Heltec-213Red-V2-Rear.png">Rear</a> | `Heltec_213Red_V2` | `.colors.BLACK`<br />`.colors.WHITE`<br />`.colors.RED` | `.quality.DETAILED`                      |
| **Heltec 2.9" V2**            | <a href="https://github.com/todd-herbert/heltec-eink-modules/blob/main/docs/SupportList/Heltec-290-V2-Front.jpg?raw=true">Front </a><br /><a href="https://raw.githubusercontent.com/todd-herbert/heltec-eink-modules/main/docs/SupportList/Heltec-290-V2-Rear.jpg">Rear</a><br /> | `Heltec_290_V2`    | `.colors.BLACK`<br />`.colors.WHITE`                    | `.quality.DETAILED`                      |



## Wiring

### The display is 3.3V, do not connect it directly to an Arduino.

All warnings aside, connection isn't all that hard. Just be sure to implement some sort of level-shifter. I can can confirm that a simple voltage divider is perfectly adequate, for example: 

![voltage-divider example](https://github.com/todd-herbert/Heltec-213R-V2/blob/main/docs/wiring_example.png?raw=true)

### Display Pins:

* **VCC**: 3.3V Power In
* **GND**: Ground
* **D/C**: Data / Command
  * Tells display whether incoming serial data is a command, or is image data.
    * Can connect to any available digital pin on Arduino
    * 3.3V Logic Input, needs level shifter

* **SDI**: Serial Data Input
  * SPI *MOSI* pin
  * On Arduino UNO, *must connect to pin 11*
  * 3.3V Logic Input, needs level shifter
* **CS**: Chip Select
  * SPI *SS* Pin
  * Can connect to any available digital pin on Arduino, however *pin 10* is traditional. 
  * 3.3V Logic Input, needs level shifter
* **CLK**: Clock
  * SPI *SCK* pin
  * On Arduino UNO, *must connect to pin 13*
  * 3.3V Logic Input, needs level shifter
* **BUSY**
  * Pin is LOW when screen is ready to accept commands
  * Can connect to any available digital pin on Arduino
  * 3.3V Logic Output, **level shifter not required** as 3.3V is a valid level for a HIGH signal on Arduino UNO

Make sure to specify the location of your *D/C, CS* and *BUSY* pins in the constructor.




## Using the library

```c++
#include "heltec-eink-modules.h"

//Use the correct class for your display
Heltec_213Red_V2  display(/* DC PIN */  8, /* CS PIN */  10, /* BUSY PIN */ 7);

void setup() {
	//Get everything ready
	display.begin();
	
	//All drawing commands go intside this WHILE
	while ( display.calculating() ) {
		//================================
		//Graphics commands here
		//For example:
		display.fillCircle(50, 100, 20, display.colors.RED);
		//================================
	}
    //Draw this new image to the display
    display.update();
}

void loop() {}
```

To summarise: 

* Set your hardware pins in the constructor
* Call ```.begin()```
* All drawing commands go inside the ```while ( .calculating () )``` loop. <br />
  This loop repeats the commands for each little slice (page) of the screen, as many times as needed
* Call ```.update()``` to show this new image data on the screen

That's it! Everything else (should) be taken care of automatically.

### Drawing Commands

In the interest of laziness, I'm going to direct you to [the official adafruit-gfx tutorial](https://learn.adafruit.com/adafruit-gfx-graphics-library/graphics-primitives) for information on the drawing commands. 

This library *should* work pretty much the same, with a few small exceptions:

* The display will only support a limited set of colors:
  * ```.colors.BLACK```
  * ```.colors.WHITE```
  * ```.colors.RED```  (3-Color displays only*)

* The adafruit ```.fillScreen()``` method will work just fine, however it is more efficient to use ```.setDefaultColor()```, before the paging while loop.

* A few new handy methods have been added to help with layout:
  * `.bounds.full.`	---   *Dimensions for the whole screen* <br />
       							* `.left()` <br />
							* `.right()` <br />
							* `.top()` <br />
							* `.bottom()` <br />
							* `.centerX()` <br />
							* `.centerY()` <br />
							<br />
  * `bounds.window.`	---   *Dimensions for the current window ([see here](#update-region))* <br />
         						* `.left()` <br />
							* `.right()` <br />
							* `.top()` <br />
							* `.bottom()` <br />
							* `.centerX()` <br />
							* `.centerY()` <br />
							<br />
  * `.setCursorTopLeft()`  --- *sets text-cursor position by upper-left corner value*
  * `.getTextWidth()` 
  * `.getTextHeight()` 

As decided by the Adafruit library, the ancient *"XBitmap"* is the format of choice for pre-rendered graphics. Luckily, GIMP maintains good support for it.

If you need a hint on how to use it, I have thrown together a [tutorial on preparing XBitmap images](https://github.com/todd-herbert/heltec-eink-modules/blob/main/docs/XBitmapTutorial/xbitmap-tutorial.md).



## Configuration Options

* [Pins](#pins)
* [Page Size](#page-size)
* [Power Management](#power-management)
* [Non-Blocking Updates](#blocking-vs-non-blocking)
* [Update Region](#update-region)
* [Update Quality](#update-quality)
* [Code Readability](#code-readability)

### Pins

```c++
//Make sure to use the correct class for your display model
Heltec_154_V2 display(dc, cs, busy);	
```

Pass the Arduino digital pin numbers where the *D/C*, *CS*, and *BUSY* pins from the display are connected.

### Page Size

It is possible to change the *speed vs. memory* tradeoff while calling `.begin()`.

```c++
display.begin(display.pageSize.TINY); 	//100kb of SRAM, 5% of total (Arduino UNO)
display.begin(display.pageSize.SMALL); 	//250kb of SRAM, 12.5% of total (Arduino UNO)
display.begin(display.pageSize.MEDIUM); //500kb of SRAM, 25% of total (Arduino UNO)
display.begin(display.pageSize.LARGE); 	//1000kb of SRAM, 50% of total (Arduino UNO)
```

If `begin()` is called with no parameters, `.pageSize.MEDIUM` is selected.

With `begin()`, it is also possible to set two callback functions, wake and sleep. This brings us to..

### Power Management ###

Many E-Ink displays are able to enter a "deep sleep" power-saving mode. With the *Heltec Modules*, this is technically possible, however the reset pin on the controller IC has not been broken out, meaning that there is no easy way to wake the display without cycling power.

To serve a similar purpose, two callbacks may be specifed through the `.begin()`method

```c++
void wake() {
	//Connect power to display
} 

void sleep() {
	//Remove power from display
}

void setup() {
	display.begin(display.PAGESIZE_MEDIUM, wake, sleep);
}
```

This should make it a simple matter to run your display and/or level shifter through a transistor (or other switching device of your choosing).

The library will run these callbacks as needed to power the display up to allow image updating.

### Blocking vs. Non-Blocking

The E-INK display will begin to update as soon as  `.update()`. By default, this process blocks any further code execution until complete. The design of e-ink panels means that the physical update process can take several seconds.

It is possible to instead update the display in the background by running with the parameter "blocking" set to false: ```.update(false)```. 

It is very important to be aware that if this option is used,  the display will not respond to any further commands until it has completed its background update process. 
This can be checked by calling ```.busy()```, which will return false once the the display is once again free to respond.

Note: Power management callbacks will not work if update is run in the background (i.e. with blocking = false). In this case it is up to the user to manually check `busy()` and power down when appropriate.

### Update Region ###

By default, the entire screen contents will be erased and updated when ```while ( .calculating () ) ``` runs. Alternatively, it is possible to overwrite only a section of the screen, leaving the remainder unchanged. This is know as a **windowed update**.

To perform a windowed update, the parameter for *region*, along with the window dimensions should be set when calling `.calculating()`:

```c++
while( display.calculating(display.region.WINDOWED,
						/*left*/,
						/*top*/,
						/*width*/,
						/*height*/) )
{
	//Graphics commands go here e.g
	//display.drawRect(0, 0, 100, 100, display.colors.BLACK);
}
display.update();
```

Be aware that, due to hardware limitations of the displays, windows may only be drawn with a width which is a multiple of 8. *(Note: this limitation does not rotate with the `.setRotation()` command)*.

It is possible to place a window so that it will have precisely the requested dimensions, however this is not strictly required as the library will automatically expand the window until it both satisfies the hardware limitations, and is large enough to encompass the requested region.

This automatic expansion can lead to a border around your graphics. One way to work around this issue is to use the dimensions calculated in `.bounds.window.*` (see [drawing](#drawing)). 

```c++
display.drawRect(display.bounds.window.left(),
                 display.bounds.window.top(), 
                 display.bounds.window.width(),
                 display.bounds.window.height(), 
                 display.colors.BLACK);
```

*(That's a lot of typing for a value that you use so often..  - [yes, yes it is](#code-readability))*

These values are updated to reflect the true dimensions of the window, rather than the dimensions requested in `.calculating()`. This means that although your window won't be quite the size you asked for, you will at least be able to use its full width.

### Update Quality ###

By default, all displays perform what is referred to as a **detailed update**. This can take several seconds, as the image is carefully etched into the screen. Once again, this is a hardware process and not connected to this library.

Some E-Ink displays are designed with the ability to perform a **fast update**. These updates make take only a fraction of a second, but do give a lower image quality. 

This ability is not as common with the current generation of Heltec displays as it may be with other manufacturers, however this does remain subject to change as it is indeed possible for the software code required to perform these fast updates to be calculated and released even for pre-exsiting displays.

As it stands, only the *1.54" V2* display is capable of performing a fast update. This should be by setting the update quality parameter when calling `.update()`

```c++
 display.update(display.quality.FAST);
```

The image data drawn in fast mode remains in the display's RAM, meaning that it is possible to at some point redraw the screen image in *detailed mode* without requiring additional graphics commands. This is done by calling `.detail()`

### Code Readability ###

If you are at all like me, you might find that all these long calls make your code "wordy":

```c++
display.drawRect(display.bounds.window.left(),
                 display.bounds.window.top(), 
                 display.bounds.window.width(),
                 display.bounds.window.height(), 
                 display.colors.BLACK);
```

As an alternative, declaring "shortcuts" at the start of the code can really cut down on a lot of the bloat:

```c++
//Ugly mess here but
Heltec_154_V2::Bounds::Window w = display.bounds.window;
Heltec_154_V2::ColorList c = display.colors;
    
//Nice & clean here
display.drawRect( w.left(), w.top(), w.width(), w.height(), c.BLACK );
```



## Installation

**Arduino:** Library can be installed to Arduino IDE with *Sketch* -> *Include Library* -> *Add .Zip Library..*, or through the built-in Library Manager.

**Platform.io:** Available through the built-in library registiry, or alternatively, can be installed by extracting the Zip file to the lib folder of your project.

# Acknowledgements

This library is inspired by [GxEPD2](https://github.com/ZinggJM/GxEPD2), a similar project for Goodisplay and Waveshare displays.

Information on how to correctly communicate with the display hardware was provided by on the [official Heltec library](https://github.com/HelTecAutomation/e-ink).

The drawing functions are provided by [GFX Root](https://github.com/ZinggJM/GFX_Root), which itself is a stripped down version of [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library).
