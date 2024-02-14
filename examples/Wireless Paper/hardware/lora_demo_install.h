// This file contains the LoRa demo (detect channel activity)
// It also contains an alternate "install walkthrough" for RadioLib, if not found.

void LoRaDemo();
void installRadioLibGuide();

// ---

// If RadioLib library is installed
#ifdef _RADIOLIB_H
    // Listen for any LoRa activity
    void LoRaDemo() {
        // Draw the title block
        drawTitle("LoRa Test");
        display.update();

        // Prepare to draw body text
        display.fastmodeOn();
        display.setCursor(0, 47);

        // Create the LoRa radio object
        SX1262 radio = new Module(PIN_LORA_NSS, PIN_LORA_DIO_1, PIN_LORA_NRST, PIN_LORA_BUSY);

        // Start the LoRa hardware
        int state = radio.begin();

        // If there was an error starting-up
        if (state != RADIOLIB_ERR_NONE) {
            display.println("- Error starting LoRa hardware");
            display.update();
        }

        // Start-up went fine - carry on
        else {
            display.println("- Hardware started successfully");
            display.println("- Listening for LoRa traffic");
            display.update();

            // Listen (blocking) until a LoRa transmission is overheard, or 15 seconds pass
            bool found = false;
            uint32_t listening_begins = millis();

            do {
                // Detect Channel Activity
                if ( radio.scanChannel() == RADIOLIB_LORA_DETECTED ) {
                    found = true;
                    break;
                }
                delay(100); // RadioLib example suggest waiting 100ms between scans (?)

            } while (millis() - listening_begins < 15000);  // Only spend 15 seconds waiting


            // Finished listening - did we get a TX, or did we timeout?
            if (found)
                display.println("- Detected LoRa activity!");
            else {
                display.println("- Didn't hear any traffic");
                display.println("  Maybe no-one is transmitting?");
            }
            display.update();
        }

        // LoRa demo done
        display.fastmodeOff();
        display.clearMemory();
        delay(5000);
    }

#endif

// The installGuide() function is only built if Radiolib not installed
#ifndef _RADIOLIB_H

    // Give installation instructions for RadioLib
    void installRadioLibGuide() {

        display.clearMemory();
        drawTitle("Library not found");
        const char text_libnotfound[] = \
            "The 'RadioLib' library\n" \
            "is required to run\n" \
            "the LoRa example.";

        display.setCursor(
            display.getTextCenterX(text_libnotfound),
            60
        );

        display.print(text_libnotfound);

        display.update();
        delay(8000);

        // Screen 1 - Arduino IDE

        // Draw the IDE image
        display.clearMemory();    
        display.drawXBitmap(0, 0, radiolib1_bits, 255, 122, BLACK);
        display.update();

        delay(1000);    // Let user 'take in' the IDE

        display.fastmodeOn();

        // Draw a thick circle around the Library Manager icon
        for(int radius = 18; radius <= 20; radius++)
            display.drawCircle(
                17,
                110,
                radius,
                BLACK
            );

        display.update();

        char caption_openlibman[] = "Open 'Library Manager'";
        alignBottomRight(caption_openlibman);
        textBox(caption_openlibman, WHITE);
        display.update();

        delay(4000);

        // Screen 2 - Library manager opens

        // Draw the IDE with library manager
        display.clearMemory();
        display.drawXBitmap(0, 0, radiolib2_bits, 255, 122, BLACK);
        display.update();

        delay(1000);    // Let user 'take in' the new IDE screenshot

        // Circle the search box
        display.drawRoundRect(
            40,     // Left
            20,     // Top
            160,    // Width
            45,     // Height
            10,     // Corner radius
            BLACK   // Line color
        );
        display.update();

        // Print the query in the search box
        display.setFont(NULL);                      // Use built-in font: smaller
        display.setCursor(55, 48);                  // Place cursor over the library manager search box
        textBox("radiolib        ", BLACK);
        display.setFont(DEFAULT_FONT);
        display.update();

        // Print the caption - Search 'radiolib'
        const char caption_search[] = "Search 'radiolib'";
        alignBottomRight(caption_search);
        textBox(caption_search, WHITE);
        display.update();

        delay(4000);

        // Screen 3


        // Draw the IDE image, scrolled down to show "install"
        display.clearMemory();
        display.drawXBitmap(0, 0, radiolib3_bits, 255, 122, BLACK);
        display.update();

        delay(1000);    // Let the user "take in" the new IDE screenshot

        // Circle the search box
        display.drawRoundRect(
            100,    // Left
            92,     // Top
            85,     // Width
            31,     // Height
            10,     // Corner radius
            BLACK   // Line color
        );
        display.update();

        // Print the caption - Press install
        display.setCursor(115, 70);     // Not in the corner, would cover the button
        textBox("Press install", WHITE);
        display.update();

        delay(4000);

        // End of install guide
        display.fastmodeOff();
        display.clearMemory();
        return;
    }

#endif