#include "HTE029A1.h"

/// Draw a single pixel. 
/// This method is overriden from GFX_Root, and all other drawing methods pass through here

void HTE029A1::drawPixel(int16_t x, int16_t y, uint16_t color) {
    // Rotate the pixel
    int16_t x1, y1;
    switch(rotation) {
        case 0:         // No rotation
            x1=x;
            y1=y;
            break;
        case 1:         // 90deg clockwise
            x1 = (panel_width - 1) - y;
            y1 = x;
            break;
        case 2:         // 180deg
            x1 = (panel_width - 1) - x;
            y1 = (panel_height - 1) - y;
            break;
        case 3:         // 270deg clockwise
            x1 = y;
            y1 = (panel_height - 1) - x;
            break;
    }
    x = x1;
    y = y1;

    // Handle flip
    if (imgflip & FlipList::HORIZONTAL) {
        if (rotation % 2)   // If landscape
            y = (drawing_height - 1) - y;
        else                    // If portrait
            x = (drawing_width - 1) - x;
    }
    if (imgflip & FlipList::VERTICAL) {
        if (rotation % 2)   // If landscape
            x = (drawing_width - 1) - x;
        else                    // If portrait
            y = (drawing_height - 1) - y;
    }

    // Check if pixel falls in our page
    if((uint16_t) x >= winrot_left && (uint16_t) y >= page_top && (uint16_t) y <= page_bottom && (uint16_t) x <= winrot_right) {

        // Calculate a memory location for our pixel

        uint16_t memory_location;
        
        memory_location = (y - page_top) * ((winrot_right - winrot_left + 1) / 8);
        memory_location += ((x - winrot_left) / 8);     
        uint16_t bit_location = x % 8;  // Find the location of the bit in which the value will be stored
        bit_location = (7 - bit_location);  // For some reason, the screen wants the bit order flipped. MSB vs LSB?

        // Insert the correct color values into the appropriate location
        uint8_t bitmask = ~(1 << bit_location);
        page_black[memory_location] &= bitmask;
        page_black[memory_location] |= (color & colors.WHITE) << bit_location;
    }
}

/// Set the image flip
/// Proceed with caution - Window locations do not flip, but content drawn into them does
void HTE029A1::setFlip(FlipList::Flip flip) {
    this->imgflip = flip;
}

/// Set the color of the blank canvas, before any drawing is done
/// Note: Function is efficient, but only takes effect at the start of a calculation. At any other time, use fillScreen()
void HTE029A1::setDefaultColor(uint16_t bgcolor) {
    default_color = bgcolor;
}

/// Set the text cursor according to the desired upper left corner
void HTE029A1::setCursorTopLeft(const char* text, uint16_t x, uint16_t y) {
    int16_t offset_x(0), offset_y(0);
    getTextBounds(text, 0, 0, &offset_x, &offset_y, NULL, NULL);
    setCursor(x - offset_x, y - offset_y);
}

uint16_t HTE029A1::getTextWidth(const char* text) {
    int16_t x(0),y(0);
    uint16_t w(0), h(0);
    getTextBounds(text, 0, 0, &x, &y, &w, &h);  // Need to keep x and y as they appear to be used internally by getTextBounds()
    return w;
}

uint16_t HTE029A1::getTextHeight(const char* text) {
    int16_t x(0),y(0);
    uint16_t w(0), h(0);
    getTextBounds(text, 0, 0, &x, &y, &w, &h);  // Need to keep x and y as they appear to be used internally by getTextBounds()
    return h;
}



// Helper methods to find window bounds
// ======================================

uint16_t HTE029A1::Bounds::Window::top() {
    return getWindowBounds(T);
}

uint16_t HTE029A1::Bounds::Window::right() {
    return getWindowBounds(R);
}

uint16_t HTE029A1::Bounds::Window::bottom() {
    return getWindowBounds(B);
}

uint16_t HTE029A1::Bounds::Window::left() {
    return getWindowBounds(L);
}

uint16_t HTE029A1::Bounds::Window::getWindowBounds(HTE029A1::Bounds::Window::side request) {

    // Boolean LUT (x:side, y:rotation): after considering rotation, does requested edge need to measure from opposite edge.
    static const uint8_t rotswap_lut[4] = { B0000,
                                            B0101,
                                            B1111,
                                            B1010 };

    // Handle setFlip() - first part
    // If flipping, we need to find the opposite edge, and right at the end, measure from the opposite side
    if ( (request % 2) && (*m_imgflip & flip.HORIZONTAL) ) {  // If we're flipping horizontal, and this edge needs flipping
        request = (Window::side)((request + 2) % 4);
    }
    if ( !(request % 2) && (*m_imgflip & flip.VERTICAL) ) {  // If vertical flip
        request = (Window::side)((request + 2) % 4);      
    } // -------------- End Flip Part 1 -----------

    uint16_t rotated_request = (request + *m_rotation) % 4;    // Rotate the Window::side value
    uint16_t result;    // Build in this varaible    

    // Given our request side and rotation, do we need to measure from opposite edge
    bool rotswap = rotswap_lut[*m_rotation] & (1 << request);

    // Start by simply picking a rotated edge
    result = *edges[rotated_request];

    // If required by LUT, find display width or height, and subtract the edge distance
    if (rotswap) {
        uint16_t minuend = (rotated_request % 2) ? (drawing_width - 1) : (drawing_height - 1);
        result = minuend - result;
    }

    // Handle setFlip() - 2nd part
    if ( (request % 2) && (*m_imgflip & flip.HORIZONTAL) ) {  // If we're flipping horizontal, and this edge needs flipping
        uint16_t minuend = (rotated_request % 2) ? (drawing_width - 1) : (drawing_height - 1);
        result = minuend - result;
    }
    if ( !(request % 2) && (*m_imgflip & flip.VERTICAL) ) {  // If vertical flip
        uint16_t minuend = (rotated_request % 2) ? (drawing_width - 1) : (drawing_height - 1);
        result = minuend - result;    
    } // ----------- end flip part 2 -------------

    return result;
}

// Font overrides to use bounds.window.left() and bounds.window.right() instead of _width from GFX
// ===============================================================================================

// Many (but maybe not all) non-AVR board installs define macros
// for compatibility with existing PROGMEM-reading AVR code.
// Do our own checks and defines here for good measure...

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

size_t HTE029A1::write(uint8_t c) 
{
  if (!gfxFont) { // 'Classic' built-in font

    if (c == '\n') {              // Newline?
      cursor_x = (int16_t)bounds.window.left();               // Reset x to zero,
      cursor_y += textsize_y * 8; // advance y one line
    } else if (c != '\r') {       // Ignore carriage returns
      if (wrap && ((cursor_x + textsize_x * 6) > (int16_t)bounds.window.right())) { // Off right?
        cursor_x = (int16_t)bounds.window.left();                                       // Reset x to zero,
        cursor_y += textsize_y * 8; // advance y one line
      }
      drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize_x,
               textsize_y);
      cursor_x += textsize_x * 6; // Advance x one char
    }

  } else { // Custom font

    if (c == '\n') {
      cursor_x = (int16_t)bounds.window.left();
      cursor_y +=
        (int16_t)textsize_y * (uint8_t)pgm_read_byte(&gfxFont->yAdvance);
    } else if (c != '\r') {
      uint8_t first = pgm_read_byte(&gfxFont->first);
      if ((c >= first) && (c <= (uint8_t)pgm_read_byte(&gfxFont->last))) {
        GFXglyph *glyph = pgm_read_glyph_ptr(gfxFont, c - first);
        uint8_t w = pgm_read_byte(&glyph->width),
                h = pgm_read_byte(&glyph->height);
        if ((w > 0) && (h > 0)) { // Is there an associated bitmap?
          int16_t xo = (int8_t)pgm_read_byte(&glyph->xOffset); // sic
          if (wrap && ((cursor_x + textsize_x * (xo + w)) > (int16_t)bounds.window.right())) {
            cursor_x = (int16_t)bounds.window.left();
            cursor_y += (int16_t)textsize_y *
                        (uint8_t)pgm_read_byte(&gfxFont->yAdvance);
          }
          drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize_x,
                   textsize_y);
        }
        cursor_x +=
          (uint8_t)pgm_read_byte(&glyph->xAdvance) * (int16_t)textsize_x;
      }
    }
  }
  return 1;
}

void HTE029A1::charBounds(unsigned char c, int16_t *x, int16_t *y, int16_t *minx, int16_t *miny, int16_t *maxx, int16_t *maxy) 
{

  if (gfxFont) {

    if (c == '\n') { // Newline?
      *x = (int16_t)bounds.window.left();        // Reset x to zero, advance y by one line
      *y += textsize_y * (uint8_t)pgm_read_byte(&gfxFont->yAdvance);
    } else if (c != '\r') { // Not a carriage return; is normal char
      uint8_t first = pgm_read_byte(&gfxFont->first),
              last = pgm_read_byte(&gfxFont->last);
      if ((c >= first) && (c <= last)) { // Char present in this font?
        GFXglyph *glyph = pgm_read_glyph_ptr(gfxFont, c - first);
        uint8_t gw = pgm_read_byte(&glyph->width),
                gh = pgm_read_byte(&glyph->height),
                xa = pgm_read_byte(&glyph->xAdvance);
        int8_t xo = pgm_read_byte(&glyph->xOffset),
               yo = pgm_read_byte(&glyph->yOffset);
        if (wrap && ((*x + (((int16_t)xo + gw) * textsize_x)) > (int16_t)bounds.window.right())) {
          *x = (int16_t)bounds.window.left(); // Reset x to zero, advance y by one line
          *y += textsize_y * (uint8_t)pgm_read_byte(&gfxFont->yAdvance);
        }
        int16_t tsx = (int16_t)textsize_x, tsy = (int16_t)textsize_y,
                x1 = *x + xo * tsx, y1 = *y + yo * tsy, x2 = x1 + gw * tsx - 1,
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

  } else { // Default font

    if (c == '\n') {        // Newline?
      *x = (int16_t)bounds.window.left();               // Reset x to zero,
      *y += textsize_y * 8; // advance y one line
      // min/max x/y unchaged -- that waits for next 'normal' character
    } else if (c != '\r') { // Normal char; ignore carriage returns
      if (wrap && ((*x + textsize_x * 6) > (int16_t)bounds.window.right())) { // Off right?
        *x = (int16_t)bounds.window.left();                                       // Reset x to zero,
        *y += textsize_y * 8;                         // advance y one line
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