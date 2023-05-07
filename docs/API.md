# Heltec E-Ink Modules - API

- [Include Library](#include-library)
- [Methods](#methods)
  - [`DEPG0150BNS810()`](#depg0150bns810)
  - [`DEPG0154BNS800()`](#depg0154bns800)
  - [`DEPG0290BNS75A()`](#depg0290bns75a)
  - [`DEPG0290BNS800()`](#depg0290bns800)
  - [`GDEP015OC1()`](#gdep015oc1)
  - [`HTE029A1()`](#hte029a1)
  - [`QYEG0213RWS800()`](#qyeg0213rws800)
  - [`clear()`](#clear)
  - [`setDefaultColor()`](#setdefaultcolor)
  - [`setRotation()`](#setrotation)
  - [`setWindow()`](#setwindow)
  - [`fullscreen()`](#fullscreen)
  - [`setFastmode()`](#setfastmode)
  - [`setFlip()`](#setflip)
  - [`calculating()`](#calculating)
  - [`update()`](#update)
  - [`deepSleep()`](#deepsleep)
  - [`drawBitmap()`](#drawbitmap)
  - [`drawCircle()`](#drawcircle)
  - [`drawCircleHelper()`](#drawcirclehelper)
  - [`drawLine()`](#drawline)
  - [`drawPixel()`](#drawpixel)
  - [`drawRect()`](#drawrect)
  - [`drawRoundRect()`](#drawroundrect)
  - [`drawTriangle()`](#drawtriangle)
  - [drawXbitmap](#drawxbitmap)
  - [`fillCircle()`](#fillcircle)
  - [`fillRect()`](#fillrect)
  - [`fillRoundRect()`](#fillroundrect)
  - [`fillScreen()`](#fillscreen)
  - [`fillTriangle()`](#filltriangle)
  - [`getRotation()`](#getrotation)
  - [`getTextBounds()`](#gettextbounds)
  - [`getTextWidth()`](#gettextwidth)
  - [`getTextHeight()`](#gettextheight)
  - [`setTextColor()`](#settextcolor)
  - [`setTextWrap()`](#settextwrap)
  - [`setCursor()`](#setcursor)
  - [`setCursorTopLeft()`](#setcursortopleft)
  - [`getCursorX()`](#getcursorx)
  - [`getCursorY()`](#getcursory)
  - [`bounds.full.left()`](#boundsfullleft)
  - [`bounds.full.top()`](#boundsfulltop)
  - [`bounds.full.right()`](#boundsfullright)
  - [`bounds.full.bottom()`](#boundsfullbottom)
  - [`bounds.full.width()`](#boundsfullwidth)
  - [`bounds.full.height()`](#boundsfullheight)
  - [`bounds.full.centerX()`](#boundsfullcenterx)
  - [`bounds.full.centerY()`](#boundsfullcentery)
  - [`bounds.window.left()`](#boundswindowleft)
  - [`bounds.window.top()`](#boundswindowtop)
  - [`bounds.window.right()`](#boundswindowright)
  - [`bounds.window.bottom()`](#boundswindowbottom)
  - [`bounds.window.width()`](#boundswindowwidth)
  - [`bounds.window.height()`](#boundswindowheight)
  - [`bounds.window.centerX()`](#boundswindowcenterx)
  - [`bounds.window.centerY()`](#boundswindowcentery)
- [Constants](#constants)
  - [`colors`](#colors)
  - [`fastmode`](#fastmode)
  - [`flip`](#flip)
  - [`orientation`](#orientation)


## Include Library
```cpp
#include <heltec-eink-module.h>
```

## Methods

___
### `DEPG0150BNS810()`

Create a display controller object, for model [DEPG0150BNS810](/docs/README.md#identifying-your-display).

#### Syntax

```cpp
DEPG0150BNS810(DC_PIN, CS_PIN, BUSY_PIN)
DEPG0150BNS810(DC_PIN, CS_PIN, BUSY_PIN, page_height)
```

#### Parameters

* _DC_PIN_: pin which connects ([through a level shifter](/docs/README.md#wiring)) to "Display / Command" (D/C) pin on the display.
* _CS_PIN_: pin which connects ([through a level shifter](/docs/README.md#wiring)) to "Chip Select" (CS) on the display.
* _BUSY_PIN_: pin which connects to "BUSY" on the display.
* _page\_height_ (optional): number of rows per page. Default value is 20, meaning the display is calculated 20 rows at a time. Higher values consume more RAM

#### Example

```cpp
#include <heltec-eink-modules.h>

DEPG0150BNS810 display(8, 10, 7);
```

___
### `DEPG0154BNS800()`

Create a display controller object, for model [DEPG0154BNS800](/docs/README.md#identifying-your-display).

#### Syntax
```cpp
DEPG0154BNS800(DC_PIN, CS_PIN, BUSY_PIN)
DEPG0154BNS800(DC_PIN, CS_PIN, BUSY_PIN, page_height)
```

#### Parameters

* _DC_PIN_: pin which connects ([through a level shifter](/docs/README.md#wiring)) to "Display / Command" (D/C) pin on the display.
* _CS_PIN_: pin which connects ([through a level shifter](/docs/README.md#wiring)) to "Chip Select" (CS) on the display.
* _BUSY_PIN_: pin which connects to "BUSY" on the display.
* _page\_height_ (optional): number of rows per page. Default value is 20, meaning the display is calculated 20 rows at a time. Higher values consume more RAM

#### Example

```cpp
#include <heltec-eink-modules.h>

DEPG0154BNS800 display(8, 10, 7);
```

___
### `DEPG0290BNS75A()`

Create a display controller object, for model [DEPG0290BNS75A](/docs/README.md#identifying-your-display).

#### Syntax

```cpp
DEPG0290BNS75A(DC_PIN, CS_PIN, BUSY_PIN)
DEPG0290BNS75A(DC_PIN, CS_PIN, BUSY_PIN, page_height)
```

#### Parameters

* _DC_PIN_: pin which connects ([through a level shifter](/docs/README.md#wiring)) to "Display / Command" (D/C) pin on the display.
* _CS_PIN_: pin which connects ([through a level shifter](/docs/README.md#wiring)) to "Chip Select" (CS) on the display.
* _BUSY_PIN_: pin which connects to "BUSY" on the display.
* _page\_height_ (optional): number of rows per page. Default value is 20, meaning the display is calculated 20 rows at a time. Higher values consume more RAM

#### Example

```cpp
#include <heltec-eink-modules.h>

DEPG0290BNS75A display(8, 10, 7);
```

___
### `DEPG0290BNS800()`

Create a display controller object, for model [DEPG0290BNS800](/docs/README.md#identifying-your-display).

#### Syntax

```cpp
DEPG0290BNS800(DC_PIN, CS_PIN, BUSY_PIN)
DEPG0290BNS800(DC_PIN, CS_PIN, BUSY_PIN, page_height)
```

#### Parameters

* _DC_PIN_: pin which connects ([through a level shifter](/docs/README.md#wiring)) to "Display / Command" (D/C) pin on the display.
* _CS_PIN_: pin which connects ([through a level shifter](/docs/README.md#wiring)) to "Chip Select" (CS) on the display.
* _BUSY_PIN_: pin which connects to "BUSY" on the display.
* _page\_height_ (optional): number of rows per page. Default value is 20, meaning the display is calculated 20 rows at a time. Higher values consume more RAM

#### Example

```cpp
#include <heltec-eink-modules.h>

DEPG0290BNS800 display(8, 10, 7);
```

___
### `GDEP015OC1()`

Create a display controller object, for model [GDEP015OC1](/docs/README.md#identifying-your-display).

#### Syntax

```cpp
GDEP015OC1(DC_PIN, CS_PIN, BUSY_PIN)
GDEP015OC1(DC_PIN, CS_PIN, BUSY_PIN, page_height)
```

#### Parameters

* _DC_PIN_: pin which connects ([through a level shifter](/docs/README.md#wiring)) to "Display / Command" (D/C) pin on the display.
* _CS_PIN_: pin which connects ([through a level shifter](/docs/README.md#wiring)) to "Chip Select" (CS) on the display.
* _BUSY_PIN_: pin which connects to "BUSY" on the display.
* _page\_height_ (optional): number of rows per page. Default value is 20, meaning the display is calculated 20 rows at a time. Higher values consume more RAM

#### Example

```cpp
#include <heltec-eink-modules.h>

GDEP015OC1 display(8, 10, 7);
```

___
### `HTE029A1()`

Create a display controller object, for model [HTE029A1](/docs/README.md#identifying-your-display).

#### Syntax

```cpp
HTE029A1(DC_PIN, CS_PIN, BUSY_PIN)
HTE029A1(DC_PIN, CS_PIN, BUSY_PIN, page_height)
```

#### Parameters

* _DC_PIN_: pin which connects ([through a level shifter](/docs/README.md#wiring)) to "Display / Command" (D/C) pin on the display.
* _CS_PIN_: pin which connects ([through a level shifter](/docs/README.md#wiring)) to "Chip Select" (CS) on the display.
* _BUSY_PIN_: pin which connects to "BUSY" on the display.
* _page\_height_ (optional): number of rows per page. Default value is 20, meaning the display is calculated 20 rows at a time. Higher values consume more RAM

#### Example

```cpp
#include <heltec-eink-modules.h>

HTE029A1 display(8, 10, 7);
```

___
### `QYEG0213RWS800()`
Create a display controller object, for model [QYEG0213RWS800](/docs/README.md#identifying-your-display).

#### Syntax

```cpp
QYEG0213RWS800(DC_PIN, CS_PIN, BUSY_PIN)
QYEG0213RWS800(DC_PIN, CS_PIN, BUSY_PIN, page_height)
```

#### Parameters

* _DC_PIN_: pin which connects ([through a level shifter](/docs/README.md#wiring)) to "Display / Command" (D/C) pin on the display.
* _CS_PIN_: pin which connects ([through a level shifter](/docs/README.md#wiring)) to "Chip Select" (CS) on the display.
* _BUSY_PIN_: pin which connects to "BUSY" on the display.
* _page\_height_ (optional): number of rows per page. Default value is 20, meaning the display is calculated 20 rows at a time. Higher values consume more RAM

#### Example

```cpp
#include <heltec-eink-modules.h>

QYEG0213RWS800 display(8, 10, 7);
```

___
### `clear()`

Clear the display, along with its internal memory. This is a standalone method, called outside of the `calculating()` loop. The display will be cleared to solid white, unless changed using `setDefaultColor()`.

#### Syntax

```cpp
clear()
```

#### Parameters
None.

#### Example

```cpp
#include <heltec-eink-modules.h>

QYEG0213RWS800 display(8, 10, 7);

void setup() {
    display.clear();    // Display now changes to show solid white
    
    display.setDefaultColor(display.colors.BLACK);
    display.clear();    // Display clears instead to solid black
    
    ...

    display.clear();    // Clears again to solid black
}
```

#### See also

* [setDefaultColor()](#setdefaultcolor)

___
### `setDefaultColor()`

Sets the background color to be used for future display updates. All graphics operations are drawn on top of this background color. Also determines the color which is set during the standalone `clear()` method.

Default value is `.colors.WHITE`

#### Syntax

```cpp
display.setDefaultColor(bgcolor)
```

#### Parameters

* _bgcolor_: color to set as background

#### Example

```cpp
#include <heltec-eink-modules.h>

QYEG0213RWS800 display(8, 10, 7);

void setup() {
    display.clear();    // Display now changes to show solid white
    
    display.setDefaultColor(display.colors.BLACK);
    display.clear();    // Display clears instead to solid black
    
    ...

    display.clear();    // Clears again to solid black
}
```
#### See also

* [colors](#colors)

___
### `setRotation()`

Rotate future drawing operations by a multiple of 90 degrees. Avoid calling between `setWindow()` and the start of the `calculating()` loop.

#### Syntax

```cpp
setRotation(rotation)
```

#### Parameters

* _rotation_: absolute clockwise rotation, in 90 degree increments (1 = 90&deg;, 2=180&deg; etc) <br />
    Alternatively, pass one of the following:
    * `.orientation.PINS_ABOVE`
    * `.orientation.PINS_LEFT`
    * `.orientation.PINS_BELOW`
    * `.orientation.PINS_RIGHT`

#### Example

```cpp
#include <heltec-eink-modules.h>

DEPG0150BNS810 display(8, 10, 7);

void setup() {

    // Set the rotation before
    display.setRotation(display.orientation.PINS_BELOW);
    while( display.calculating() ) {
        display.setCursor(10, 10);
        display.print("Upside Down");
    }
    display.update();

    delay(2000);    // Pause to view the image

    // Set the rotation during
    while( display.calculating() ) {
        display.setCursor(10, 10);
        display.setRotation(0);     // No rotation
        display.print("top");

        display.setCursor(10, 10);
        display.setRotation(1);     // 1 * 90deg rotation
        display.print("left");

        display.setCursor(10, 10);
        display.setRotation( display.orientation.PINS_BELOW );     // 2 * 90deg rotation. (display's pins are now below the screen)
        display.print("bottom");
    }
    display.update();
}

void loop() {}
```
#### See also

* [orientation](#orientation)

___
### `setWindow()`
Draw to only a particular part of the screen ("a window"), leaving the remainder unchanged. Call before the `calculating()` loop. 

Window parameters are intepreted in the context of the current rotation. Avoid calling rotation between `setWindow()` and the start of the `calculating()` loop, or you will find that your window does not end up where you had intended! 

Because of a hardware limitation, window width (or height, if you are using a landscape rotation) is always a multiple of 8. Any value given will be automatically rounded up to the nearest multiple. For your convenience, these new "rounded up" dimensions are available through the `.bounds.window` feature. In this way, you can draw your graphics to cover the slightly expanded window, and work around the limitation. Note that the window will never "round down"; your originally requested region will always fit within the window provided.

#### Syntax

```cpp
display.setWindow(left, top, width, height)
```

#### Parameters

* _left_: left edge of the window
* _top_: top edge of the window
* _width_: width of the window
* _height_: height of the window

#### Example
```cpp
#include <heltec-eink-modules.h>

QYEG0213RWS800 display(8, 10, 7);

void setup() {
    display.clear();    // Fill screen with white

    display.setWindow(1, 1, 8, 3);  // Set the window dimensions
    display.setDefaultColor();      // Use black as our background color

    while ( display.calculating() ) {
        // Not actually doing anything
        // Just drawing the black background
    }

    display.update();
}

/* The result:

    0   1   2   3   4   5   6   7   8   9
0   
1   #   #   #   #   #   #   #   #
2   #   #   #   #   #   #   #   #
3

*/
```
#### See also

* [fullscreen()](#fullscreen)

___
### `fullscreen()`

Draw to the entire screen, rather than just a particular part. Undoes the `setWindow()` method. Call before the `calculating()` loop.

Fullscreen is the default state at start of sketch.

#### Syntax

```cpp
display.fullscreen()
```

#### Parameters

None.

#### See also

* [setWindow()](#setwindow)

___
### `setFastmode()`

Some displays have a secondary mode, where the image updates much faster. This is known officially as a *"Partial Refresh"*. For the sake of user-friendliness, this library instead uses the descriptive term *"Fast Mode*".

The trade-off is that images drawn in fast mode are of a lower quality. The process may also be particularly difficult on the hardware. **You should make sure to exit fast mode when not in use.**

Not all displays support fast mode. Some displays may have a physical limitation, however with others, it seems that the technical settings have not yet been calculated and released.

Note that this state is somewhat tempermental. If you wish to call `setWindow()`, or to return to `.fastmode.OFF`, you should first set `.fastmode.FINALIZE`

Calling `update()` during `.fastmode.ON` will have no effect; the display is updated automatically. Calling `update()` after `.fastmode.FINALIZE` is unnecessary; doing so will cause the whole screen to be redrawn with the slower, higher definition `.fastmode.OFF` method. This may be desirable.

If you are working in fullscreen, `.fastmode.FINALIZE` is not relevant, as the whole display will be re-rendered.

#### Syntax

```cpp
display.setFastmode(state)
```

#### Parameters

* _state_: the fastmode state to use. <br />
    Options are
    * `.fastmode.OFF` &nbsp;&nbsp; - &nbsp;&nbsp; Normal operation
    * `.fastmode.ON` &nbsp;&nbsp; - &nbsp;&nbsp; Fast-mode
    * `.fastmode.FINALIZE` &nbsp;&nbsp; - &nbsp;&nbsp; A special fast-mode state called before moving back to `.fastmode.OFF`

    Images drawn in ```.fastmode.FINALIZE``` are preserved when moving window, or returning to ```.fastmode.OFF```. <br />
    Images drawn in ```.fastmode.ON``` will not be preserved. 
    When ```.fastmode.FINALIZE``` has run, the display will automatically return to ```.fastmode.OFF```.

#### Example

```cpp
#include <heltec-eink-modules.h>

DEPG0150BNS810 display(8, 10, 7);

void setup() {
    display.clear();

    // Begin fastmode
    display.setFastmode( display.fastmode.ON );

    while( display.calculating() ) {
        display.setCursor(10, 10);
        display.print("ON");
    }
    delay(2000);

    while( display.calculating() ) {
        display.setCursor(10, 10);
        display.print("still ON");
    }
    delay(2000);

    // Still fastmode, but slower; preparing to mode to .OFF
    display.setFastmode( display.fastmode.FINALIZE );

    while( display.calculating() ) {
        display.setCursor(10, 10);
        display.print("FINALIZE");
    }

    //display.setFastmode( display.fastmode.OFF ) has been automatically called after .FINALIZE
    display.setWindow(0, 40, 100, 100);

    while( display.calculating() ) {
        display.setCursor(10, 40);
        display.print("OFF now..");
    }
    display.update();

}

void loop() {}
```

#### See also

* [fastmode](#fastmode)

___
### `setFlip()`

Reverse the image, either horizontally, or vertically. **Currently not supported with `setWindow`()**

#### Syntax

```cpp
setFlip(axis)
```

#### Parameters

* _axis_: which way to flip the image 
    Supported values:
    * `.flip.OFF`
    * `.flip.HORIZONTAL`
    * `.flip.VERTICAL`

#### Example

```cpp
#include <heltec-eink-modules.h>

DEPG0150BNS810 display(8, 10, 7);

void setup() {

    // Flip horizontally
    display.setFlip( display.flip.HORIZONTAL );
    
    while( display.calculating() ) {
        display.setCursor(10, 10);
        display.print("Mirrored Text");
    }

    display.update();
}
```


___
### `calculating()`

Used exclusively with a `while()` loop. Renders a slice of the image, and writes the result to the display's onboard memory. When using *fast-mode*, it also calls `update()` automatically.

#### Syntax

```cpp
while ( display.calculating() )
```

#### Parameters

None.

#### Returns

* `false` if the whole display is calculated, and the `while()` loop should end; or
* `true` to continue the loop, moving on to calculate the next display slice.

#### Example

```cpp
#include <heltec-eink-modules.h>

DEPG0150BNS810 display(8, 10, 7);

void setup() {

    while( display.calculating() ) {
        //Graphics commands go here, for example:
        display.fillCircle(50, 100, 20, display.colors.RED);
    }

    display.update();
}
```

#### See also

* [update](#update)


___
### `update()`

Display the calculated image on the E-ink screen. Called after the `calculating()` loop. Has no effect when called during fast-mode.

#### Syntax

```cpp
display.update()
```

#### Parameters

None.

#### Example

```cpp
#include <heltec-eink-modules.h>

DEPG0150BNS810 display(8, 10, 7);

void setup() {

    while( display.calculating() ) {
        display.setCursor(10, 10);
        display.print("Example");
    }

    display.update();   // Image on display changes with this command
}
```

___
### `deepSleep()`

Put the display into a low-power state. The display will not respond to any further commands until power has been fully removed. This can be done manually (unplugging your Arduino), or with external reset hardware.

#### Syntax

```cpp
display.deepSleep()
```

#### Parameters

None.

#### See also

* [README - Power Management](/docs/README.md#power-management)


___
### `drawBitmap()`

Draw a RAM-resident 1-bit image at the specified (x,y) position, using the specified foreground color (unset bits are transparent).

*This is an AdafruitGFX method*

#### Syntax

``` cpp
display.drawBitmap(x, y, bitmap, w, h, color, bg)
```

#### Parameters

* _x_:   Top left corner x coordinate
* _y_:   Top left corner y coordinate
* _bitmap_:  byte array with monochrome bitmap
* _w_:   Width of bitmap in pixels
* _h_:   Height of bitmap in pixels
* _color_: Color to draw pixels with
* _bg_: Color to draw background with

#### See also

* [colors](#colors)
* [drawXbitmap()](#drawxbitmap)

___
### `drawCircle()`

Draw a circle outline

*This is an AdafruitGFX method*

#### Syntax

```cpp
display.drawCircle( x, y, r, color)
```

#### Parameters

* _x0_: Center-point x coordinate
* _y0_: Center-point y coordinate
* _r_: Radius of circle
* _color_: Color to draw with

#### See also

* [fillCircle()](#fillcircle)
* [colors](#colors)

___
### `drawCircleHelper()`

Quarter-circle drawer, outline only

*This is an AdafruitGFX method*

#### Syntax

```cpp
display.drawCircleHelper(x, y, r, corner_mask, color)
```

#### Parameters

* _x_: Center-point x coordinate
* _y_: Center-point y coordinate
* _r_: Radius of circle
* _corner\_mask_: Which corner(s) to draw. Select by setting the first four bits: Least Signifact Bit for top left, travelling clockwise as bit # increases.
* _color_: Color to draw with 

#### Example

```cpp
#include <heltec-eink-modules.h>

DEPG0150BNS810 display(8, 10, 7);

void setup() {
    byte corners = 0;
    
    bool TOP_LEFT = false;
    bool TOP_RIGHT = true;
    bool BOTTOM_RIGHT = false;
    bool BOTTOM_LEFT = true;

    corners = (TOP_LEFT << 0) | (TOP_RIGHT << 1) | (BOTTOM_RIGHT << 2) | (BOTTOM_LEFT << 3);

    // Or alternatively..
    // corners = B1010;

    while( display.calculating() ) {
        display.drawCircleHelper(50, 50, 50, corners, display.colors.BLACK);
    }

    display.update();
}

void loop() {}
```

#### See also

* [colors](#colors)

___
### `drawLine()`

Draw a line

*This is an AdafruitGFX method*

#### Syntax

```cpp
display.drawLine(x0, y0, x1, y1, color)
```

#### Parameters
* _x0_:  Start point x coordinate
* _y0_:  Start point y coordinate
* _x1_:  End point x coordinate
* _y1_:  End point y coordinate
* _color_: Color to draw with

#### See also

* [colors](#colors)

___
### `drawPixel()`

Draw a single pixel

#### Syntax

```cpp
display.drawPixel(x, y, color)
```

#### Parameters

* _x_: X coordinate
* _y_: Y coordinate
* _color_: Color to draw with

#### See also

* [colors](#colors)

___
### `drawRect()`

 Draw a rectangle with no fill color

 *This is an AdafruitGFX method*

#### Syntax

```cpp
display.drawRect(x, y, w, h, color)
```

#### Parameters

* _x_:   Top left corner x coordinate
* _y_:   Top left corner y coordinate
* _w_:   Width in pixels
* _h_:   Height in pixels
* _r_:   Radius of corner rounding
* _color_: Color to draw with

#### See also

* [fillRect()](#fillrect)
* [drawRoundRect()](#drawroundrect)
* [fillRoundRect()](#fillroundrect)
* [colors](#colors)

___
### `drawRoundRect()`

Draw a rounded rectangle with no fill color

*This is an AdafruitGFX method*

#### Syntax

```cpp
display.drawRoundRect(x, y, w, h, r, color)
```

#### Parameters

* _x_: Top left corner x coordinate
* _y_: Top left corner y coordinate
* _w_: Width in pixels
* _h_: Height in pixels
* _r_: Radius of corner rounding
* _color_: Color to draw with

___
### `drawTriangle()`

Draw a triangle with no fill color

*This is an AdafruitGFX method*

#### Syntax

```cpp
display.drawTriangle(x0, y0, x1, y1, x2, y2, color)
```

#### Parameters

* _x0_: Vertex #0 x coordinate
* _y0_: Vertex #0 y coordinate
* _x1_: Vertex #1 x coordinate
* _y1_: Vertex #1 y coordinate
* _x2_: Vertex #2 x coordinate
* _y2_: Vertex #2 y coordinate
* _color_: Color to draw with

#### See also

* [fillTriangle](#filltriangle)
* [colors](#colors)

___
### drawXbitmap

Draw PROGMEM-resident XBitMap Files (*.xbm), exported from GIMP. See [tutorial on preparing XBitmap images](XBitmapTutorial/README.md).

*This is an AdafruitGFX method*

#### Syntax
```cpp
#include <heltec-eink-modules.h>
#include "chess_200x200.h"

DEPG0150BNS810 display(8, 10, 7);

void setup() {
    // Don't forget to set the orientation, so your image fits how you intended
    display.setRotation(display.orientation.PINS_LEFT);  

    while( display.calculating() ) {
        display.drawXBitmap(0, 0, chess_bits, chess_width, chess_height, display.colors.BLACK);
    }

    display.update();
}

void loop() {}
```

#### See also

* [drawBitmap()](#drawbitmap)
* [colors](#colors)

___
### `fillCircle()`

Draw a circle with filled color

*This is an AdafruitGFX method*

#### Syntax

```cpp
display.fillCircle(x, y, r, color)
```

#### Parameters

* _x0_: Center-point x coordinate
* _y0_: Center-point y coordinate
* _r_: Radius of circle
* _color_: Color to fill with


___
### `fillRect()`

Fill a rectangle completely with one color

*This is an AdafruitGFX method*

#### Syntax

```cpp
display.fillRect(x, y, w, h, color)
```

#### Parameters
* _x_:  Start point x coordinate
* _y_:  Start point y coordinate
* _x_:  End point x coordinate
* _y_:  End point y coordinate
* _color_: Color to fill with

#### See also

* [drawRect()](#drawrect)
* [drawRoundRect()](#drawroundrect)
* [fillRoundRect()](#fillroundrect)
* [colors](#colors)

___
### `fillRoundRect()`

Draw a rounded rectangle with fill color

*This is an AdafruitGFX method*

#### Syntax

```cpp
display.fillRoundRect(x, y, w, h, r, color)
```

#### Parameters

* _x_: Top left corner x coordinate
* _y_: Top left corner y coordinate
* _w_: Width in pixels
* _h_: Height in pixels
* _r_: Radius of corner rounding
* _color_: 16-bit 5-6-5 Color to draw/fill with

#### See also

* [drawRect()](#drawrect)
* [drawRoundRect()](#drawroundrect)
* [fillRoundRect()](#fillroundrect)
* [colors](#colors)


___
### `fillScreen()`

Fill the screen completely with one color. **Inefficient, consider instead `setDefaultColor()`**

*This is an AdafruitGFX method*

#### Syntax

```cpp
display.fillScreen(color)
```

#### Parameters

* _color_: Color to draw with

#### See also

* [setDefaultColor](#setdefaultcolor)
* [colors](#colors)

___
### `fillTriangle()`

Draw a triangle with color-fill

*This is an AdafruitGFX method*

#### Syntax

```cpp
display.fillTriangle(x0, y0, x1, y1, x2, y2, color)
```

#### Parameters

* _x0_: Vertex #0 x coordinate
* _y0_: Vertex #0 y coordinate
* _x1_: Vertex #1 x coordinate
* _y1_: Vertex #1 y coordinate
* _x2_: Vertex #2 x coordinate
* _y2_: Vertex #2 y coordinate
* _color_: Color to fill with

#### See also

* [drawTriangle()](#drawtriangle)
* [colors](#colors)

___
### `getRotation()`
Get rotation setting for display

*This is an AdafruitGFX method*

#### Syntax

```cpp
display.getRotation()
```

#### Parameters

None.

#### Returns

0 through 3, corresponding to 4 cardinal rotations

#### See also

* [setRotation()](#setrotation)
* [orientation](#orientation)

___
### `getTextBounds()`

Helper to determine size of a string with current font/size. Pass string and a cursor position, returns UL corner and W,H.

*This is an AdafruitGFX method*

#### Syntax

```cpp
getTextBounds(str, x, y, x1 y1 )
```

#### Parameters

* _str_: The ascii string to measure
* _x_: The current cursor X
* _y_: The current cursor Y
* _x1_: The boundary X coordinate, set by function, **pass by reference**
* _y1_: The boundary Y coordinate, set by function, **pass by reference**
* _w_: The boundary width, set by function, **pass by reference**
* _h_: The boundary height, set by function, **pass by reference**

#### Returns

None. Variables passed by reference will be set.

#### See also

* [getTextWidth()](#gettextwidth)
* [getTextHeight()](#gettextheight)

___
### `getTextWidth()`

Gets width of a string, given the current font settings. Wrapper for `getTextBounds()`

#### Syntax

```cpp
display.getTextWidth(text)
```

#### Parameters

* _text_: the string to measure, as a char array or char pointer

#### Returns

The width of the string.

#### See also

* [getTextWidth()](#gettextbounds)

___
### `getTextHeight()`

Gets height of a string, given the current font settings. Wrapper for `getTextBounds()`

#### Syntax

```cpp
display.getTextHeight(text)
```

#### Parameters

* _text_: the string to measure, as a char array or char pointer

#### Returns

The height of the string.

#### See also

* [getTextWidth()](#gettextbounds)

___
### `setTextColor()`

Set text font color, with or without a background

*This is an AdafruitGFX method*

#### Syntax

```cpp
display.setTextColor(c)
display.setTextColor(c, bg)
```

#### Parameters

* _c_: color to draw text with
* _bg_: (optional) color to draw background/fill with

#### See also

* [colors](#colors)

___
### `setTextWrap()`

Set whether text that is too long for the screen width should automatically wrap around to the next line (else clip right).

*This is an AdafruitGFX method*

#### Syntax

```cpp
display.setTextWrap(w)
```

#### Parameters
* _w_: `true` for wrapping, `false` for clipping.

___
### `setCursor()`

Set text cursor location. *Make sure to use inside the `calculating()` loop*.

*This is an AdafruitGFX method*

#### Syntax

```cpp
display.setCursor(x, y)
```

#### Parameters
* _x_: X coordinate in pixels
* _y_: Y coordinate in pixels

#### See also

* [setCursorTopLeft()](#setcursortopleft)

___
### `setCursorTopLeft()`

Wraps `getTextBounds()` and `setCursor()`, for convenience. Set the text cursor according to the desired upper left corner

#### Syntax

```cpp
display.setCursorTopLeft(text, x, y)
```

#### Parameters

* _text_: The text, as char array or char pointer, to be measured for finding top left.
* _x_: Target X coordinate
* _y_: Target Y coordinate

#### See also

* [setCursor()](#setcursor)

___
### `getCursorX()`

Get current cursor position

*This is an AdafruitGFX method*

#### Syntax

```cpp
display.getCursorX()
```

#### Parameters

None.

#### Returns

X Coordinate in pixels

___
### `getCursorY()`

Get text cursor Y location

*This is an AdafruitGFX method*

#### Syntax

```cpp
display.getCursorY()
```

#### Parameters

None.

#### Returns

Y coordinate in pixels

___
### `bounds.full.left()`

Get the left edge of the display. This will always be zero, but is included for completeness.

#### Syntax

```cpp
display.bounds.full.left()
```

#### Parameters

None.

#### Returns

Position of the left edge of the full display, in pixels.

___
### `bounds.full.top()`

Get the top edge of the display. This will always be zero, but is included for completeness.

#### Syntax

```cpp
display.bounds.full.top()
```

#### Parameters

None.

#### Returns

Position of the top edge of the full display, in pixels.

___
### `bounds.full.right()`

Get the right edge of the display. Value will change to match the current rotation.

#### Syntax

```cpp
display.bounds.full.right()
```

#### Parameters

None.

#### Returns

Position of the right edge of the full display, in pixels.

___
### `bounds.full.bottom()`

Get the bottom edge of the display. Value will change to match the current rotation.

#### Syntax

```cpp
display.bounds.full.bottom()
```

#### Parameters

None.

#### Returns

Position bottom edge of the full display, in pixels.

___
### `bounds.full.width()`

Get the width of the display. A display with width 200 will have a left edge of 0, and a right edge of 199. Value will change to match the current rotation.

#### Syntax

```cpp
display.bounds.full.width()
```

#### Parameters

None.

#### Returns

Width of the full display, in pixels.

___
### `bounds.full.height()`

Get the height of the display. A display with height 200 will have a top edge of 0, and a bottom edge of 199. Value will change to match the current rotation.

#### Syntax

```cpp
display.bounds.full.height()
```

#### Parameters

None.

#### Returns

Height of the full display, in pixels.

___
### `bounds.full.centerX()`

Get the horizontal midpoint of the display. If the center is between two pixels, the leftmost is returned. Value will change to match the current rotation.

#### Syntax

```cpp
display.bounds.full.centerX()
```

#### Parameters

None.

#### Returns

Horizontal center of the full display, in pixels.

___
### `bounds.full.centerY()`

Get the vertical midpoint of the display. If the center is between two pixels, the topmost is returned. Value will change to match the current rotation.

#### Syntax

```cpp
display.bounds.full.centerY()
```

#### Parameters

None.

#### Returns

Vertical center of the full display, in pixels.

-------------------------------------------------

___
### `bounds.window.left()`

Get the left edge of the current window, after it has been expanded to meet hardware requirements. Value will change to match the current rotation.

#### Syntax

```cpp
display.bounds.window.left()
```

#### Parameters

None.

#### Returns

Position of the left edge of the current window, in pixels.

___
### `bounds.window.top()`

Get the top edge of the current window, after it has been expanded to meet hardware requirements. Value will change to match the current rotation.

#### Syntax

```cpp
display.bounds.window.top()
```

#### Parameters

None.

#### Returns

Position of the top edge of the current window, in pixels.

___
### `bounds.window.right()`

Get the right edge of the current window, after it has been expanded to meet hardware requirements. Value will change to match the current rotation.

#### Syntax

```cpp
display.bounds.window.right()
```

#### Parameters

None.

#### Returns

Position of the right edge of the current window, in pixels.

___
### `bounds.window.bottom()`

Get the bottom edge of the current window, after it has been expanded to meet hardware requirements. Value will change to match the current rotation.

#### Syntax

```cpp
display.bounds.window.bottom()
```

#### Parameters

None.

#### Returns

Position bottom edge of the current window, in pixels.

___
### `bounds.window.width()`

Get the width of the current window. A window with a left edge of 0, and a right edge of 7, would have a width of 8. Value will change to match the current rotation.

#### Syntax

```cpp
display.bounds.window.width()
```

#### Parameters

None.

#### Returns

Width of the current window, in pixels.

___
### `bounds.window.height()`

Get the height of the current window. A window with a top edge of 0, and a bottom edge of 7, would have a height of 8. Value will change to match the current rotation.

#### Syntax

```cpp
display.bounds.window.height()
```

#### Parameters

None.

#### Returns

Height of the current window, in pixels.

___
### `bounds.window.centerX()`

Get the horizontal midpoint of the current window. If the center is between two pixels, the leftmost is returned. Value will change to match the current rotation.

#### Syntax

```cpp
display.bounds.window.centerX()
```

#### Parameters

None.

#### Returns

Horizontal center of the current window, in pixels.

___
### `bounds.window.centerY()`

Get the vertical midpoint of the current window. If the center is between two pixels, the topmost is returned. Value will change to match the current rotation.

#### Syntax

```cpp
display.bounds.window.centerY()
```

#### Parameters

None.

#### Returns
Vertical center of the current window, in pixels.

## Constants

This section describes the various constants (as *enumerations*), which are accepted as parameters by various methods throughout the library.

___
### `colors`

#### Values

* `.colors.WHITE`
* `.colors.BLACK`
* `.colors.RED` - Supported displays only

#### Example

```cpp
display.setDefaultColor( display.colors.BLACK )
```

___
### `fastmode`

Used to move the display in and out of fast-mode. Passed to `setFastmode()'

#### Values

* `.fastmode.OFF`: normal operation
* `.fastmode.ON`: update the screen using fastmode
* `.fastmode.FINALIZE`: called to exit fastmode, to preserve the display and return to normal operation

#### Example

```cpp
display.setFastmode( display.fastmode.ON )
```

___
### `flip`

Specify along which axis the screen should be flipped (mirrored)

#### Values

* `.flip.NONE`
* `.flip.HORIZONTAL`
* `.flip.VERTICAL`

#### Example

```cpp
display.setFlip( display.flip.HORIZONTAL )
```

___
### `orientation`

A convenient shortcut for getting the correct display rotation. Describes the desired rotation in relation to the header pins on the module.

#### Values

* `.orientation.PINS_ABOVE`
* `.orientation.PINS_LEFT`
* `.orientation.PINS_BELOW`
* `.orientation.PINS_RIGHT`

#### Example

```cpp
display.setRotation( display.orientation.PINS_LEFT )
```
