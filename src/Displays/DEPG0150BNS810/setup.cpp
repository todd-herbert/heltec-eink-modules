#include "DEPG0150BNS810.h"

void DEPG0150BNS810::init() {
    BaseDisplay::panel_width = this->panel_width;
    BaseDisplay::panel_height = this->panel_height;

    // Not set for this display: same as panel
    BaseDisplay::drawing_width = this->panel_width;
    BaseDisplay::drawing_height = this->panel_height;

    BaseDisplay::supported_colors = this->supported_colors;

    BaseDisplay::init();    // Now that BaseDisplay has the info, it can finish the setup
}