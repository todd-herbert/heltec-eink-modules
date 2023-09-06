#include "QYEG0213RWS800.h"

void QYEG0213RWS800::init() {
    BaseDisplay::panel_width = this->panel_width;
    BaseDisplay::panel_height = this->panel_height;

    BaseDisplay::drawing_width = this->drawing_width;
    BaseDisplay::drawing_height = this->drawing_height;

    BaseDisplay::supported_colors = this->supported_colors;

    BaseDisplay::init();    // Now that BaseDisplay has the info, it can finish the setup
}