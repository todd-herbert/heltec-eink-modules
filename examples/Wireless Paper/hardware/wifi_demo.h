// This file contains the WiFi hardware demo - scan WiFi networks

void wifiDemo() {
    // Draw the title block
    const char title_wifi[] = "WiFi Network Scan";
    drawTitle(title_wifi);

    // Draw the initial "scanning" label
    const char text_scanning[] = "scanning..";
    display.setCursor(
        display.getTextCenterX(text_scanning),
        display.getTextCenterY(text_scanning)
    );
    display.print(text_scanning);

    // Show the title and "scanning" label
    display.update();

    // NOTE: to keep things simple, this example uses a "blocking" technique
    // This is bad practice - you should use callbacks

    // ESP32 wifi: disconnect, set to station mode (client)
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    // Scan for networks
    int network_count = WiFi.scanNetworks();

    // Select "quick and dirty" display technique
    display.fastmodeOn();

    // Display the found networks, one-by-one
    for (int displayed = 0; displayed < network_count; displayed++) {
        display.clearMemory();      // Fresh drawing
        display.setCursor(0, 25);   // Text cursor "behind the title"

        // Print the current network, and the past few entries
        // Creates a "scrolling" effect
        // ---------------------------------
        int scroll;

        // Don't scroll at first - let the entries stack up
        if (displayed < 4) {
            scroll = 0;
            display.println();  // Skip first list - it is "behind the title"
        }

        // If four entries are already visible, scroll them backwards
        else
            scroll = displayed - 4;

        // Otherwise, draw the latest (and previous) entries, creating the scrolling effect
        for (; scroll <= displayed; scroll++) {
            display.print('#');
            display.print(scroll);
            display.print(": ");
            display.println(WiFi.SSID(scroll));
        }

        // Re-draw the title-block, overtop. (Layered effect)
        drawTitle(title_wifi);

        // Show this frame of the "scrolling animation"
        display.update();
    }

    // If no WiFi networks found
    if (network_count == 0) {
        display.setCursor(0, 25);

        display.println();  // Skip 1st line - "behind the title"
        display.println("Scan finished");
        display.println("No networks found");

        display.update();
    }

    // Wifi demo done
    display.fastmodeOff();      // Back to "slow and pretty" updates
    display.clearMemory();      // Clean up
    delay(8000);                // Pause for user to read
}