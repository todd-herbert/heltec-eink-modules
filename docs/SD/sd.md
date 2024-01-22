# Heltec E-ink Modules - SD Card

These methods allow reading and writing **.bmp images** from an SD / MicroSD card, using a cheap SPI adapter.

With level-shifter  |   Without level-shifter
--------------------|-------------------------
![MicroSD module](adapter-level-shifter.png) | ![MicroSD module](adapter.png)

⚠ Depending on your adapter, and your Arduino, additional level-shifting circuitry may be required.

For more information, see: [wiring](/docs/README.md#wiring).

- [Limitations](#limitations)
- [loadFullscreenBMP()](#loadfullscreenbmp)
- [Save drawing to SD](#save-drawing-to-sd)
  - [Loading a saved image](#loading-a-saved-image)
- [Composing with .bmp](#composing-with-bmp)
- [Getting Info](#getting-info)


## Limitations

* Low speed
* Bigger sketches 
* Higher RAM usage
* Not all methods available for Uno
    * `draw24BitBMPFile()` consumes too much RAM
    * `SAVE_TO_SD()` must be enabled in [optimization.h](/src/optimization.h)
    * Uno HardwareSerial does not play nice with `SAVE_TO_SD()`. [Workaround here](/docs/sd/MinimalSerial.md)
* Card format must be FAT or FAT32

## loadFullscreenBMP()

This is an efficient method for loading a .bmp file directy to the display.

It accepts only a specific type of .bmp image.
* 24bit .bmp file
* Portrait, not landscape
* Dimensions: full screen width x height



Example: DEPG0290BNS75A | Example: QYEG0213RWS800
---|---
![diagram of "canvas"](canvas_depg0290bns75a.png) | ![diagram of "canvas"](canvas_qyeg0213rws800.png)

```cpp
#include <heltec-eink-modules.h>

DEPG0290BNS75A display(2, 4, 5);

void setup() {
    // Once, set CS pin
    display.useSD(7);

    display.loadFullscreeBMP("image.bmp");
}
```
## Save drawing to SD

Instead of drawing to display, the output can be directed into a canvas.

*Arduino Uno:* this feature is disabled by default, to minimize sketch size. See [optimization.h](/src/optimization.h)

```cpp
#include <heltec-eink-modules.h>

DEPG0150BNS810 display(2, 4, 5);

void setup() {
    // SD card CS pin 7
    display.useSD(7);

    // Save by filename
    SAVE_TO_SD (display, "canvas01.bmp") {
        //Graphics commands go here, for example:
        display.fillCircle(50, 100, 20, BLACK);
    }

    // Or: save by prefix + number
    SAVE_TO_SD (display, "canvas", 1) {
        //Graphics commands go here, for example:
        display.fillCircle(50, 100, 20, BLACK);
    }

}
```

If your microcontroller is powerful enough, you can [skip the `SAVE_TO_SD`](/docs/API.md#save_to_sd) loop (similar to `update()`)

```cpp
DEPG0290BNS75A display(2, 4, 5);

void setup() {
    // Once, set CS pin
    display.useSD(7);

    display.setCursor(20, 20);
    display.print("Hello, World!");

    display.saveToSD("test_canvas.bmp");
    
    // If you wish, you can also display the result without re-rendering
    // display.update();
}
```

`SAVE_CANVAS()` and `saveCanvas()` also accept integers, the same as `loadCanvas()` (above)

### Loading a saved image

You can either load a saved image by filename, or with the same prefix and numeric identifier you gave while saving.

```cpp
DEPG0290BNS75A display(2, 4, 5);

void setup() {
    // Once, set CS pin
    display.useSD(7);

    // Load by filename
    display.loadFullscreenBMP("chart005.bmp");
    
    // Or alternatively, by prefix + number
    display.loadFullscreenBMP("chart", 5);
}
```

## Composing with .bmp

Rather than immediately displaying a single .bmp file, you may want use the image as part of a complex drawing.

The most efficient option is to use "monochromatic bitmaps" (1-bit). These can be processed similarly to [XBitmaps](/docs/XBitmapTutorial/mono.md).

Much like XBitmaps, these are drawn as part of the normal drawing flow.

```cpp
DEPG0290BNS75A display(2, 4, 5);

void setup() {
    // Once, set CS pin
    display.useSD(7);

    DRAW (display) {
        display.drawMonoBMP(0, 0, "mono.bmp", BLACK);
    }    
}
```

Another option is to draw "24bit bitmaps" (color).
This is much less efficient, but could be convenient when working with 3-Color displays.

```cpp
DEPG0290BNS75A display(2, 4, 5);

void setup() {
    // Once, set CS pin
    display.useSD(7);

    DRAW (display) {
        display.draw24bitBMP(0, 0, "24bit.bmp");
    }    
}
```

## Getting Info

Several methods are provided to retrieve information about the SD card status and contents.

```cpp
DEPG0290BNS75A display(2, 4, 5);

void setup() {
    // Set CS pin
    display.useSD(7);

    // Check card connection
    if ( !display.SDCardFound() )
        return;

    // Check file
    if ( !display.SDFileExists("test.bmp" ))
        return;

    // Check if image file is suitable for loadFullscreenBMP()
    if ( !display.fullscreenBMPValid("test.bmp")) {
        // Do something?
    }


    // Check if valid for loadFullscreenBMP, and delete if corrupt
    if ( display.SDCanvasValid("test.bmp", true) ) {
        // Do something?
    }

    int width = display.getBMPWidth("test.bmp");
    int height = display.getBMPHeight("test.bmp");
}
```
