#ifndef __BOUNDS_H__
#define __BOUNDS_H__

#include "DataTypes/enums.h"

#include "Bounds/window.h"
#include "Bounds/full.h"

// Subclasses to provide dimensioning info
class Bounds { 
    public:  
        // Constructors
        Bounds() = default;
        Bounds( const uint16_t drawing_width,
                const uint16_t drawing_height,
                uint16_t *window_top, 
                uint16_t *window_right, 
                uint16_t *window_bottom, 
                uint16_t *window_left, 
                uint8_t *rotation, 
                Flip *flip ) {

            this->window = WindowBounds(drawing_width, drawing_height, window_top, window_right, window_bottom, window_left, rotation, flip);
            this->full = FullBounds(drawing_width, drawing_height, rotation);
        } 

        WindowBounds window;
        FullBounds full; 
};


#endif