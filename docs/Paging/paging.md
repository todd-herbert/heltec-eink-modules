# Heltec E-Ink Modules - Paging

Older boards, like Arduino UNO R3, do not have enough RAM to render a full screen image. A technique called "paging" lets us get around this issue. 
<!-- On these older boards, your drawing commands are run, over and over, calculating just one small area at a time.  -->

Instead of storing the full image in RAM, we only use enough memory to hold a small region. The full image is rendered, but any pixels that fall outside this region are ignored. This rendered region is transferred to the Display's on-board memory. The process is then repeated for a different region, re-using the same RAM on Arduino, until the whole screen has been calculated, piece by piece.


![paging graphic](paging_graphic.png)

**If you have a more powerful board (ESP, SAMD21), the library won't bother paging. Your image will be calculated once, and once only, at full speed.**

If your Arduino *is* paging to compensate for low RAM, or you wish to re-enable paging on a newer board, most displays allow you to set the optional ```page_height``` argument in your constructor.

```c++
DEPG0150BNS810 display(dc, cs, busy, page_height); 
```

For Uno R3, the default value is 20, meaning the display is calculated 20 rows at a time. Higher values use more RAM.


**Attention ATmega2560 users:** <br /> 

* Paging is used for 3-Color displays: insufficient RAM.
* 2.9" displays use **60% of  ATmega2560's RAM**. If this in unacceptable, enable paging by setting a `page_height` in your [constructor](/docs/API.md#display-constructors).
