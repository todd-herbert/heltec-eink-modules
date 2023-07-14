// Define your pins:
// ------------------

// ( DO NOT connect pins directly to display )
// See https://github.com/todd-herbert/heltec-eink-modules#wiring

    #define PIN_BUSY    7
    #define PIN_CS      10
    #define PIN_DC      8


// Identify Your Display
// --------------------------------------------------------

// This sketch cycles through different modes, allowing you to determine which is correct for your E-ink module.
// Connect your display and upload to your Arduino UNO.

// The test image is a white background, with a black cross from corner to corner.
// The display model name is also printed.

// The orange on-board LED, near pin 13, will light up when the current test is complete.
// If you do not see any image, or the image is incorrect, press the Arduino's RESET button.
// The sketch will move forward and test the next display.
// If after several seconds, the orange on-board LED does not light up, your display may have become stuck,
// or the sketch may have tested all possible displays.
// In either case, you should completely disconnect your Arduino and display module from their power source
// for 10 seconds.
// This will reset both the display, and the sketch, allowing the test to return to the start.

// ---------------------------------------------------------

#include "heltec-eink-modules.h"
#include "tests.h"

// Non-standard gcc feature - don't initialize the variable: we're using it to detect a cold boot
__attribute__((section(".noinit"))) uint32_t state;


void setup() {
    // If our unitialized memory hack reports an abnormal value, user probably unplugged the board
    if (state > 6) state = 0;

    // Seems to make SPI play nice, after we forced the CLK pin HIGH to use the LED on pin 13
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
    delay(1000);


    // Run the test code for the current display
    // Order is important - some displays will get "stuck" if initialized with wrong code
    switch (state) {
        case 0:
            test_gdep015oc1(PIN_DC, PIN_CS, PIN_BUSY);
            break;
        case 1:
            test_gde029a1(PIN_DC, PIN_CS, PIN_BUSY);
            break;
        case 2:
            test_qyeg0213rws800(PIN_DC, PIN_CS, PIN_BUSY);
            break;              
        case 3:
            test_depg0154bns800(PIN_DC, PIN_CS, PIN_BUSY);
            break;
        case 4:
            test_depg0150bns810(PIN_DC, PIN_CS, PIN_BUSY);
            break;
        case 5:
            test_depg0290bns800(PIN_DC, PIN_CS, PIN_BUSY);
            break;
        case 6:
            test_depg0290bns75a(PIN_DC, PIN_CS, PIN_BUSY);
            break;
        default:
            // If all the modes have been tested, don't light the LED - force the user to hard reboot
            return;     
    }

    // This variable will persist across resets, but will clear on a full unplug / replug reboot.
    state += 1;

    // Light the onboard LED to indicate completion
    SPI.end();
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
}

void loop() {
    
}
