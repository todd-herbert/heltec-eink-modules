#include <heltec-eink-modules.h>

// Pick your panel  -  https://github.com/todd-herbert/heltec-eink-modules
// ---------------

    // EInkDisplay_WirelessPaperV1 display;
    // EInkDisplay_WirelessPaperV1_1 display;


// DEMO: Wireless Paper - Download
// -------------------------------
// This example is only for Heltec's "Wireless Paper" all-in-one boards.
// Downloads a JPG image from a web url, decodes as a mono bitmap, and draws to display.
//
// This sketch is NOT a feature of the library, this is only a demonstration.
//
// No dithering is performed!
// For best results, JPG should be formatted for E-Ink display BEFORE upload to web
// Open the IMAGE_URL in your browser and take a look.
//
// JPG decoding performed by the Bodmer/TJpg_Decoder library - included with example sketch
// Not all compression methods supported. If image fails, try another one?


// Sketch config
// -------------

// WiFi Settings (for image download)
#define WIFI_SSID "Your WiFi Name"
#define PASSWORD "Your Password"

// URL of image to download
#define IMAGE_URL "https://raw.githubusercontent.com/todd-herbert/heltec-eink-modules/c82d910/docs/WirelessPaper/snowy.jpg"

// Shrink the downloaded image before drawing
// Higher values: smaller image
// (1, 2, 4 or 8)
#define IMAGE_SCALE 1

// How bright a pixel must be to draw as white
// Higher values: draw more black pixels
#define BW_THRESHOLD 0.5

// -------------

#include <FS.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "TJpg_Decoder.h"

// List of functions to define later (prototyping)
bool writeToEink(int16_t x_start, int16_t y_start, uint16_t w, uint16_t h, uint16_t* decoded_block);
void logToDisplay(const char* message, bool use_fastmode = true);

void setup() {
    // Prepare display for log messages
    display.landscape();
    display.clear();
    display.fastmodeOn();

    char message[60];   // Used to build strings for log
    const char local_filename[] = "/demo_image.jpg";    // Save downloaded image as

    // Download the image to SPIFFS (ESP32 filesystem, old style)
    // ----------------------------------------------------------

    // Initialise SPIFFS, formatting if needed
    if (!SPIFFS.begin()) {
        logToDisplay("[FS] Formatting, please wait.");
        
        if (!SPIFFS.format() || !SPIFFS.begin()) {
            logToDisplay("[FS] Formatting failed. Aborting", false);
            return;
        }
    }
    logToDisplay("[FS] SPIFFS (filesystem) init done.");

    // If file already exists locally, delete it
    if (SPIFFS.exists(local_filename)) {
        logToDisplay("[FS] Deleting existing image.");
        SPIFFS.remove(local_filename);
    }

    // Connect to WiFi
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, PASSWORD);
    uint32_t wifi_connect_start = millis();
    logToDisplay("[WiFi] Attempting to connect.");
    bool logged_stillwaiting = false;
    while (WiFi.status() != WL_CONNECTED) {
        uint32_t now = millis();
        if (!logged_stillwaiting && now > wifi_connect_start + 15000) {
            logToDisplay("[WiFi] Still waiting...");
            logged_stillwaiting = true;
        }
        if (millis() > wifi_connect_start + 30000) {
            logToDisplay("[WiFi] Connection timeout. Aborting.", false);
            return;
        }
        yield();
    }
    logToDisplay("[WiFi] Connection successful.");
    
    // Start the HTTP connection
    HTTPClient http;
    http.begin(IMAGE_URL);
    int http_code = http.GET();

    // Log the HTTP response code
    strcpy(message, "[WiFi] HTTP response: ");
    char http_code_str[5];
    itoa(http_code, http_code_str, 10);
    strcat(message, http_code_str);
    logToDisplay(message);

    // Abort if any code other than 200
    if (http_code != HTTP_CODE_OK) {
        logToDisplay("[WiFi] Needed response 200 (OK). Aborting.", false);
        return;
    }

    logToDisplay("[WiFi] Download begins. Please wait.");

    // Open a new local file, to receive download
    fs::File image_file = SPIFFS.open("/demo_image.jpg", "w+");

    // Get the remote filesize
    int remote_filesize = http.getSize();
    int remaining = remote_filesize;

    // Buffer and stream, for download
    uint8_t download_buffer[128];
    WiFiClient *stream = http.getStreamPtr();

    // While filesize incomplete, and HTTP still connected, stream to local file
    while (http.connected() && (remaining > 0 || remote_filesize == -1)) {
        // How many bytes can we read right now
        unsigned int bytes_available = stream->available();

        // If *any* bytes of data available
        if (bytes_available > 0) {
            // Download bytes into the buffer: as many as possible, so long as less than buffer size
            int amount_read = stream->readBytes( download_buffer, min(bytes_available, sizeof(download_buffer)) );
            
            // Write the downloaded bytes from the buffer to the local file
            image_file.write(download_buffer, amount_read);

            // Keep track of download progress (hopefully)
            remaining -= amount_read;
        }

        yield(); // Give any other tasks a chance to run too
    }
    image_file.close();
    http.end();

    if (remaining == 0)
        logToDisplay("[WiFi] Download complete.");
    else if (remaining == -1)
        logToDisplay("[WiFi] Download complete? Download size unknown.");
    else {
        logToDisplay("[WiFi] Connection closed unexpectedly. Aborting.", false);
        return;
    }

    // Process the downloaded image
    // ----------------------------

    TJpgDec.setJpgScale(IMAGE_SCALE); // (1, 2, 4 or 8) Higher values shrink the image.

    // Specify the function which will handle the decoded output
    // We've written this ourselves, below
    TJpgDec.setCallback(writeToEink);

    // Grab the image dimensions, for position on the screen
    uint16_t jpeg_width, jpeg_height;
    TJpgDec.getJpgSize(&jpeg_width, &jpeg_height, "/demo_image.jpg");
    jpeg_width /= IMAGE_SCALE;
    jpeg_height /= IMAGE_SCALE;

    // Log the image dimensions
    strcpy(message, "[JPEG] Dimensions: ");
    char dimension[6];
    itoa(jpeg_width, dimension, 10);
    strcat(message, dimension);
    strcat(message, "px x ");
    itoa(jpeg_height, dimension, 10);
    strcat(message, dimension);
    strcat(message, "px");
    logToDisplay(message);

    // Check if image HAS dimensions
    if (jpeg_width == 0 && jpeg_height == 0) {
        logToDisplay("[JPEG] Unsupported JPG compression? Aborting", false);
        return;
    }

    // Align the bottom of screen with bottom edge of image
    // (Just because it looks better with the demo image)
    int16_t image_y = display.bounds.full.height() - jpeg_height;

    // Begin decoding - calls writeToEink with decoded data
    logToDisplay("[JPEG] Begin decoding.");
    TJpgDec.drawFsJpg(0, image_y, "/demo_image.jpg");

    // All decoded, all processed through writeToEink() - time to display the result
    display.fastmodeOff();
    display.update();
}


void loop() {

}

// Decide if the decoded grayscale pixel are white or black, then write to display
bool writeToEink(int16_t x_start, int16_t y_start, uint16_t w, uint16_t h, uint16_t* decoded_block) {

    uint8_t *grayscale_pixels = (uint8_t*)decoded_block;
    uint16_t count = 0;

    // Loop down rows
    for (int16_t y = y_start; y < (y_start + h); y++) {
        // Loop along row (pixels)
        for (int16_t x = x_start; x < (x_start) + w; x++) {

            // Interpret gray pixel as either black or white (threshold set at top of sketch)
            Color c = grayscale_pixels[count] > (uint8_t)(255 * BW_THRESHOLD) ? WHITE : BLACK;

            // Hand-off to "heltec-eink-modules" library
            display.drawPixel(x, y, c);

            // Step through "decoded_block"
            count++;
        }
    }
  // Return 1 to decode next block
  return true;
}

// Log sketch info to display, instead of serial monitor
void logToDisplay(const char* message, bool use_fastmode) {

    // If not a blank message, insert a bullet point
    if (strlen(message) > 0)
        display.print("- ");

    display.println(message);
    display.setCursor(0, display.getCursorY() + 3); // Extra line spacing 
    
    // Draw without fastmode, for display health
    if (!use_fastmode) {
        display.fastmodeOff();
        display.update();
        display.fastmodeOn();
    }
    
    // Not cleaning. Use fastmode
    else
        display.update();
}
