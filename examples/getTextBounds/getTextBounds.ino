// Which panel are you using?  (uncomment one)
// --------------------------------------------
    // #define	USING_DEPG0150BNS810		// 1.54" V2 - BW - Reb Tab
    // #define	USING_DEPG0154BNS800		// 1.54" V2 - BW - Red Tab
    // #define	USING_GDEP015OC1			// 1.54" V2 - BW - Blue Tab
    // #define	USING_QYEG0213RWS800		// 2.13" V2 - BWR - Red Tab
    // #define	USING_DEPG0290BNS75A		// 2.9" V2 - BW - Red Tab
    // #define  USING_DEPG0290BNS800        // 2.9" V2 - BW - Red Tab
    // #define	USING_HTE029A1              // 2.9" V2 - BW - Blue Tab


// Where is your panel connected?
// --------------------------------
    #define DC_PIN 8
    #define CS_PIN 10
    #define BUSY_PIN 7


// (Example automatically picks the correct class and sample text)
#if     defined USING_DEPG0150BNS810
    #define		PANEL_CLASS     DEPG0150BNS810
    #define		SAMPLE_TEXT		"Fancy fonty text."
#elif   defined USING_DEPG0154BNS800
    #define		PANEL_CLASS     DEPG0154BNS800  
    #define		SAMPLE_TEXT		"Fancy font."   // Display too small
#elif   defined USING_GDEP015OC1
    #define     PANEL_CLASS     GDEP015OC1
    #define		SAMPLE_TEXT		"Fancy fonty text."  
#elif   defined USING_QYEG0213RWS800
    #define		PANEL_CLASS     QYEG0213RWS800
    #define		SAMPLE_TEXT		"Fancy fonty text."    
#elif   defined USING_DEPG0290BNS75A
    #define		PANEL_CLASS     DEPG0290BNS75A
    #define		SAMPLE_TEXT		"Fancy fonty text."
#elif   defined USING_DEPG0290BNS800
    #define     PANEL_CLASS     DEPG0290BNS800
    #define		SAMPLE_TEXT		"Fancy fonty text."   
#elif   defined USING_HTE029A1
    #define		PANEL_CLASS     HTE029A1
    #define		SAMPLE_TEXT		"Fancy fonty text."
#endif

    
// DEMO: Placing text accurately with getTextBounds()
// ---------------------------------------------------
    // NOTE: THIS FUNCTION DOES NOT APPEAR TO WORK CORRECTLY WITH THE BUILT-IN FALLBACK FONT
    // So be sure to use setFont()!
    // This is an error in GFX_Root and not an error with the Heltec_213R_V2 library

#include "heltec-eink-modules.h"

#include "Fonts/FreeSerifBoldItalic9pt7b.h"   // Include the particular font

PANEL_CLASS display(DC_PIN, CS_PIN, BUSY_PIN);

void setup() {
    display.begin();

    display.setRotation(display.orientation.PINS_LEFT);  // Landscape

    display.setFont( &FreeSerifBoldItalic9pt7b );   // Pass (the address of) the font to the library
    const char text[] = SAMPLE_TEXT;

    // Precisely place our text using getTextBounds()
    // -----------------------------------------------


    int16_t text_top_edge; // These will receive information about how much space our text will take up 
    int16_t text_left_edge;
    uint16_t text_width;
    uint16_t text_height;
    
    // This will tell us where the bounds of the text would be, if we setCursor(0,0) and then print(text)
    // Note that the variables are passed by reference
    display.getTextBounds(text, 0, 0, &text_left_edge, &text_top_edge, &text_width, &text_height);

    // We can use this information in our loop to help place the string
    // We'll show off and align our text right
    // setCursor()'s Y value is the imaginary line that the characters sit on. In this case, slightly above the base of the screen
    uint16_t cursor_demo_x = display.bounds.full.right() - text_width - 5;	// 5px safety margin
    uint16_t cursor_demo_y = display.bounds.full.bottom() - 30;



    // Graphics GO!
    // -------------

    while( display.calculating() ) {

        display.setCursor(cursor_demo_x, cursor_demo_y);          
        display.print(text);

        // Lets draw a line across the screen at cursor height, to really make the point clear
        display.drawLine(0, cursor_demo_y, display.bounds.full.right(), cursor_demo_y, display.colors.BLACK);
        
    }

        display.update();   // The display will only begin to change once update() is called
}

void loop() { }

// ===============================================================
// Note: other methods to help with text-placement include:
//      setCursorTopLeft()  -   Put text by top / left
//      getTextWidth()
//      getTextHeight()
// ===============================================================