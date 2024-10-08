/* 
    File: lut_partial.inc

        - Lookup table for E-ink display
            Model: DEPG0154BNS800
            Refresh: Partial

            Source: Custom (Referencing Heltec Link)
            https://github.com/HelTecAutomation/Wireless-Paper/blob/ac5e7004309d9384c098e494d613f77c882d1d3c/src/DEPG0154BxS800FxX_BW.h#L17

            1. Tap existing black pixels into place - helps when initially moving into fastmode
            2. Move new pixels into place - long
            3. New pixels + old black pixels - short
            4. All pixels together - v. short, then cooldown (crucial!)

            Last adjusted: 2024-2-27
*/

0x40, 0x00, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     // B2B
0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     // B2W
0x00, 0x40, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     // W2B
0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     // W2W
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     // VCOM
0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00 