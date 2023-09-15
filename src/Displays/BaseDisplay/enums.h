#ifndef __BASE_DISPLAY_ENUMS_H__
#define __BASE_DISPLAY_ENUMS_H__

enum Flip : uint8_t {NONE = 0, HORIZONTAL=1, VERTICAL=2, HORIZONTAL_WINDOW=5, VERTICAL_WINDOW=6};
enum Rotation : uint8_t {PINS_ABOVE = 0, PINS_LEFT=1, PINS_BELOW = 2, PINS_RIGHT = 3};
enum Color : uint8_t {BLACK = 0, WHITE = 1, RED = 3};   // RED = 3, to simplify pixel processing with 3 color displays
enum SwitchType : bool {PNP = LOW, NPN = HIGH, ACTIVE_LOW = LOW, ACTIVE_HIGH = HIGH};
#endif