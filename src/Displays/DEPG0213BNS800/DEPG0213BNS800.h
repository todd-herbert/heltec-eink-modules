#include <Arduino.h>
#include "Displays/BaseDisplay/base.h"

// Heltec Wireless Paper
// Connector label: FPC-7528B
class DEPG0213BNS800 : public BaseDisplay {

    // Display Config
    // ======================
    private:
        static const uint16_t panel_width = 128;                                    // Display width
        static const uint16_t panel_height = 250;                                   // Display height
        static const uint16_t drawing_width = 122;                                  // Usable width
        static const uint16_t drawing_height = 250;                                 // Usable height
        static const Color supported_colors = (Color) ( BLACK | WHITE );            // Colors available for drawing

    // Constructors
    // ======================
    public:

        #ifdef WIRELESS_PAPER
            DEPG0213BNS800(uint16_t page_height = DEFAULT_PAGE_HEIGHT) : BaseDisplay(PIN_PCB_DC, PIN_PCB_CS, PIN_PCB_BUSY, DEFAULT_SDI, DEFAULT_CLK, page_height)
                { init(); }

        #else
            /* --- ERROR: This display is only used by "Wireless Paper" boards --- */   DEPG0213BNS800(uint16_t page_height = DEFAULT_PAGE_HEIGHT) = delete;
        #endif


    // Look up tables
    // ==========================
    private:
        PROGMEM static constexpr uint8_t lut_partial[153] = {
            #include "lut_partial.inc"
        };


    // Setup
    // ==========================
    private:
        void init();        // Once instantiated, pass config to base


    // Virtual methods
    // ==========================
    public:
        #ifdef WIRELESS_PAPER
            void sleep();
            void wake();
        #endif
    private:
        void calculateMemoryArea( int16_t &sx, int16_t &sy, int16_t &ex, int16_t &ey );
        void configPartial();           // Configure panel to use partial refresh
        void configFull();
        void activate();


    // // Disabled methods
    // // ==========================
    // private:
    //     /* --- Error: Display does not support fastmode (partial refresh) --- */        void fastmodeOn() {}
    //     /* --- Error: Display does not support fastmode (partial refresh) --- */        void fastmodeTurbo() {}
};