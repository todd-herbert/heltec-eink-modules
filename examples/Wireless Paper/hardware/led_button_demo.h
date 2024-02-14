// This file contains the demo section for BUTTON_PRG and LED_BULITIN

void LEDDemo();
void buttonDemo();

// ---

// Demonstrate LED_BUILTIN
void LEDDemo() {
    // Draw a faded version of the board's rear
    display.clearMemory();    
    display.drawXBitmap(0, 0, board_inverse_bits, 255, 122, BLACK);
    display.update();

    delay(1000);    // Let user "take in" the board image

    display.fastmodeOn();

    // Draw a thick circle around LED_BUILTIN
    for(int radius = 14; radius <= 15; radius++)
        display.drawCircle(
            220,    // Center X
            4,      // Center Y
            radius,
            BLACK
        );
    display.update();

    // Print the caption - LED_BUILTIN
    display.setCursor(110, 30);
    textBox("LED_BUILTIN", WHITE);
    display.update();


    // Blink the LED for a while
    const uint8_t blink_freq = 3;           // Hz
    const uint16_t blink_duration = 15;     // Seconds

    pinMode(LED_BUILTIN, OUTPUT);
    for(uint16_t count = 0; count < blink_freq * blink_duration; count++) {
        digitalWrite(LED_BUILTIN, (count % 2) ? LOW : HIGH);

        uint32_t pause_start = millis();
        while (millis() - pause_start < (500 / blink_freq) )
            yield();
    }
    digitalWrite(LED_BUILTIN, LOW);     // Make double-sure we turned the LED off

    display.fastmodeOff();
}


// Demonstrate BUTTON_PRG
void buttonDemo() {
    // Draw a faded version of the board's rear
    display.fastmodeOn();
    display.clearMemory();    
    display.drawXBitmap(0, 0, board_inverse_bits, 255, 122, BLACK);
    display.update();

    // Draw a thick circle around the PRG button
    for(int radius = 14; radius <= 16; radius++)
        display.drawCircle(
            145,    // Center X
            117,    // Center Y
            radius,
            BLACK
        );
    display.update();

    delay(1000);    // Let the user spot where the button is..

    // Print the caption - BUTTON_PRG
    display.setCursor(110, 20);
    textBox("BUTTON_PRG", WHITE);
    display.update();

    // Print comment - External pull-up
    display.println();              // Drop down a line
    display.setCursor(              // (Lazy)
        display.getCursorX() - 5,   // Cursor slightly left
        display.getCursorY() + 10   // Cursor slightly down
    );
    textBox("(external pull-up)", WHITE);    // Black text, on white bg
    display.update();

    delay(1000);    // Pause to read about BUTTON_PRG

    // Draw a hooked arrow, pointing to BUTTON_PRG
    display.drawXBitmap(175, 75, arrow_hooked_bits, arrow_hooked_width, arrow_hooked_height, BLACK);
    display.update();

    // Print comment - Press to continue
    display.println();              // Drop down a line
    display.setCursor(
        display.getCursorX() - 5,   // Corsor slightly left
        display.getCursorY() + 10   // Cursor slightly down
    );
    textBox("Press to continue", BLACK);    // Black text, on white bg
    display.update();


    pinMode(BUTTON_PRG, INPUT);                 // (Redundant? - call added for clarity)
    while (digitalRead(BUTTON_PRG) == HIGH)     // External pull-up resistor
        yield();
    
    display.fastmodeOff();
}