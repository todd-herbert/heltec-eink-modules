# Heltec E-Ink Modules - API

- [Include Library](#include-library)
- [Display Constructors](#display-constructors)
  - [`DEPG0150BNS810()`](#depg0150bns810)
  - [`DEPG0154BNS800()`](#depg0154bns800)
  - [`DEPG0213BNS800`](#depg0213bns800)
  - [`DEPG0213RWS800()`](#depg0213rws800)
  - [`DEPG0290BNS75A()`](#depg0290bns75a)
  - [`DEPG0290BNS800()`](#depg0290bns800)
  - [`EInkDisplay_VisionMasterE213`](#einkdisplay_visionmastere213)
  - [`EInkDisplay_VisionMasterE290`](#einkdisplay_visionmastere290)
  - [`EInkDisplay_WirelessPaperV1`](#einkdisplay_wirelesspaperv1)
  - [`EInkDisplay_WirelessPaperV1_1`](#einkdisplay_wirelesspaperv1_1)
  - [`GDE029A1()`](#gde029a1)
  - [`GDEP015OC1()`](#gdep015oc1)
  - [`LCMEN2R13EFC1`](#lcmen2r13efc1)
  - [`QYEG0213RWS800()`](#qyeg0213rws800)
- [Methods](#methods)
  - [`begin()`](#begin)
  - [`bottom()`](#bottom)
  - [`centerX()`](#centerx)
  - [`centerY()`](#centery)
  - [`clear()`](#clear)
  - [`clearMemory()`](#clearmemory)
  - [`DRAW()`](#draw)
  - [`draw24bitBMP()`](#draw24bitbmp)
  - [`drawBitmap()`](#drawbitmap)
  - [`drawCircle()`](#drawcircle)
  - [`drawCircleHelper()`](#drawcirclehelper)
  - [`drawLine()`](#drawline)
  - [`drawMonoBMP()`](#drawmonobmp)
  - [`drawPixel()`](#drawpixel)
  - [`drawRect()`](#drawrect)
  - [`drawRoundRect()`](#drawroundrect)
  - [`drawTriangle()`](#drawtriangle)
  - [`drawXBitmap()`](#drawxbitmap)
  - [`customPowerOff()`](#custompoweroff)
  - [`customPowerOn()`](#custompoweron)
  - [`fastmodeOff()`](#fastmodeoff)
  - [`fastmodeOn()`](#fastmodeon)
  - [`fastmodeTurbo()`](#fastmodeturbo)
  - [`fillCircle()`](#fillcircle)
  - [`fillRect()`](#fillrect)
  - [`fillRoundRect()`](#fillroundrect)
  - [`fillScreen()`](#fillscreen)
  - [`fillTriangle()`](#filltriangle)
  - [`fullscreen()`](#fullscreen)
  - [`fullscreenBMPValid()`](#fullscreenbmpvalid)
  - [`getBMPHeight()`](#getbmpheight)
  - [`getBMPWidth()`](#getbmpwidth)
  - [`getCursorX()`](#getcursorx)
  - [`getCursorY()`](#getcursory)
  - [`getRotation()`](#getrotation)
  - [`getTextBounds()`](#gettextbounds)
  - [`getTextCenterX()`](#gettextcenterx)
  - [`getTextCenterY()`](#gettextcentery)
  - [`getTextHeight()`](#gettextheight)
  - [`getTextWidth()`](#gettextwidth)
  - [`height()`](#height)
  - [`landscape()`](#landscape)
  - [`left()`](#left)
  - [`loadFullscreenBMP()`](#loadfullscreenbmp)
  - [`print()`](#print)
  - [`printCenter()`](#printcenter)
  - [`println()`](#println)
  - [`portrait()`](#portrait)
  - [`right()`](#right)
  - [`SAVE_TO_SD()`](#save_to_sd)
  - [`saveToSD()`](#savetosd)
  - [`SDCardFound()`](#sdcardfound)
  - [`SDFileExists()`](#sdfileexists)
  - [`setBackgroundColor()`](#setbackgroundcolor)
  - [`setCursor()`](#setcursor)
  - [`setCursorTopLeft()`](#setcursortopleft)
  - [`setFont()`](#setfont)
  - [`setFlip()`](#setflip)
  - [`setRotation()`](#setrotation)
  - [`setTextColor()`](#settextcolor)
  - [`setTextWrap()`](#settextwrap)
  - [`setWindow()`](#setwindow)
  - [`top()`](#top)
  - [`update()`](#update)
  - [`useCustomPowerSwitch()`](#usecustompowerswitch)
  - [`useSD()`](#usesd)
  - [`width()`](#width)
  - [`window.left()`](#windowleft)
  - [`window.top()`](#windowtop)
  - [`window.right()`](#windowright)
  - [`window.bottom()`](#windowbottom)
  - [`window.width()`](#windowwidth)
  - [`window.height()`](#windowheight)
  - [`window.centerX()`](#windowcenterx)
  - [`window.centerY()`](#windowcentery)
- [Constants](#constants)
  - [`Color`](#color)
  - [`Flip`](#flip)
  - [`Rotation`](#rotation)
  - [`SwitchType`](#switchtype)


## Include Library
```cpp
#include <heltec-eink-modules.h>
```

## Display Constructors

### `DEPG0150BNS810()`

Create a display controller object, for model [DEPG0150BNS810](/docs/README.md#154-inch-e-ink-display-v2).

#### Syntax

```cpp
DEPG0150BNS810(DC_PIN, CS_PIN, BUSY_PIN)
DEPG0150BNS810(DC_PIN, CS_PIN, BUSY_PIN, page_height)
DEPG0150BNS810(DC_PIN, CS_PIN, BUSY_PIN, SDI_PIN, CLK_PIN)  // ESP32 or SAMD21G18A only
DEPG0150BNS810(DC_PIN, CS_PIN, BUSY_PIN, SDI_PIN, CLK_PIN, page_height) // ESP32 or SAMD21G18A only
```

#### Parameters

* _DC_PIN_: pin which connects to "Display / Command" (D/C) pin on the display.
* _CS_PIN_: pin which connects to "Chip Select" (CS) on the display.
* _BUSY_PIN_: pin which connects to "BUSY" on the display.
* _SDI_PIN_: pin which connects to "SDI" on the display. *ESP32 or SAMD21G18A only*
* _CLK_PIN_: pin which connects to "CLK" on the display. *ESP32 or SAMD21G18A only*
* _page\_height_ (optional): number of rows per page. For Arduino Uno default value is 20, meaning the display is calculated 20 rows at a time. Higher values consume more RAM. For more powerful boards, paging is disabled by default.

#### Example

```cpp
#include <heltec-eink-modules.h>

DEPG0150BNS810 display(2, 4, 5);
```

___
### `DEPG0154BNS800()`

Create a display controller object, for model [DEPG0154BNS800](/docs/README.md#154-inch-e-ink-display-v2).

#### Syntax
```cpp
DEPG0154BNS800(DC_PIN, CS_PIN, BUSY_PIN)
DEPG0154BNS800(DC_PIN, CS_PIN, BUSY_PIN, page_height)
DEPG0154BNS800(DC_PIN, CS_PIN, BUSY_PIN, SDI_PIN, CLK_PIN)  // ESP32 or SAMD21G18A only
DEPG0154BNS800(DC_PIN, CS_PIN, BUSY_PIN, SDI_PIN, CLK_PIN, page_height) // ESP32 or SAMD21G18A only
```

#### Parameters

* _DC_PIN_: pin which connects to "Display / Command" (D/C) pin on the display.
* _CS_PIN_: pin which connects to "Chip Select" (CS) on the display.
* _BUSY_PIN_: pin which connects to "BUSY" on the display.
* _SDI_PIN_: pin which connects to "SDI" on the display. *ESP32 or SAMD21G18A only*
* _CLK_PIN_: pin which connects to "CLK" on the display. *ESP32 or SAMD21G18A only*
* _page\_height_ (optional): number of rows per page. For Arduino Uno default value is 20, meaning the display is calculated 20 rows at a time. Higher values consume more RAM. For more powerful boards, paging is disabled by default.

#### Example

```cpp
#include <heltec-eink-modules.h>

DEPG0154BNS800 display(2, 4, 5);
```

___
### `DEPG0213BNS800`
Create a display controller object, for for model DEPG0213BNS800, which is used on original "Wireless Paper" all-in-one boards (V1).

Display instances of this class should be declared without parentheses, or they will be mistaken for a function prototype. See example.

#### Parameters

None.

#### Example

```cpp
#include <heltec-eink-modules.h>

DEPG0213BNS800 display;
```

___
### `DEPG0213RWS800()`
Create a display controller object, for model [DEPG0213RWS800](/docs/README.md#213-inch-e‑ink-display-v2).

#### Syntax

```cpp
DEPG0213RWS800(DC_PIN, CS_PIN, BUSY_PIN)
DEPG0213RWS800(DC_PIN, CS_PIN, BUSY_PIN, page_height)
DEPG0213RWS800(DC_PIN, CS_PIN, BUSY_PIN, SDI_PIN, CLK_PIN)  // ESP32 or SAMD21G18A only
DEPG0213RWS800(DC_PIN, CS_PIN, BUSY_PIN, SDI_PIN, CLK_PIN, page_height) // ESP32 or SAMD21G18A only
```

#### Parameters

* _DC_PIN_: pin which connects to "Display / Command" (D/C) pin on the display.
* _CS_PIN_: pin which connects to "Chip Select" (CS) on the display.
* _BUSY_PIN_: pin which connects to "BUSY" on the display.
* _SDI_PIN_: pin which connects to "SDI" on the display. *ESP32 or SAMD21G18A only*
* _CLK_PIN_: pin which connects to "CLK" on the display. *ESP32 or SAMD21G18A only*
* _page\_height_ (optional): number of rows per page. For Arduino Uno default value is 20, meaning the display is calculated 20 rows at a time. Higher values consume more RAM. For more powerful boards, paging is disabled by default.

#### Example

```cpp
#include <heltec-eink-modules.h>

DEPG0213RWS800 display(2, 4, 5);
```

___
### `DEPG0290BNS75A()`

Create a display controller object, for model [DEPG0290BNS75A](/docs/README.md#29-inch-e‑ink-display-v2).

#### Syntax

```cpp
DEPG0290BNS75A(DC_PIN, CS_PIN, BUSY_PIN)
DEPG0290BNS75A(DC_PIN, CS_PIN, BUSY_PIN, page_height)
DEPG0290BNS75A(DC_PIN, CS_PIN, BUSY_PIN, SDI_PIN, CLK_PIN)  // ESP32 or SAMD21G18A only
DEPG0290BNS75A(DC_PIN, CS_PIN, BUSY_PIN, SDI_PIN, CLK_PIN, page_height) // ESP32 or SAMD21G18A only
```

#### Parameters

* _DC_PIN_: pin which connects to "Display / Command" (D/C) pin on the display.
* _CS_PIN_: pin which connects to "Chip Select" (CS) on the display.
* _BUSY_PIN_: pin which connects to "BUSY" on the display.
* _SDI_PIN_: pin which connects to "SDI" on the display. *ESP32 or SAMD21G18A only*
* _CLK_PIN_: pin which connects to "CLK" on the display. *ESP32 or SAMD21G18A only*
* _page\_height_ (optional): number of rows per page. For Arduino Uno default value is 20, meaning the display is calculated 20 rows at a time. Higher values consume more RAM. For more powerful boards, paging is disabled by default.

#### Example

```cpp
#include <heltec-eink-modules.h>

DEPG0290BNS75A display(2, 4, 5);
```

___
### `DEPG0290BNS800()`

Create a display controller object, for model [DEPG0290BNS800](/docs/README.md#29-inch-e‑ink-display-v2).

#### Syntax

```cpp
DEPG0290BNS800(DC_PIN, CS_PIN, BUSY_PIN)
DEPG0290BNS800(DC_PIN, CS_PIN, BUSY_PIN, page_height)
DEPG0290BNS800(DC_PIN, CS_PIN, BUSY_PIN, SDI_PIN, CLK_PIN)  // ESP32 or SAMD21G18A only
DEPG0290BNS800(DC_PIN, CS_PIN, BUSY_PIN, SDI_PIN, CLK_PIN, page_height) // ESP32 or SAMD21G18A only
DEPG0290BNS800 // Vision Master E290
```

#### Parameters

* _DC_PIN_: pin which connects to "Display / Command" (D/C) pin on the display.
* _CS_PIN_: pin which connects to "Chip Select" (CS) on the display.
* _BUSY_PIN_: pin which connects to "BUSY" on the display.
* _SDI_PIN_: pin which connects to "SDI" on the display. *ESP32 or SAMD21G18A only*
* _CLK_PIN_: pin which connects to "CLK" on the display. *ESP32 or SAMD21G18A only*
* _page\_height_ (optional): number of rows per page. For Arduino Uno default value is 20, meaning the display is calculated 20 rows at a time. Higher values consume more RAM. For more powerful boards, paging is disabled by default.

#### Example

```cpp
#include <heltec-eink-modules.h>

DEPG0290BNS800 display(2, 4, 5);
```

___
### `EInkDisplay_VisionMasterE213`
Create a display controller object, for Vision Master E213 boards.

Display instances of this class should be declared without parentheses, or they will be mistaken for a function prototype. See example.

*This is an alias for [`LCMEN2R13EFC1`](#lcmen2r13efc1).*

#### Parameters

None.

#### Example

```cpp
#include <heltec-eink-modules.h>

EInkDisplay_VisionMasterE213 display;
```

___
### `EInkDisplay_VisionMasterE290`
Create a display controller object, for Vision Master E290 boards.

Display instances of this class should be declared without parentheses, or they will be mistaken for a function prototype. See example.

*This is an alias for [`DEPG0290BNS800`](#depg0290bns800).*

#### Parameters

None.

#### Example

```cpp
#include <heltec-eink-modules.h>

EInkDisplay_VisionMasterE290 display;
```

___
### `EInkDisplay_WirelessPaperV1`
Create a display controller object, for the original Wireless Paper boards (V1). These models are no longer produced, and have been replaced with the V1.1 version.

Display instances of this class should be declared without parentheses, or they will be mistaken for a function prototype. See example.

*This is an alias for [`DEPG0213BNS800`](#depg0213bns800).*

#### Parameters

None.

#### Example

```cpp
#include <heltec-eink-modules.h>

EInkDisplay_WirelessPaperV1 display;
```

___
### `EInkDisplay_WirelessPaperV1_1`
Create a display controller object, for Wireless Paper V1.1 boards.

Display instances of this class should be declared without parentheses, or they will be mistaken for a function prototype. See example.

*This is an alias for [`LCMEN2R13EFC1`](#lcmen2r13efc1).*

#### Parameters

None.

#### Example

```cpp
#include <heltec-eink-modules.h>

EInkDisplay_WirelessPaperV1_1 display;
```

___
### `GDE029A1()`

Create a display controller object, for model [GDE029A1](/docs/README.md#29-inch-e‑ink-display-v2).

#### Syntax

```cpp
GDE029A1(DC_PIN, CS_PIN, BUSY_PIN)
GDE029A1(DC_PIN, CS_PIN, BUSY_PIN, page_height)
GDE029A1(DC_PIN, CS_PIN, BUSY_PIN, SDI_PIN, CLK_PIN)  // ESP32 or SAMD21G18A only
GDE029A1(DC_PIN, CS_PIN, BUSY_PIN, SDI_PIN, CLK_PIN, page_height) // ESP32 or SAMD21G18A only
```

#### Parameters

* _DC_PIN_: pin which connects to "Display / Command" (D/C) pin on the display.
* _CS_PIN_: pin which connects to "Chip Select" (CS) on the display.
* _BUSY_PIN_: pin which connects to "BUSY" on the display.
* _SDI_PIN_: pin which connects to "SDI" on the display. *ESP32 or SAMD21G18A only*
* _CLK_PIN_: pin which connects to "CLK" on the display. *ESP32 or SAMD21G18A only*
* _page\_height_ (optional): number of rows per page. For Arduino Uno default value is 20, meaning the display is calculated 20 rows at a time. Higher values consume more RAM. For more powerful boards, paging is disabled by default.

#### Example

```cpp
#include <heltec-eink-modules.h>

GDE029A1 display(2, 4, 5);
```

___
### `GDEP015OC1()`

Create a display controller object, for model [GDEP015OC1](/docs/README.md#154-inch-e-ink-display-v2).

#### Syntax

```cpp
GDEP015OC1(DC_PIN, CS_PIN, BUSY_PIN)
GDEP015OC1(DC_PIN, CS_PIN, BUSY_PIN, page_height)
GDEP015OC1(DC_PIN, CS_PIN, BUSY_PIN, SDI_PIN, CLK_PIN)  // ESP32 or SAMD21G18A only
GDEP015OC1(DC_PIN, CS_PIN, BUSY_PIN, SDI_PIN, CLK_PIN, page_height) // ESP32 or SAMD21G18A only
```

#### Parameters

* _DC_PIN_: pin which connects to "Display / Command" (D/C) pin on the display.
* _CS_PIN_: pin which connects to "Chip Select" (CS) on the display.
* _BUSY_PIN_: pin which connects to "BUSY" on the display.
* _SDI_PIN_: pin which connects to "SDI" on the display. *ESP32 or SAMD21G18A only*
* _CLK_PIN_: pin which connects to "CLK" on the display. *ESP32 or SAMD21G18A only*
* _page\_height_ (optional): number of rows per page. For Arduino Uno default value is 20, meaning the display is calculated 20 rows at a time. Higher values consume more RAM. For more powerful boards, paging is disabled by default.

#### Example

```cpp
#include <heltec-eink-modules.h>

GDEP015OC1 display(2, 4, 5);
```

___
### `LCMEN2R13EFC1`
Create a display controller object, for model LCMEN2R13EFC1, which is used on "Wireless Paper" and "Vision Master E213" all-in-one boards.

*`EInkDisplay_WirelessPaperV1_1` and `EInkDisplay_VisionMasterE213` are aliases for this class.*

Display instances of this class should be declared without parentheses, or they will be mistaken for a function prototype. See example.

#### Syntax

```cpp
LCMEN2R13EFC1
```

#### Parameters

None.

#### Example

```cpp
#include <heltec-eink-modules.h>

LCMEN2R13EFC1 display;
```

___
### `QYEG0213RWS800()`
Create a display controller object, for model [QYEG0213RWS800](/docs/README.md#213-inch-e‑ink-display-v2).

#### Syntax

```cpp
QYEG0213RWS800(DC_PIN, CS_PIN, BUSY_PIN)
QYEG0213RWS800(DC_PIN, CS_PIN, BUSY_PIN, page_height)
QYEG0213RWS800(DC_PIN, CS_PIN, BUSY_PIN, SDI_PIN, CLK_PIN)  // ESP32 or SAMD21G18A only
QYEG0213RWS800(DC_PIN, CS_PIN, BUSY_PIN, SDI_PIN, CLK_PIN, page_height) // ESP32 or SAMD21G18A only
```

#### Parameters

* _DC_PIN_: pin which connects to "Display / Command" (D/C) pin on the display.
* _CS_PIN_: pin which connects to "Chip Select" (CS) on the display.
* _BUSY_PIN_: pin which connects to "BUSY" on the display.
* _SDI_PIN_: pin which connects to "SDI" on the display. *ESP32 or SAMD21G18A only*
* _CLK_PIN_: pin which connects to "CLK" on the display. *ESP32 or SAMD21G18A only*
* _page\_height_ (optional): number of rows per page. For Arduino Uno default value is 20, meaning the display is calculated 20 rows at a time. Higher values consume more RAM. For more powerful boards, paging is disabled by default.

#### Example

```cpp
#include <heltec-eink-modules.h>

QYEG0213RWS800 display(2, 4, 5);
```

## Methods

### `begin()`

**You** ***shouldn't*** **need to call this method.**<br />
Perform initial hardware setup at start of sketch. In theory, this is all handled automatically, but maybe your use case has a need for this?

#### Syntax

```cpp
begin()
```

#### Parameters
None.

#### Example

```cpp
#include <heltec-eink-modules.h>

// Class is "display model"
QYEG0213RWS800 display(2, 4, 5);

void setup() {

    display.begin();    // Get ready to draw - call once only
    
    display.setCursor(5, 10);
    display.print("Hello, World!");
    
    display.update();   // Display whatever we've drawn

    delay(4000);        // Let user read
    display.clear();    // Wipe the screen immediately
}
```

___
### `bottom()`

Get the bottom edge of the display. Value will change to match the current rotation.

#### Syntax

```cpp
display.bottom()
```

#### Parameters

None.

#### Returns

Position bottom edge of the full display, in pixels.

___
### `centerX()`

Get the horizontal midpoint of the display. If the center is between two pixels, the leftmost is returned. Value will change to match the current rotation.

#### Syntax

```cpp
display.centerX()
```

#### Parameters

None.

#### Returns

Horizontal center of the full display, in pixels.

___
### `centerY()`

Get the vertical midpoint of the display. If the center is between two pixels, the topmost is returned. Value will change to match the current rotation.

#### Syntax

```cpp
display.centerY()
```

#### Parameters

None.

#### Returns

Vertical center of the full display, in pixels.

___
### `clear()`

Clear the display, along with its internal memory. This is a standalone method, called outside of the `DRAW` loop. The display will be cleared to solid white, unless changed using `setBackgroundColor()`.

#### Syntax

```cpp
clear()
```

#### Parameters
None.

#### Example

```cpp
#include <heltec-eink-modules.h>

QYEG0213RWS800 display(2, 4, 5);

void setup() {
    display.clear();    // Display now changes to show solid white
    
    display.setBackgroundColor(BLACK);
    display.clear();    // Display clears instead to solid black
    
    ...

    display.clear();    // Clears again to solid black
}
```

#### See also

* [setBackgroundColor()](#setbackgroundcolor)

___
### `clearMemory()`

**ATmega328P (Uno / Nano): not supported**<br />
**ATmega2560: disabled for some displays** 

Reset the drawing memory to default color, if not using a `DRAW()` loop. Changes are not displayed until `update()` is called.

#### Syntax

```cpp
clearMemory()
```

#### Parameters
None.

#### Example

```cpp
#include <heltec-eink-modules.h>

QYEG0213RWS800 display(2, 4, 5);

void setup() {
    display.clear();    // Whole display immediately changes now to white

    display.setCursor(10, 10);
    display.print("First line.");

    display.update();   // Display now shows "first line"

    display.clearMemory();    // Last drawing cleared from memory; display unchanged
    
    display.setCursor(10, 40);
    display.print("Second line.");
    
    display.update();   // Display now shows "second line", and not "first line"
}

void loop() {}
```

#### See also

* [clear()](#clear)
* [DRAW()](#draw)
* [update()](#update)
* [setBackgroundColor()](#setbackgroundcolor)

___
### `DRAW()`

Performs drawing commands, then updates the display. If necessary, paging is used.

#### Syntax

```cpp
DRAW (display)
```

#### Parameters

* _display_: the display on which to execute the drawing commands.

#### Example

```cpp
#include <heltec-eink-modules.h>

DEPG0150BNS810 display(2, 4, 5);

void setup() {

    DRAW (display) {
        //Graphics commands go here, for example:
        display.fillCircle(50, 100, 20, BLACK);
    }

}
```

#### See also

* [update()](#update)
  
___
### `draw24bitBMP()`

**ATmega328P (Uno / Nano): not supported**<br />
**ATmega2560: disabled for some displays** 

Draw a 24-bit .bmp image, from SD card, at the specified (x,y) position. 
Alpha-mask color can be set, either by [Color](#color) enum, or RGB values.

#### Syntax

``` cpp
display.draw24bitBMP(left, top, filename)
display.draw24bitBMP(left, top, filename, mask)
display.draw24bitBMP(left, top, filename, mask_r, mask_g, mask_b)

```

#### Parameters

* _left_:   Top left corner x coordinate
* _top_:   Top left corner y coordinate
* _filename_:  filename of the .bmp image on SD card
* _mask_ (optional): Color to draw transparent
* _mask_r_ (optional): Color to draw transparent - Red channel
* _mask_g_ (optional): Color to draw transparent - Green channel
* _mask_b_ (optional): Color to draw transparent - Blue channel

#### See also

* [colors](#colors)
* [drawXbitmap()](#drawxbitmap)
* [SD card](/docs/SD/sd.md)

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
* _corner\_mask_: Which corner(s) to draw. Select by setting the first four bits: Least Significant Bit for top left, traveling clockwise as bit # increases.
* _color_: Color to draw with 

#### Example

```cpp
#include <heltec-eink-modules.h>

DEPG0150BNS810 display(2, 4, 5);

void setup() {
    byte corners = 0;
    
    bool TOP_LEFT = false;
    bool TOP_RIGHT = true;
    bool BOTTOM_RIGHT = false;
    bool BOTTOM_LEFT = true;

    corners = (TOP_LEFT << 0) | (TOP_RIGHT << 1) | (BOTTOM_RIGHT << 2) | (BOTTOM_LEFT << 3);

    // Or alternatively..
    // corners = B1010;

    DRAW (display) {
        display.drawCircleHelper(50, 50, 50, corners, BLACK);
    }

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
### `drawMonoBMP()`

Draw a 1-bit .bmp image, from SD card, at the specified (x,y) position, using the specified foreground color. 
Unset bits are transparent by default, unless argument `bg` is passed.

#### Syntax

``` cpp
display.drawMonoBMP(left, top, filename, color)
display.drawMonoBMP(left, top, filename, color, bg)
```

#### Parameters

* _left_:   Top left corner x coordinate
* _top_:   Top left corner y coordinate
* _filename_:  filename of the .bmp image on SD card
* _color_: Color to draw pixels with
* _bg_: Color to draw background with

#### See also

* [colors](#colors)
* [drawXbitmap()](#drawxbitmap)
* [SD card](/docs/SD/sd.md)

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

* [fillTriangle()](#filltriangle)
* [colors](#colors)

___
### `drawXBitmap()`

Draw PROGMEM-resident XBitMap Files (*.xbm), exported from GIMP. See [tutorial on preparing XBitmap images](XBitmapTutorial/README.md).

*This is an AdafruitGFX method*

#### Syntax

```cpp
display.drawXBitmap( x, y, bitmap[], w, h, color)
```

#### Parameters

* _x_: Top left corner x coordinate
* _y_:   Top left corner y coordinate
* _bitmap_: byte array with monochrome bitmap (PROGMEM only)
* _w_: Width of bitmap in pixels
* _h_: Height of bitmap in pixels
* _color_: Color to draw pixels with

#### Example

```cpp
#include <heltec-eink-modules.h>
#include "chess_200x200.h"

DEPG0150BNS810 display(2, 4, 5);

void setup() {

    // Don't forget to set the rotation, so your image fits how you intended
    display.setRotation(PINS_LEFT);  

    DRAW (display) {
        display.drawXBitmap(0, 0, chess_bits, chess_width, chess_height, BLACK);
    }

}

void loop() {}
```

#### See also

* [drawBitmap()](#drawbitmap)
* [colors](#colors)

___
### `customPowerOff()`

Disconnect power from the display, using an external power switch, such as a transistor.

Must be configured with `useCustomPowerSwitch()`.

#### Syntax

```cpp
display.customPowerOff()
```

___
### `customPowerOn()`

Connect power to the display, using an external power switch, such as a transistor.

Must be configured with `useCustomPowerSwitch()`.

#### Syntax

```cpp
display.customPowerOn()
```

___
### `fastmodeOff()`

Disable fastmode, return to normal ("full refresh").

#### Syntax
```cpp
display.fastmodeOff()
```

#### Parameters

None.

#### Example

```cpp
#include <heltec-eink-modules.h>

DEPG0150BNS810 display(2, 4, 5);

void setup() {
    display.clear();

    // Begin fastmode
    display.fastmodeOn();

    DRAW (display) {
        display.setCursor(10, 10);
        display.print("ON");
    }
    delay(2000);

    DRAW (display) {
        display.setCursor(10, 10);
        display.print("still ON");
    }
    delay(2000);

    // Back to normal drawing
    display.fastmodeOff();

    display.setWindow(0, 40, 100, 100);

    DRAW (display) {
        display.setCursor(10, 40);
        display.print("OFF now..");
    }

}
```

___
### `fastmodeOn()`

Enable fastmode.

Some displays have a second mode, where the image updates much faster. This is known officially as a *"Partial Refresh"*. For the sake of user-friendliness, this library uses the term *"Fast Mode*".

The trade-off is that images drawn in fast mode are of a lower quality. The process may also be particularly difficult on the hardware. **Use sparingly.**

Not all displays support fast mode.

#### Syntax

```cpp
display.fastmodeOn()
display.fastmodeOn(clear_if_reset)
```

#### Parameters

* _clear\_if\_reset_ (optional): Pass false to use the display memory "as-is". Useful after a processor deep sleep. If you intend to use fast-mode, make sure to at least run a normal refresh (or `clear()` / `clearMemory()`) on initial boot. Otherwise, you'll get a whole lot of static.

#### Example

```cpp
#include <heltec-eink-modules.h>

DEPG0150BNS810 display(2, 4, 5);

void setup() {
    display.clear();

    // Begin fastmode
    display.fastmodeOn();

    DRAW (display) {
        display.setCursor(10, 10);
        display.print("ON");
    }
    delay(2000);

    DRAW (display) {
        display.setCursor(10, 10);
        display.print("still ON");
    }
    delay(2000);

    // Back to normal drawing
    display.fastmodeOff();

    display.setWindow(0, 40, 100, 100);

    DRAW (display) {
        display.setCursor(10, 40);
        display.print("OFF now..");
    }

}

void loop() {}
```

#### See also

* [clear()](#clearlear)
* [clearMemory()](#clearmemory)

___
### `fastmodeTurbo()`

A variation of `fastmodeOn().` *Use with caution*

Slightly faster refresh times, particularly with lower-spec microcontrollers. Slightly lower image quality.

**Note**: To prevent changes to your previous image, before calling `setWindow()`, `setRotation()`, or `setFlip()`, you must draw the same identical image, **twice**.

This is a quirk of the display controller IC.

#### Syntax

```cpp
display.fastmodeTurbo()
display.fastmodeTurbo(clear_if_reset)
```

#### Parameters

* _clear\_if\_reset_ (optional): Pass false to use the display memory "as-is". Useful after a processor deep sleep. If you intend to use fast-mode, make sure to at least run a normal refresh (or `clear()` / `clearMemory()`) on initial boot. Otherwise, you'll get a whole lot of static.

#### Example

```cpp
void setup() {
    display.clear();

    // Fastmode turbo
    display.fastmodeTurbo();

    // Print "Turbo Test"
    DRAW (display) {
        display.setCursor(10, 10);
        display.print("Turbo Test");
    }
    delay(2000);

    // Print twice: "Double writing..""
    for(int i=0; i < 2; i++) {
        DRAW (display) {
            display.setCursor(10, 10);
            display.print("Double writing..");
        }
    }
    delay(2000);

    // Move window
    display.setWindow(0, 40, 100, 100);
    display.setBackgroundColor(BLACK);
    display.setTextColor(WHITE);

    // Print "Old image OK", in window
    DRAW (display) {
        display.setCursor(5, 45);
        display.println("Old image OK");
    }

}
```

#### See also

* [clear()](#clearlear)
* [clearMemory()](#clearmemory)

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

Fill the screen completely with one color. **Inefficient, consider instead `setBackgroundColor()`**

*This is an AdafruitGFX method*

#### Syntax

```cpp
display.fillScreen(color)
```

#### Parameters

* _color_: Color to draw with

#### See also

* [setBackgroundColor](#setbackgroundcolor)
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
### `fullscreen()`

Draw to the entire screen, rather than just a particular part. Undoes the `setWindow()` method. Call before the `DRAW` loop.

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
### `fullscreenBMPValid()`

Check if file is a valid fullscreen .bmp image for this display.

#### Syntax

```cpp
display.fullscreenBMPValid(filename)
display.fullscreenBMPValid(prefix, number)
display.fullscreenBMPValid(filename, purge)
display.fullscreenBMPValid(prefix, number, purge)
```

#### Parameters

* _filename_: canvas file to check
* _prefix_: identifies different sets of images
* _number_: image's location in the set
* _purge_ (optional): when purge = true, canvas will be deleted from SD card, if detected as invalid. 

#### Returns

`true` if canvas is valid for this display.
`false` if invalid, wrong display, or doesn't exist.

#### See also

* [SD card](/docs/SD/sd.md)

___
### `getBMPHeight()`

Gets height of a .bmp image stored on SD card.

#### Syntax

```cpp
display.getBMPHeight(filename)
```

#### Parameters

* _filename_: the name of the image to read, on SD card

#### Returns

The height of the image.

#### See also

* [getBMPWidth()](#getbmpwidth)
* [SD card](/docs/SD/sd.md)

___
### `getBMPWidth()`

Gets width of a .bmp image stored on SD card.

#### Syntax

```cpp
display.getBMPWidth(filename)
```

#### Parameters

* _filename_: the name of the image to read, on SD card

#### Returns

The width of the image.

#### See also

* [getBMPHeight()](#getbmpheight)
* [SD card](/docs/SD/sd.md)

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
* [Rotation](#rotation)

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

### `getTextCenterX()`

Gets the required cursor x position to horizontally center text.

#### Syntax

```cpp
display.getTextCenterX(text)
```

#### Parameters

* _text_: the string to use for dimensioning, as a char array or char pointer

#### Returns

X value for use with [setCursor()](#setcursor)

#### Example

```cpp
#include <heltec-eink-modules.h>

DEPG0150BNS810 display(2, 4, 5);

void setup() {

    const char text[] = "Hello!";

    int x = display.getTextCenterX(text);   // Horizontal
    int y = display.getTextCenterY(text);   // Vertical

    DRAW (display) {
        display.setCursor(x, y);
        display.print(text);
    }
    
}

void loop() {}
```

#### See also

* [getTextCenterY()](#gettextcentery)

___

### `getTextCenterY()`

Gets the required cursor y position to vertically center text.

#### Syntax

```cpp
display.getTextCenterY(text)
```

#### Parameters

* _text_: the string to use for dimensioning, as a char array or char pointer

#### Returns

Y value for use with [setCursor()](#setcursor)

#### Example

```cpp
#include <heltec-eink-modules.h>

DEPG0150BNS810 display(2, 4, 5);

void setup() {

    const char text[] = "Hello!";

    int x = display.getTextCenterX(text);   // Horizontal
    int y = display.getTextCenterY(text);   // Vertical

    DRAW (display) {
        display.setCursor(x, y);
        display.print(text);
    }
    
}

void loop() {}
```

#### See also

* [getTextCenterX()](#gettextcenterx)

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
### `height()`

Get the height of the display. A display with height 200 will have a top edge of 0, and a bottom edge of 199. Value will change to match the current rotation.

#### Syntax

```cpp
display.height()
```

#### Parameters

None.

#### Returns

Height of the full display, in pixels.

___
### `landscape()`

Alias for `setRotation(3)`. Enters a landscape orientation. 
270 degrees rotation is used because it is the physical orientation of the display on Wireless Paper all-in-one boards.

#### See also

* [portrait()](#portrait)
* [setRotation()](#setrotation)

___
### `left()`

Get the left edge of the display. This will always be zero, but is included for completeness.

#### Syntax

```cpp
display.left()
```

#### Parameters

None.

#### Returns

Position of the left edge of the full display, in pixels.

___
### `loadFullscreenBMP()`

Load a fullscreen .bmp, from SD card to display, in one pass. Can be loaded by filename, or using a prefix and numeric identifier, if convenient.

Accepts only a specific type of .bmp image.
* 24bit .bmp file
* Portrait, not landscape
* Dimensions: full screen width x height

#### Syntax

```cpp
display.loadFullscreenBMP(filename)
display.loadFullscreenBMP(prefix, number)
```

#### Parameters

* _filename_: fullscreen .bmp file to load
* _prefix_: identifies different sets of images
* _number_: image's location in the set

#### See also

* [SAVE_TO_SD()](#SAVE_TO_SD)
* [SD card](/docs/SD/sd.md)

___
### `print()`

Draw text to screen, at position of `setCursor()`.

#### Syntax

```cpp
print(text)
```

#### Parameters

* _text_: printable to draw to screen

#### See also

* [println](#println)
* [setCursor()](#setcursor)
* [setFont()](#setfont)
* [setTextColor()](#settextcolor)

___
### `printCenter()`

Center text on-screen, with optional x and y offset.

#### Syntax

```cpp
printCenter(str, offset_x, offset_y)
printCenter(int, offset_x, offset_y)
printCenter(float, decimal_places, offset_x, offset_y)
printCenter(double, decimal_places, offset_x, offset_y)
```

#### Parameters

* _str_: text to draw to screen (C-String or Arduino String)
* _int_: integer value to draw to screen
* _float_: float value to draw to screen
* _double_: double value to draw to screen
* _offset\_x_: (optional) offset left(negative) or right(positive) of center, in pixels. Default 0
* _offset\_y_: (optional) offset above (negative) or below(positive) of center, in pixels. Default 0
* _decimal\_places_: (optional) with double or float values, how many decimal places should be printed. Default 2

___
### `println()`

Draw text to screen, followed by a newline, at position of `setCursor()`.

#### Syntax

```cpp
println(text)
```

#### Parameters

* _text_: printable to draw to screen

#### See also

* [setCursor()](#setcursor)
* [setFont()](#setfont)
* [setTextColor()](#settextcolor)

___
### `portrait()`

Alias for `setRotation(0)`. Enters a portrait orientation. 

#### See also

* [landscape()](#landscape)
* [setRotation()](#setrotation)

___
### `right()`

Get the right edge of the display. Value will change to match the current rotation.

#### Syntax

```cpp
display.right()
```

#### Parameters

None.

#### Returns

Position of the right edge of the full display, in pixels.

___
### `SAVE_TO_SD()`

Performs drawing commands, outputting to SD card, instead of display. If necessary, paging is used. 

Output filename can be specified, or instead a prefix and numeric identifier can be given, which will be used to generate a unique filename. The prefix has a maximum length of 6 characters.

#### *On Arduino Uno:* 
* this feature is disabled by default, to minimize sketch size. See [optimization.h](/src/optimization.h)
* feature interferes with Serial. The [`MinimalSerial`](/docs/SD/MinimalSerial.md) class provided by SdFat should be used instead
#### Syntax

```cpp
SAVE_TO_SD (display, filename)
SAVE_TO_SD (display, prefix, number)
```

#### Parameters

* _display_: display for which the saved image is suitable
* _filename_: save canvas on SD card with this filename
* _prefix_: identifies different sets of images
* _number_: image's location in the set

#### Example

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

#### See also

* [update()](#update)

___
### `saveToSD()`

**ATmega328P (Uno / Nano): not supported**<br />
**ATmega2560: disabled for some displays** 

Draw a canvas image to SD card, outside of a `SAVE_TO_SD` loop, on-top of any existing screen data. 

Output filename can be specified, or instead a prefix and numeric identifier can be given, which will be used to generate a unique filename. The prefix has a maximum length of 6 characters.

#### Syntax

```cpp
display.saveToSD(filename)
display.saveToSD(prefix, number)
```

#### Parameters

* _filename_: save canvas on SD card with this filename
* _prefix_: identifies different sets of images
* _number_: image's location in the set

#### Example

```cpp
#include <heltec-eink-modules.h>

DEPG0150BNS810 display(2, 4, 5);

void setup() {

    display.setCursor(10, 10);
    display.print("Example");

    // Save by filename
    display.saveToSD("canvas01.bmp");   // Result of first two commands saved to SD

    // Or: save by prefix + identifier
    display.saveToSD("canvas", 1);
}
```

#### See also

* [SD card](/docs/SD/sd.md)

___
### `SDCardFound()`

Check if SD card is connected and accessible.

#### Syntax

```cpp
display.SDCardFound()
```

#### Parameters

None.

#### Returns

`true` if card is accessible.
`false` if there is an error.

#### See also

* [SD card](/docs/SD/sd.md)

___
### `SDFileExists()`

Check if an image exists on SD card.

#### Syntax

```cpp
display.SDFileExits(filename)
display.SDFileExits(prefix, number)
```

#### Parameters

* _filename_: image file
* _prefix_: identifies different sets of images
* _number_: image's location in the set

#### Returns

`true` if exists.
`false` if not found.

#### See also

* [SD card](/docs/SD/sd.md)

___
### `setBackgroundColor()`

Sets the background color to be used for future display updates. All graphics operations are drawn on top of this background color. Also determines the color which is set during the standalone `clear()` method.

Default value is `WHITE`

#### Syntax

```cpp
display.setBackgroundColor(bgcolor)
```

#### Parameters

* _bgcolor_: color to set as background

#### Example

```cpp
#include <heltec-eink-modules.h>

QYEG0213RWS800 display(2, 4, 5);

void setup() {
    display.clear();    // Display now changes to show solid white
    
    display.setBackgroundColor(BLACK);
    display.clear();    // Display clears instead to solid black
    
    ...

    display.clear();    // Clears again to solid black
}
```
#### See also

* [colors](#colors)

___
### `setCursor()`

Set text cursor location. *Make sure to use inside the `DRAW()` loop*.

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
### `setFont()`

Set the font to display when print()ing, either custom or default. Several fonts are included with this library, in the [Fonts folder](/src/Fonts/). Fonts can take up a bit of memory, so don't #include too many!

*This is an AdafruitGFX method*

#### Syntax

```cpp
display.setFont(f)
```

#### Parameters

* _f_: (address of) The GFXfont object, if NULL use built in 6x8 font.

#### Example

```cpp
#include <heltec-eink-modules.h>
#include "Fonts/FreeSerifBold12pt7b.h"

DEPG0150BNS810 display(2, 4, 5);

void setup() {
    // Pass (the address of) the font to the library
    display.setFont( &FreeSerifBold12pt7b );   

    DRAW (display) {
        // Set the (word-processor-like) cursor to the arbitrary position of x=10, y=50
        display.setCursor(10, 50);                      
        display.print("example");
    }

}

void loop() {}
```

___
### `setFlip()`

Reverse the image, either horizontally, or vertically.

Flip can be applied in the context of the window, or the whole screen. Flip is applied relative to the current rotation.

Because of a hardware limitation, window width (or height, if you are using a landscape rotation) is always a multiple of 8. Be aware that this may affect window dimensions when drawing flipped. If you are using a window, your window's width will be automatically rounded up to the nearest multiple. For your convenience, these new "rounded up" dimensions are available through the `.window` feature. In this way, you can draw your graphics to cover the slightly expanded window, and work around the limitation. Note that the window will never "round down"; your originally requested region will always fit within the window provided.

#### Syntax

```cpp
setFlip(axis)
```

#### Parameters

* _axis_: which way to flip the image. <br /> 
    Supported values:
    * `OFF`
    * `HORIZONTAL`
    * `VERTICAL`
    * `HORIZONTAL_WINDOW`
    * `VERTICAL_WINDOW`

#### Example

```cpp
#include <heltec-eink-modules.h>

DEPG0150BNS810 display(2, 4, 5);

void setup() {

    // Flip horizontally
    display.setFlip( HORIZONTAL );
    
    DRAW (display) {
        display.setCursor(10, 10);
        display.print("Mirrored Text");
    }
}
```

#### See also

* [setRotation()](#setrotation)

___
### `setRotation()`

Rotate future drawing operations by a multiple of 90 degrees.  

Because of a hardware limitation, window width (or height, if you are using a landscape rotation) is always a multiple of 8. If you are using a window, your window's width will be automatically rounded up to the nearest multiple. For your convenience, these new "rounded up" dimensions are available through the `.window` feature. In this way, you can draw your graphics to cover the slightly expanded window, and work around the limitation. Note that the window will never "round down"; your originally requested region will always fit within the window provided.

#### Syntax

```cpp
setRotation(rotation)
```

#### Parameters

* _rotation_: clockwise rotation:<br /> 
    * 0, 90, 180, 270 (degrees), negative allowed
    * in 90 degree increments (1 = 90&deg;, 2=180&deg; etc), negative allowed <br />
    * relative to "display module" header pins:
      * `PINS_ABOVE` &nbsp;(0&deg;)
      * `PINS_LEFT` &nbsp;(90&deg;)
      * `PINS_BELOW` &nbsp;(180&deg;)
      * `PINS_RIGHT` &nbsp;(270&deg;)
    * relative to "Wireless Paper" boards' USB connector:
      * `USB_ABOVE` &nbsp;(0&deg;)
      * `USB_LEFT` &nbsp;(90&deg;)
      * `USB_BELOW` &nbsp;(180&deg;)
      * `USB_RIGHT` &nbsp;(270&deg;)

#### Example

```cpp
#include <heltec-eink-modules.h>

DEPG0150BNS810 display(2, 4, 5);

void setup() {

    // Set the rotation before
    display.setRotation( PINS_BELOW );
    DRAW (display) {
        display.setCursor(10, 10);
        display.print("Upside Down");
    }

    delay(2000);    // Pause to view the image

    // Set the rotation during
    DRAW (display) {
        display.setCursor(10, 10);
        display.setRotation(0);     // No rotation
        display.print("top");

        display.setCursor(10, 10);
        display.setRotation(1);     // 1 * 90deg rotation
        display.print("left");

        display.setCursor(10, 10);
        display.setRotation( PINS_BELOW );  // 2 * 90deg rotation. (display's pins are now below the screen)
        display.print("bottom");
    }

}

void loop() {}
```
#### See also

* [Rotation](#rotation)

___
### `setTextColor()`

Set text font color, with or without a background

*This is an AdafruitGFX method*

Note from Adafruit:
```cpp
// NOTE: THERE IS NO 'BACKGROUND' COLOR OPTION ON CUSTOM FONTS.
// THIS IS ON PURPOSE AND BY DESIGN.  The background color feature
// has typically been used with the 'classic' font to overwrite old
// screen contents with new data.  This ONLY works because the
// characters are a uniform size; it's not a sensible thing to do with
// proportionally-spaced fonts with glyphs of varying sizes (and that
// may overlap).
```

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
### `setWindow()`
Draw to only a particular part of the screen ("a window"), leaving the remainder unchanged. Call before the `DRAW()` loop. 

Window parameters are interpreted in the context of the current rotation and flip.

Because of a hardware limitation, window width (or height, if you are using a landscape rotation) is always a multiple of 8. Any value given will be automatically rounded up to the nearest multiple. For your convenience, these new "rounded up" dimensions are available through the `.window` feature. In this way, you can draw your graphics to cover the slightly expanded window, and work around the limitation. Note that the window will never "round down"; your originally requested region will always fit within the window provided.

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

QYEG0213RWS800 display(2, 4, 5);

void setup() {
    display.clear();    // Fill screen with white

    display.setWindow(0, 1, 8, 3);                      // Set the window dimensions
    display.setBackgroundColor(BLACK);      // Use black as our background color

    DRAW (display) {
        // Not actually doing anything
        // Just drawing the black background
        // (For the example)
    }
}

/* The result:

    0   1   2   3   4   5   6   7   8   
0   
1   #   #   #   #   #   #   #   #
2   #   #   #   #   #   #   #   #
3   #   #   #   #   #   #   #   #
4

*/
```
#### See also

* [fullscreen()](#fullscreen)
* [setRotation()](#setrotation)
* [setFlip()](#setflip)

___
### `top()`

Get the top edge of the display. This will always be zero, but is included for completeness.

#### Syntax

```cpp
display.top()
```

#### Parameters

None.

#### Returns

Position of the top edge of the full display, in pixels.

___
### `update()`

**ATmega328P (Uno / Nano): not supported**<br />
**ATmega2560: disabled for some displays** 

Execute drawing commands outside of a `DRAW` loop, drawing on-top of the existing screen data.

#### Syntax

```cpp
display.update()
```

#### Parameters

None.

#### Example

```cpp
#include <heltec-eink-modules.h>

DEPG0150BNS810 display(2, 4, 5);

void setup() {

    display.setCursor(10, 10);
    display.print("Example");

    display.update();   // Image on display changes with this command
}
```

#### See also

* [DRAW()](#draw)
* [clearMemory()](#clearmemory)

___
### `useCustomPowerSwitch()`

Configure the display to use an external power switch, such as a transistor, for power-saving. When requested, the library will configure the display appropriately, and then set the specified switch pin.

#### Syntax

```cpp
display.useCustomPowerSwitch(pin, type)
```

#### Parameters

* _pin_: pin connected to base of a transistor, or other low current switching device.
* _type_: type of signal to output on pin<br />
    Supported values:<br />
    * `NPN`
    * `PNP`
    * `ACTIVE_HIGH`
    * `ACTIVE_LOW`

___
### `useSD()`

Configure the library to use an SD card - SPI adapter. Must be called before and SD code is used.

#### Syntax

```cpp
display.useSD(cs_pin)
display.useSD(cs_pin, miso_pin) // ESP32 or SAMD21G18A only
```

#### Parameters

* _cs_pin_: pin connected to the CS pin of the SD card adapter
* _miso_pin_: custom pin for the MISO connection of the the SD card adapter 

#### See also

* [SD card](/docs/SD/sd.md)

___
### `width()`

Get the width of the display. A display with width 200 will have a left edge of 0, and a right edge of 199. Value will change to match the current rotation.

#### Syntax

```cpp
display.width()
```

#### Parameters

None.

#### Returns

Width of the full display, in pixels.

___
### `window.left()`

Get the left edge of the current window, after it has been expanded to meet hardware requirements. Value will change to match the current rotation.

#### Syntax

```cpp
display.window.left()
```

#### Parameters

None.

#### Returns

Position of the left edge of the current window, in pixels.

___
### `window.top()`

Get the top edge of the current window, after it has been expanded to meet hardware requirements. Value will change to match the current rotation.

#### Syntax

```cpp
display.window.top()
```

#### Parameters

None.

#### Returns

Position of the top edge of the current window, in pixels.

___
### `window.right()`

Get the right edge of the current window, after it has been expanded to meet hardware requirements. Value will change to match the current rotation.

#### Syntax

```cpp
display.window.right()
```

#### Parameters

None.

#### Returns

Position of the right edge of the current window, in pixels.

___
### `window.bottom()`

Get the bottom edge of the current window, after it has been expanded to meet hardware requirements. Value will change to match the current rotation.

#### Syntax

```cpp
display.window.bottom()
```

#### Parameters

None.

#### Returns

Position bottom edge of the current window, in pixels.

___
### `window.width()`

Get the width of the current window. A window with a left edge of 0, and a right edge of 7, would have a width of 8. Value will change to match the current rotation.

#### Syntax

```cpp
display.window.width()
```

#### Parameters

None.

#### Returns

Width of the current window, in pixels.

___
### `window.height()`

Get the height of the current window. A window with a top edge of 0, and a bottom edge of 7, would have a height of 8. Value will change to match the current rotation.

#### Syntax

```cpp
display.window.height()
```

#### Parameters

None.

#### Returns

Height of the current window, in pixels.

___
### `window.centerX()`

Get the horizontal midpoint of the current window. If the center is between two pixels, the leftmost is returned. Value will change to match the current rotation.

#### Syntax

```cpp
display.window.centerX()
```

#### Parameters

None.

#### Returns

Horizontal center of the current window, in pixels.

___
### `window.centerY()`

Get the vertical midpoint of the current window. If the center is between two pixels, the topmost is returned. Value will change to match the current rotation.

#### Syntax

```cpp
display.window.centerY()
```

#### Parameters

None.

#### Returns
Vertical center of the current window, in pixels.

## Constants

This section describes the various constants (as *enumerations*), which are accepted as parameters by various methods throughout the library.

### `Color`

#### Values

* `WHITE`
* `BLACK`
* `RED` - Supported displays only

#### Example

```cpp
display.setBackgroundColor( BLACK )
```

___
### `Flip`

Specify along which axis the screen should be flipped (mirrored)

#### Values

* `NONE`
* `HORIZONTAL`
* `VERTICAL`
* `HORIZONTAL_WINDOW`
* `VERTICAL_WINDOW`

#### Example

```cpp
display.setFlip( HORIZONTAL )
```

___
### `Rotation`

A convenient shortcut for getting the correct display rotation. Describes the desired rotation in relation to the header pins on the module.

#### Values

* `PINS_ABOVE`
* `PINS_LEFT`
* `PINS_BELOW`
* `PINS_RIGHT`

#### Example

```cpp
display.setRotation( PINS_LEFT )
```

___
### `SwitchType`

Values passed to `useCustomPowerSwitch()`, to specify the type of external switch in user's custom power control circuit.

#### Values

* `NPN`
* `PNP`
* `ACTIVE_HIGH`
* `ACTIVE_LOW`

#### See also

* [useCustomPowerSwitch()](#useCustomPowerSwitch)