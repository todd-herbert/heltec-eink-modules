
# Preparing Mono XBitmaps for E-INK
1. [Install GIMP](#install-gimp)
2. [Resize Image](#resize-image)
3. [Indexed Color](#change-to-indexed-color-mode)
4. [Export](#export-as-xbitmap)
5. [Import & Modify](#importing-and-modifying)
6. [Drawing the Xbitmap](#drawing-the-xbitmap)
## Install GIMP
GIMP (GNU Image Manipulation Program) is a free and powerful image editor that is capable of exporting XBitmap images.
If you haven't already done so, head over to https://www.gimp.org/ and download it now.

## Open Image in GIMP
You can go ahead and open your source image in GIMP. 
When selecting an image, it pays to remember the limations of E-INK displays. Pixels are either ON or OFF, there is no inbetween.

In this tutorial I will be using [this image](https://commons.wikimedia.org/wiki/File:Black_and_White_Chessboard.jpg) from Wikimedia Commons.

![tutorial image source](https://github.com/todd-herbert/Heltec-213R-V2/blob/main/docs/XBitmapTutorial/source.png?raw=true)
## Resize Image
Your image can be either fullscreen on cover just a small part; the process is the same.
Keeping the dimensions of your display in mind, it is now time to resize your image.

In this tutorial, I am using a Heltec 2.13" Red V2 Display, which has a size of 122px x 250px. 

Use the *Image* -> *Scale Image* dialog in GIMP to achieve an appropriate size.
![scale](https://github.com/todd-herbert/Heltec-213R-V2/blob/main/docs/XBitmapTutorial/scale.png?raw=true)

Note that the new dimensions of 250x141 are still too large for my 250x122 display, so I will now crop the image using the *Image* -> *Canvas Size* dialog.

![scale](https://github.com/todd-herbert/Heltec-213R-V2/blob/main/docs/XBitmapTutorial/crop.png?raw=true)

Entering the desired height, and then pushing *Center* will give the right dimensions for the crop operation.

## Change to "Indexed Color Mode"
By changing to *Indexed Color Mode*, we are reducing the entire image down to a small set of states for each pixel. In this case, *Black* or *White*.

After zooming in, to get a better look at the image, open the *Indexed Color Conversion* dialog by selecting *Image*-> *Mode* -> *Indexed..*
![scale](https://github.com/todd-herbert/Heltec-213R-V2/blob/main/docs/XBitmapTutorial/index.png?raw=true)

You can then select "Use black and white (1-bit) palette".

An important option to explore here is *Dithering*.
This setting controls how shades of gray will be converted into the the all black / all white values of the E-Ink display. Different settings will suit different images

This table shows the different possible outcomes:
Dithering Style | Result
----------------|-------
None                     | <img src="https://github.com/todd-herbert/Heltec-213R-V2/blob/main/docs/XBitmapTutorial/DitheringExamples/NoDither.jpg?raw=true" width="250">
Floyd-Steinberg (normal) |  <img src="https://github.com/todd-herbert/Heltec-213R-V2/blob/main/docs/XBitmapTutorial/DitheringExamples/FSNormal.jpg?raw=true" width="250">
Floyd-Steinberg (reduced color bleeding) | <img src="https://github.com/todd-herbert/Heltec-213R-V2/blob/main/docs/XBitmapTutorial/DitheringExamples/FSReduced.jpg?raw=true" width="250">
Positioned | <img src="https://github.com/todd-herbert/Heltec-213R-V2/blob/main/docs/XBitmapTutorial/DitheringExamples/Positioned.jpg?raw=true" width="250">

For this image, I think that the *"Floyd-Steinberd (reduced color bleeding)"* option probably looks best.

## Export as XBitmap

Open the Export dialog by selecting *File* -> *Export As...*
To save as an XBitmap image, enter a filename with the `.xbm` extension. 

Be aware that the name you choose here will determine the name of the image in the code later on. I am saving the example image as `chess.xbm`

After pressing *Export*, another "Export Image as XBM" dialog will appear. No changes are needed here, and you can click *Export* to continue.

![export dialog](https://github.com/todd-herbert/Heltec-213R-V2/blob/main/docs/XBitmapTutorial/export.png?raw=true)
## Importing and Modifying
The XBitmap format only needs slight modification to be used with Adafruit_GFX.

1. The `.xbm`  extension needs to be changed to `.h`
(Note: this step is not required if you are using an alternative Arduino IDE such as vs-code).
Place the XBitmap file (now with `.h` ending) in the same directory as your .ino file and it should appear in the Arduino IDE.

2. Inside this `.h`  file, the data type of the *"image bits array"* needs to be changed. Add `PROGMEM const` before the `static unsigned char xxxx_bits[] = {` part.
 This step specifies that the XBitmap data must be stored in the flash memory space, not in the valuable SRAM space. This is a requirement of the drawXBitmap() method.

## Drawing the XBitmap
You can now import your xbitmap file as a header
```c++
#include "chess.h"
```
Whenever your are ready, you can draw it with the drawXBitmap() method.

Here, we are drawing from the top left corner (0,0), with the width and height that are automatically set in our XBM .h file
```c++
panel.fillScreen(panel.WHITE);
panel.drawXBitmap(0, 0, chess_bits, chess_width, chess_height, panel.BLACK);
```
![mono-result](https://github.com/todd-herbert/Heltec-213R-V2/blob/main/docs/XBitmapTutorial/MonoResult.png?raw=true)

Note: This image data doesn't necessarily have to be written as black data on white background; any color supported by the display will work.
