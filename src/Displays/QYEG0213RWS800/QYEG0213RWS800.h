#include <Arduino.h>
#include "Displays/BaseDisplay/base.h"

// Heltec 2.9" V2
// Connector label: FPC-7528
class QYEG0213RWS800 : public BaseDisplay {

    // Display Config
    // ======================
    private:
        const uint16_t panel_width = 128;                                    // Display width
        const uint16_t panel_height = 250;                                   // Display height
        const uint16_t drawing_width = 122;                                  // Usable width
        const uint16_t drawing_height = 250;                                 // Usable height
        const Color supported_colors = (Color) ( BLACK | WHITE | RED );      // Colors available for drawing


    // Constructors
    // ======================
    public:

        // UNO-style constructor
        QYEG0213RWS800(  uint8_t pin_dc, uint8_t pin_cs, uint8_t pin_busy, uint16_t page_height = DEFAULT_PAGE_HEIGHT)
            : BaseDisplay ( pin_dc, pin_cs, pin_busy, DEFAULT_SDI, DEFAULT_CLK, page_height) 
                { init(); }

        // Full pinout constructor
        #if CAN_SPECIFY_SPI_PINS
            QYEG0213RWS800(  uint8_t pin_dc, uint8_t pin_cs, uint8_t pin_busy, uint8_t pin_sdi, uint8_t pin_clk, uint16_t page_height = DEFAULT_PAGE_HEIGHT)
                : BaseDisplay ( pin_dc, pin_cs, pin_busy, pin_sdi, pin_clk, page_height)
                    { init(); }

        #else
            // If UNO uses full constructor
            /* --- ERROR: Your board's SPI pinout cannot be customized --- */   QYEG0213RWS800( uint8_t pin_dc, uint8_t pin_sdi, uint8_t pin_cs, 
                                                                                                uint8_t pin_clk, uint8_t pin_busy, 
                                                                                                uint16_t page_height ) = delete;
        #endif     

    // Disabled methods
    // =========================
    private:
        using BaseDisplay::fastmodeOff;
        using BaseDisplay::fastmodeOn;
        using BaseDisplay::fastmodeTurbo;


    // Setup
    // ==========================     
    private:
        void init();        // Once instantiated, pass config to base


    // Virtual methods
    // =========================
    public:
        void specifyMemoryArea( int16_t &sx, int16_t &sy, int16_t &ex, int16_t &ey );
    private:
        void configFull();
        void activate();
};