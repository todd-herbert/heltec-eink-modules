/* 
    File: text.cpp

        - Dimension and position of text
        - Virtual methods from AdafruitGFX, tweaked for text-wrapping support
*/

#include "base.h"

// Text positioning
// ======================================================================

// Set the text cursor according to the desired upper left corner
void BaseDisplay::setCursorTopLeft(const char* text, uint16_t x, uint16_t y) {
    int16_t offset_x(0), offset_y(0);
    getTextBounds(text, 0, 0, &offset_x, &offset_y, NULL, NULL);
    setCursor(x - offset_x, y - offset_y);
}

// Rendered width of a string
uint16_t BaseDisplay::getTextWidth(const char* text) {
    int16_t x(0),y(0);
    uint16_t w(0), h(0);
    getTextBounds(text, 0, 0, &x, &y, &w, &h);  // Still need x and y; used internally by getTextBounds()
    return w;
}

// Rendered height of a string
uint16_t BaseDisplay::getTextHeight(const char* text) {
    int16_t x(0),y(0);
    uint16_t w(0), h(0);
    getTextBounds(text, 0, 0, &x, &y, &w, &h);  // Still need x and y; used internally by getTextBounds()
    return h;
}

// Get the required cursor X position to horizontally center text 
uint16_t BaseDisplay::getTextCenterX(const char* text) {
    int16_t offset_x(0), offset_y(0);
    uint16_t width(0), height(0);

    // Get the text dimensions
    getTextBounds(text, 0, 0, &offset_x, &offset_y, &width, &height);

    uint16_t left = bounds.window.centerX() - offset_x;
    return max(0, left - (width / 2) );
}

// Get the required cursor Y position to vertically center text 
uint16_t BaseDisplay::getTextCenterY(const char* text) {
    int16_t offset_x(0), offset_y(0);
    uint16_t width(0), height(0);

    // Get the text dimensions
    getTextBounds(text, 0, 0, &offset_x, &offset_y, &width, &height);

    uint16_t top = bounds.window.centerY() - offset_y;
    return max(0, top - (height / 2) );
}


// Virtual AdafruitGFX methods. Tweaked to implement text-wrapping 
// ================================================================

#ifndef pgm_read_byte
#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#endif
#ifndef pgm_read_word
#define pgm_read_word(addr) (*(const unsigned short *)(addr))
#endif
#ifndef pgm_read_dword
#define pgm_read_dword(addr) (*(const unsigned long *)(addr))
#endif

// Pointers are a peculiar case...typically 16-bit on AVR boards,
// 32 bits elsewhere.  Try to accommodate both...

#if !defined(__INT_MAX__) || (__INT_MAX__ > 0xFFFF)
#define pgm_read_pointer(addr) ((void *)pgm_read_dword(addr))
#else
#define pgm_read_pointer(addr) ((void *)pgm_read_word(addr))
#endif

inline GFXglyph *pgm_read_glyph_ptr(const GFXfont *gfxFont, uint8_t c) {
#ifdef __AVR__
  return &(((GFXglyph *)pgm_read_pointer(&gfxFont->glyph))[c]);
#else
  // expression in __AVR__ section may generate "dereferencing type-punned
  // pointer will break strict-aliasing rules" warning In fact, on other
  // platforms (such as STM32) there is no need to do this pointer magic as
  // program memory may be read in a usual way So expression may be simplified
  return gfxFont->glyph + c;
#endif // __AVR__
}

inline uint8_t *pgm_read_bitmap_ptr(const GFXfont *gfxFont) {
#ifdef __AVR__
  return (uint8_t *)pgm_read_pointer(&gfxFont->bitmap);
#else
  // expression in __AVR__ section generates "dereferencing type-punned pointer
  // will break strict-aliasing rules" warning In fact, on other platforms (such
  // as STM32) there is no need to do this pointer magic as program memory may
  // be read in a usual way So expression may be simplified
  return gfxFont->bitmap;
#endif // __AVR__
}

size_t BaseDisplay::write(uint8_t c) {

  if (!gfxFont) { // 'Classic' built-in font

    if (c == '\n') {              // Newline?
        cursor_x = (int16_t)bounds.window.left();               // Reset x to zero,
        cursor_y += textsize_y * 8; // advance y one line
    } 
    else if (c != '\r') {       // Ignore carriage returns
        if (wrap && ((cursor_x + textsize_x * 6) > (int16_t)bounds.window.right())) {     // Off right?
            cursor_x = (int16_t)bounds.window.left();                                       // Reset x to zero,
            cursor_y += textsize_y * 8; // advance y one line
        }
        drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize_x, textsize_y);
        cursor_x += textsize_x * 6; // Advance x one char
    }

  } 
  else {    // Custom font

    if (c == '\n') {
        cursor_x = (int16_t)bounds.window.left();
        cursor_y += (int16_t)textsize_y * (uint8_t)pgm_read_byte(&gfxFont->yAdvance);
    } 
    else if (c != '\r') {
        uint8_t first = pgm_read_byte(&gfxFont->first);
        if ((c >= first) && (c <= (uint8_t)pgm_read_byte(&gfxFont->last))) {
            GFXglyph *glyph = pgm_read_glyph_ptr(gfxFont, c - first);
            uint8_t w = pgm_read_byte(&glyph->width);
            uint8_t h = pgm_read_byte(&glyph->height);

            if ((w > 0) && (h > 0)) {                                       // Is there an associated bitmap?
                int16_t xo = (int8_t)pgm_read_byte(&glyph->xOffset);        // sic
                
                if (wrap && ((cursor_x + textsize_x * (xo + w)) > (int16_t)bounds.window.right())) {
                    cursor_x = (int16_t)bounds.window.left();
                    cursor_y += (int16_t)textsize_y * (uint8_t)pgm_read_byte(&gfxFont->yAdvance);
                }
                drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize_x, textsize_y);
            }
            cursor_x += (uint8_t)pgm_read_byte(&glyph->xAdvance) * (int16_t)textsize_x;
        }
    }
  }
  return 1;
}

void BaseDisplay::charBounds(unsigned char c, int16_t *x, int16_t *y, int16_t *minx, int16_t *miny, int16_t *maxx, int16_t *maxy) 
{
    if (gfxFont) {
        if (c == '\n') {    // Newline
            *x = (int16_t)bounds.window.left();        // Reset x to zero, advance y by one line
            *y += textsize_y * (uint8_t)pgm_read_byte(&gfxFont->yAdvance);
        } 

        else if (c != '\r') {   // Not a carriage return; is normal char
            uint8_t first = pgm_read_byte(&gfxFont->first),
                    last = pgm_read_byte(&gfxFont->last);

            if ((c >= first) && (c <= last)) { // Char present in this font?
                GFXglyph *glyph = pgm_read_glyph_ptr(gfxFont, c - first);

                uint8_t gw = pgm_read_byte(&glyph->width),
                        gh = pgm_read_byte(&glyph->height),
                        xa = pgm_read_byte(&glyph->xAdvance);
                int8_t  xo = pgm_read_byte(&glyph->xOffset),
                        yo = pgm_read_byte(&glyph->yOffset);

                if (wrap && ((*x + (((int16_t)xo + gw) * textsize_x)) > (int16_t)bounds.window.right())) {
                    *x = (int16_t)bounds.window.left(); // Reset x to zero, advance y by one line
                    *y += textsize_y * (uint8_t)pgm_read_byte(&gfxFont->yAdvance);
                }

                int16_t tsx = (int16_t)textsize_x, 
                        tsy = (int16_t)textsize_y,
                        x1 = *x + xo * tsx, 
                        y1 = *y + yo * tsy, 
                        x2 = x1 + gw * tsx - 1,
                        y2 = y1 + gh * tsy - 1;

                if (x1 < *minx)
                    *minx = x1;
                if (y1 < *miny)
                    *miny = y1;
                if (x2 > *maxx)
                    *maxx = x2;
                if (y2 > *maxy)
                    *maxy = y2;
                    
                *x += xa * tsx;
            }
        }
    }

    else {  // Default font

        if (c == '\n') {        // Newline
            *x = (int16_t)bounds.window.left();               // Reset x to zero,
            *y += textsize_y * 8; // advance y one line
            // min/max x/y unchaged -- that waits for next 'normal' character
        } 

        else if (c != '\r') { // Normal char; ignore carriage returns

            if (wrap && ((*x + textsize_x * 6) > (int16_t)bounds.window.right())) {     // Cursor beyond right edge
                *x = (int16_t)bounds.window.left();      // Reset x to zero,
                *y += textsize_y * 8;                    // advance y one line
            }

            int x2 = *x + textsize_x * 6 - 1, // Lower-right pixel of char
                y2 = *y + textsize_y * 8 - 1;
            if (x2 > *maxx)
                *maxx = x2; // Track max x, y
            if (y2 > *maxy)
                *maxy = y2;
            if (*x < *minx)
                *minx = *x; // Track min x, y
            if (*y < *miny)
                *miny = *y;
            *x += textsize_x * 6; // Advance x one char
        }
    }
}