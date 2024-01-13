#ifndef __BASE_DISPLAY_ENUMS_H__
#define __BASE_DISPLAY_ENUMS_H__

enum Flip : uint8_t {NONE = 0, HORIZONTAL=1, VERTICAL=2, HORIZONTAL_WINDOW=5, VERTICAL_WINDOW=6};
enum Color : uint8_t {BLACK = 0, WHITE = 1, RED = 3};
enum SwitchType : bool {PNP = LOW, NPN = HIGH, ACTIVE_LOW = LOW, ACTIVE_HIGH = HIGH};

enum Rotation : uint8_t {
    // For "display modules" 
    PINS_ABOVE = 0, 
    PINS_LEFT=1, 
    PINS_BELOW = 2, 
    PINS_RIGHT = 3,

    // For "Wireless Paper" all-in-one board
    USB_ABOVE = 0,
    USB_LEFT = 1,
    USB_BELOW = 2,
    USB_RIGHT = 3
    };

#endif