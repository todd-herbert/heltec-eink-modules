
# Preparing 3-Color XBitmaps for E-INK
1. [Install GIMP](#install-gimp)
2. [Resize Image](#resize-image)
3. [Define Color Palette](#define-a-color-palette)
4. [Indexed Color](#change-to-indexed-color-mode)
5. [Isolate Colors](#isolating-colors)
6. [Export](#export-as-xbitmap)
7. [Repeat](#rinse-and-repeat)
8. [Import & Modify](#importing-and-modifying)
9. [Drawing the Xbitmaps](#drawing-the-xbitmaps)
## Install GIMP
GIMP (GNU Image Manipulation Program) is a free and powerful image editor that is capable of exporting XBitmap images.
If you haven't already done so, head over to https://www.gimp.org/ and download it now.

## Open Image in GIMP
You can go ahead and open your source image in GIMP. 

When selecting an image, it pays to remember the limations of E-INK displays. Pixels are either ON or OFF, there is no inbetween.  

In this tutorial, I am using a *Heltec 2.13" Red V2 Display*, which has a size of 122px x 250px and 3 Colors: White, Black, and Red. From this point I will talk about these colors, but the process is the same if your display is yellow, or any other color.

In this tutorial I will be using [this image](https://pixabay.com/photos/macaw-parrot-bird-fly-wings-209128/) from pixabay.

![tutorial image source](https://github.com/todd-herbert/Heltec-213R-V2/blob/main/docs/XBitmapTutorial/3C_source.png?raw=true)
## Resize Image
Your image can be either fullscreen on cover just a small part; the process is the same.

Purely for design purposes, I am cropping the most interesting part of my tutorial image with *Image* -> *Crop to Selection*

Keeping the dimensions of your display in mind, it is now time to resize your image. 
* Use the *Image* -> *Scale Image* dialog in GIMP to achieve an appropriate size.

![scale](https://github.com/todd-herbert/Heltec-213R-V2/blob/main/docs/XBitmapTutorial/3C_scale.png?raw=true)

Note that the new dimensions of 250x157 are still too large for my 250x122 display, so I will now crop the image using the *Image* -> *Canvas Size* dialog.

![scale](https://github.com/todd-herbert/Heltec-213R-V2/blob/main/docs/XBitmapTutorial/3C_crop.png?raw=true)  
Entering the desired height, and then pushing *Center* will give the right dimensions for the crop operation.

## Define a Color Palette
*GIMP will remember your palette, so you will be able to skip this step after your first image.*

The *Color Palette* is a list of colors available for an image to use. We can set the colors we have available, and let GIMP figure out the best way to display our image with them.

As my display has white, black, and red, I will be creating a palette with these three colors.

* Open the *Palettes Dialog* by selecting *Windows* -> *Dockable Dialogs* ->  *Palettes*

The dockable *Palette Dialog* will appear in the top right corner of the screen.
* At the bottom of the Palette Dialog, click the icon for *"Create a New Palette"*, as indicated in the image below.

![](https://github.com/todd-herbert/Heltec-213R-V2/blob/main/docs/XBitmapTutorial/3C_palette_dialog.png?raw=true)

The Palette editor will appear in the same location

* Give the palette a name so you can find it later
In this tutorial it is named "WBR", for "White Black Red"

* Click three times on the Icon for "Create a New Entry"
Three small squares should appear, in the editor, alongside some blank black space

* For each entry we created, double click the square that appeared and set its color.

![](https://github.com/todd-herbert/Heltec-213R-V2/blob/main/docs/XBitmapTutorial/3C_edit_palette.png?raw=true)


## Change to "Indexed Color Mode"
By changing to *Indexed Color Mode*, we are reducing the entire image down to just the small set of states we defined in our *Color Palette*.
* Open the *Indexed Color Conversion* dialog by selecting *Image*-> *Mode* -> *Indexed..*

* Select "*Use custom palette*"
* Selecting the small icon next to the text field, scroll through the list of available palettes until you find the one we just created, then select it.
 
![](https://github.com/todd-herbert/Heltec-213R-V2/blob/main/docs/XBitmapTutorial/3C_index.png?raw=true)

An important option to explore here is *Dithering*.
This setting controls how shades of colors will be converted into the the fixed values of our palette. Different settings will suit different images


Dithering Style | Example
----------------|-------
None                     | <img src="https://github.com/todd-herbert/Heltec-213R-V2/blob/main/docs/XBitmapTutorial/DitheringExamples/NoDither.jpg?raw=true" width="250">
Floyd-Steinberg (normal) |  <img src="https://github.com/todd-herbert/Heltec-213R-V2/blob/main/docs/XBitmapTutorial/DitheringExamples/FSNormal.jpg?raw=true" width="250">
Floyd-Steinberg (reduced color bleeding) | <img src="https://github.com/todd-herbert/Heltec-213R-V2/blob/main/docs/XBitmapTutorial/DitheringExamples/FSReduced.jpg?raw=true" width="250">
Positioned | <img src="https://github.com/todd-herbert/Heltec-213R-V2/blob/main/docs/XBitmapTutorial/DitheringExamples/Positioned.jpg?raw=true" width="250">

For the tutorial image, I think that the *"Floyd-Steinberd (reduced color bleeding)"* option will probably work best.

## Isolating Colors
Every pixel in our XBitmap is represented by a single `0` or `1`. When you draw an XBitmap, you load the file and also name a color. These `0`'s and `1`'s simply tell the library whether that color  we named belongs at each pixel or not.

When it comes to drawing 3-Color images, this means we need to get a bit clever.

Of our three color palette, we get one color for free. This is the color that we set as a background in our code. For this tutorial I will be using a white background.

This means that we need to make up two separate XBitmaps for the remaining colors: one with the location of the black pixels, and one with the location of the red.

* Click *Image* -> *Duplicate* to make a copy to work with

* Open *Windows* -> *Dockable Dialogs* -> *Colormap*

* Press `D` on your computer's keyboard to reset the foreground/background colors. If you are using a different background color, you will make to set this manually (on the screen left)

* Right click on the red square in the dialog, and click "*Select this Color*"

* Push `Delete` on your computer's keyboard ( or *Edit* -> *Clear* )

Every red pixel in the image copy will be deleted and replaced with white, leaving only the black.

![scale](https://github.com/todd-herbert/Heltec-213R-V2/blob/main/docs/XBitmapTutorial/3C_color_map.png?raw=true)

## Export as XBitmap

At this stage it is time to export one of our XBitmaps: the one with with the black data.

Open the Export dialog by selecting *File* -> *Export As...*
To save as an XBitmap image, enter a filename with the `.xbm` extension. 

Be aware that the name you choose here will determine the name of the image in the code later on. A good name for our example image might be  `parrot_black.xbm`. Remember that you are also going to make an accompanying `parrot_red.xbm` file shortly.

After pressing *Export*, another "Export Image as XBM" dialog will appear. No changes are needed here, and you can click *Export* to continue.

![export dialog](https://github.com/todd-herbert/Heltec-213R-V2/blob/main/docs/XBitmapTutorial/3C_export.png?raw=true)
## Rinse and Repeat
Now it is time to go back to [Isolating Colors](#isolating-colors) and repeat the process with a fresh duplicate of the image, only this time for the red pixels instead of the black.

## Importing and Modifying
The XBitmap format only needs slight modification to be used with Adafruit_GFX.

1. The `.xbm`  extension needs to be changed to `.h`
(Note: this step is not required if you are using an alternative Arduino IDE such as vs-code).
Place the XBitmap file (now with `.h` ending) in the same directory as your .ino file and it should appear in the Arduino IDE.

2. Inside this `.h`  file, the data type of the *"image bits array"* needs to be changed. Add `PROGMEM const` before the `static unsigned char xxxx_bits[] = {` part.
 This step specifies that the XBitmap data must be stored in the flash memory space, not in the valuable SRAM space. This is a requirement of the drawXBitmap() method.

## Drawing the XBitmaps
You can now include your xbitmap files as a headers
```c++
#include "parrot_black.h"
#include "parrot_red.h"
```
Whenever your are ready, you can draw them with the drawXBitmap() method.

Here, we are drawing from the top left corner (0,0), with the width and height that are automatically set in our XBM .h file
```c++
panel.fillScreen(panel.WHITE);
panel.drawXBitmap(0, 0, parrot_black_bits, parrot_black_width, parrot_red_height, panel.BLACK);
panel.drawXBitmap(0, 0, parrot_red_bits, parrot_red_width, parrot_red_height, panel.RED);
```
<br />

![](https://github.com/todd-herbert/Heltec-213R-V2/blob/main/docs/XBitmapTutorial/3C_result.jpg?raw=true)
