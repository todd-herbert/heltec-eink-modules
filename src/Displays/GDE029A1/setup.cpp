#include "GDE029A1.h"

void GDE029A1::init() {
    BaseDisplay::panel_width = this->panel_width;
    BaseDisplay::panel_height = this->panel_height;

    BaseDisplay::supported_colors = this->supported_colors;

    // Not set for this display: same as panel
    BaseDisplay::drawing_width = this->panel_width;
    BaseDisplay::drawing_height = this->panel_height;

    // TODO: call BaseDisplay::begin() from here. Implement at next major version - breaking change
}