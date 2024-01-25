// This file contains text-styling methods for the example

void drawTitle(const char* title);
void alignBottomRight(const char* text);
void textBox(const char* text, Color text_color);   // Print text at cursor, with filled background

// ----


// Draw a demo title-block: top-center, bold
void drawTitle(const char* title) {
    display.setFont( & FreeSansBold12pt7b );
    display.setTextColor(WHITE);

    // Get title-text width, height, far-left and far-top boundaries (left & top are negative)
    int TITLE_OFFSET_X(0), TITLE_OFFSET_Y(0);
    unsigned int TITLE_WIDTH(0), TITLE_HEIGHT(0);
    display.getTextBounds(title, 0, 0, &TITLE_OFFSET_X, &TITLE_OFFSET_Y, &TITLE_WIDTH, &TITLE_HEIGHT);

    // Set dimensions for the title and title block
    const int TITLE_MARGIN = 5;
    int TITLE_X = (f.width() / 2) - (TITLE_WIDTH / 2);
    int TITLE_Y = -TITLE_OFFSET_Y + TITLE_MARGIN;
    int TITLEBLOCK_X = TITLE_X + TITLE_OFFSET_X - TITLE_MARGIN;
    int TITLEBLOCK_Y = 0;
    int TITLEBLOCK_HEIGHT = TITLE_HEIGHT + (2 * TITLE_MARGIN);
    int TITLEBLOCK_WIDTH = TITLE_WIDTH + (2 * TITLE_MARGIN);

    // Fill the titleblock area with BLACK
    display.fillRect(TITLEBLOCK_X, TITLEBLOCK_Y, TITLEBLOCK_WIDTH, TITLEBLOCK_HEIGHT, BLACK);

    // Print the title text
    display.setCursor(TITLE_X, TITLE_Y);
    display.print(title);

    // Return to default text settings
    display.setFont( DEFAULT_FONT );
    display.setTextColor( DEFAULT_TEXT_COLOR );
}


// Align text bottom right
void alignBottomRight(const char* text) {

    // Grab info about dimensions and where the "cursor line" is
    int16_t offset_left = 0;
    int16_t offset_top = 0;
    uint16_t width = 0; 
    uint16_t height = 0;
    display.getTextBounds( text, 0, 0, &offset_left, &offset_top, &width, &height );

    // Place the cursor
    display.setCursor(
        f.right() - width - (2 * textbox_padding),  // Align right
        f.bottom() - textbox_padding                // Along bottom(ish)
    );
}

// Fill the area behind text
void textBox(const char* text, Color text_color) {

    // Get dimensions for the box
    int16_t left = 0;
    int16_t top = 0;
    uint16_t width = 0; 
    uint16_t height = 0;

    display.getTextBounds( text, display.getCursorX(), display.getCursorY(), &left, &top, &width, &height );

    // Fill the background
    display.fillRect( 
        left - textbox_padding, 
        top - textbox_padding, 
        width + (2 * textbox_padding), 
        height + (2 * textbox_padding), 
        text_color == BLACK ? WHITE : BLACK     // Opposite of text color
    );

    Color original_text_color;
    display.setTextColor(text_color);
    display.print(text);
    display.setTextColor(original_text_color);
}