// This file contains the first and last scenes of the example

void intro();
void outro();

// ---

// Disclaimer - don't use this example as a reference, please!
void intro() {
    // Show the title block
    const char title_intro[] = "Wireless Paper";
    drawTitle(title_intro); // (We defined this function)
    display.update();

    // Read the title
    delay(1000);

    // Use the "quick and dirty" update technique
    display.fastmodeOn();

    display.setCursor(5, 50);   // Text cursor
    display.print( \
        "This example shows that the\n" \
        "'heltec-eink-modules' library\n" \
        "is compatible with the board's\n" \
        "wireless hardware." \
    );
    display.update();

    // Read the 1st paragraph
    delay(10000);

    display.clearMemory();      // Fresh drawing
    display.setCursor(5, 50); 
    display.print( \
        "This is only a proof of\n" \
        "concept. It does not show\n" \
        "good technique for using\n" \
        "the wireless hardware.\n" \
    );
    drawTitle(title_intro);     // We cleared this too, gotta draw it again
    display.update();

    // Read the 2nd paragraph
    delay(10000);

    display.fastmodeOff();  // Back to the "slow and pretty" updates
    display.clearMemory();  // Clean up - fresh drawing for next demo
}

// Park the example on a showy image
void outro() {
    display.fastmodeOn();

    const char text_done[] = "Demo Complete";
    display.setFont( & FreeSansBold12pt7b );

    // Quickly show the text on a white screen
    display.clearMemory();
    display.setCursor(
        display.getTextCenterX(text_done),
        display.getTextCenterY(text_done)
    );
    textBox(text_done, WHITE);  // White text on black bg
    display.update();


    display.fastmodeOff();
    display.clearMemory();

    // Draw the chessboard image around the edge, slowly
    display.drawXBitmap(0, 0, chess_bits, chess_width, chess_height, BLACK);
    display.update();
}