// This file contains the BLE hardware demo - scan for BLE devices

void BLEDemo() {
    // Show the title block
    const char title_bt[] = "BLE Scan";
    drawTitle(title_bt);
    display.update();

    // Set-up a new scan
    BLEScan* scan;
    BLEDevice::init("Wireless Paper");
    scan = BLEDevice::getScan();    // Get the "scanner" object
    scan->setActiveScan(true);      // Full power
    scan->setInterval(100);         // How often to scan
    scan->setWindow(99);            // How long to scan for - less than interval

    // Keep track of which devices we have displaye
    int displayed = 0;

    // Start time for the demo - limit the duration
    uint32_t ble_demo_start = millis();

    // Enable "quick and dirty" display updates
    display.fastmodeOn();

    // NOTE: to keep things simple, this example uses a "blocking" technique
    // This is bad practice - you should use callbacks

    // Loop for 10 seconds
    do {

        #if defined(ESP_ARDUINO_VERSION_MAJOR) && ESP_ARDUINO_VERSION_MAJOR == 3    // Heltec ESP32 dev enviornment v3.0.0
            // Scan (blocking) for one second
            BLEScanResults *scan_results = scan->start(1, true);
        #else
            // Scan (blocking) for one second
            BLEScanResults scan_results_obj = scan->start(1, true);
            BLEScanResults *scan_results = &scan_results_obj;   // Only used to make the example compatible with old + new Heltec environment
        #endif

        // If device count increased, print the new data
        for (; displayed < scan_results->getCount(); displayed++) {

            display.clearMemory();
            display.setCursor(0, 25);

            // Print the current network, and the past few entries
            // Creates a "scrolling" effect
            // ---------------------------------
            int s;  // Scroll (iterator)

            // At first - no scroll, let the entries stack up
            if (displayed < 4) {
                display.println();
                s = 0;
            }

            // Otherwise, draw the latest (and previous) entries, creating the scrolling effect
            else 
                s = displayed - 4;

            // Print the device string
            // -----------------------
            for(; s <= displayed; s++) {
                // Index
                display.print("#");
                display.print(s);
                // RSSI
                display.print(": (");
                display.print(scan_results->getDevice(s).getRSSI());
                display.print("dBm) ");
                // Name, if present
                if (scan_results->getDevice(s).haveName())
                    display.println(scan_results->getDevice(s).getName().c_str());
                // Address, if no name
                else 
                    display.println(scan_results->getDevice(s).getAddress().toString().c_str());   
            }             

            // Draw the title block over-top (layered effect)
            drawTitle(title_bt);

            // Show this frame of the scrolling animation
            display.update();
        }
    } while (millis() - ble_demo_start < 10000);    // Only spend 10 seconds displaying new ble devices

    // If no BLE devices found
    if (displayed == 0) {
        display.setCursor(0, 25);

        display.println();
        display.println("No BLE devices found");
        display.println("within 10 seconds");

        display.update();
    }

    // Free memory
    scan->clearResults();

    // BLE demo done
    display.fastmodeOff();
    display.clearMemory();
    delay(5000);
}