#ifndef __TESTS_H__
#define __TESTS_H__

// Contains the functions for drawing a test image to each different model of display

#include <heltec-eink-modules.h>

void test_depg0150bns810(uint8_t dc, uint8_t cs, uint8_t busy) {
    DEPG0150BNS810 display( dc, cs, busy );

    static const char MODEL[] = "DEPG0150BNS810";
    display.setTextSize(2);

    uint16_t L, T, R, B, W, H;
    L = display.bounds.full.left();
    T = display.bounds.full.top();
    R = display.bounds.full.right();
    B = display.bounds.full.bottom();
    W = display.bounds.full.width();
    H = display.bounds.full.height();

    while(display.calculating()) {
        // Border
        display.drawRect( L, T, W, H, display.colors.BLACK );      
        // Cross           
        display.drawLine( L, T, R, B, display.colors.BLACK );  
        display.drawLine( L, B, R, T, display.colors.BLACK );
        // Label
        display.setCursor(  display.bounds.full.centerX() - (display.getTextWidth(MODEL) / 2), 
                            H / 4 );
        display.print(MODEL);
    }
    display.update();
}

void test_depg0154bns800(uint8_t dc, uint8_t cs, uint8_t busy) {
    DEPG0154BNS800 display( dc, cs, busy );

    display.setTextSize(2);

    uint16_t L, T, R, B, W, H;
    L = display.bounds.full.left();
    T = display.bounds.full.top();
    R = display.bounds.full.right();
    B = display.bounds.full.bottom();
    W = display.bounds.full.width();
    H = display.bounds.full.height();

    while(display.calculating()) {
        // Border
        display.drawRect( L, T, W, H, display.colors.BLACK );      
        // Cross           
        display.drawLine( L, T, R, B, display.colors.BLACK );  
        display.drawLine( L, B, R, T, display.colors.BLACK );
        // Label
        display.setCursor( L + 10, 10 );
        display.println("DEPG0154");
        display.setCursor( L + 10, display.getCursorY() );
        display.print("BNS800");
    }
    display.update();
}

void test_gdep015oc1(uint8_t dc, uint8_t cs, uint8_t busy) {
    GDEP015OC1 display( dc, cs, busy );

    static const char MODEL[] = "GDEP015OC1";
    display.setTextSize(2);

    uint16_t L, T, R, B, W, H;
    L = display.bounds.full.left();
    T = display.bounds.full.top();
    R = display.bounds.full.right();
    B = display.bounds.full.bottom();
    W = display.bounds.full.width();
    H = display.bounds.full.height();

    while(display.calculating()) {
        // Border
        display.drawRect( L, T, W, H, display.colors.BLACK );      
        // Cross           
        display.drawLine( L, T, R, B, display.colors.BLACK );  
        display.drawLine( L, B, R, T, display.colors.BLACK );
        // Label
        display.setCursor(  display.bounds.full.centerX() - (display.getTextWidth(MODEL) / 2), 
                            H / 4 );
        display.print(MODEL);
    }
    display.update();
}

void test_qyeg0213rws800(uint8_t dc, uint8_t cs, uint8_t busy) {
    QYEG0213RWS800 display( dc, cs, busy );

    display.setRotation(display.orientation.PINS_LEFT);

    static const char MODEL[] = "QYEG0213RWS800";
    display.setTextSize(2);

    uint16_t L, T, R, B, W, H;
    L = display.bounds.full.left();
    T = display.bounds.full.top();
    R = display.bounds.full.right();
    B = display.bounds.full.bottom();
    W = display.bounds.full.width();
    H = display.bounds.full.height();

    while(display.calculating()) {
        // Border
        display.drawRect( L, T, W, H, display.colors.BLACK );      
        // Cross           
        display.drawLine( L, T, R, B, display.colors.BLACK );  
        display.drawLine( L, B, R, T, display.colors.BLACK );
        // Label
        display.setCursor(  display.bounds.full.centerX() - (display.getTextWidth(MODEL) / 2), 
                            H / 4 );
        display.print(MODEL);
    }
    display.update();
}

void test_depg0290bns75a(uint8_t dc, uint8_t cs, uint8_t busy) {
   DEPG0290BNS75A display( dc, cs, busy );

    display.setRotation(display.orientation.PINS_LEFT);

    static const char MODEL[] = "DEPG0290BNS75A";
    display.setTextSize(2);

    uint16_t L, T, R, B, W, H;
    L = display.bounds.full.left();
    T = display.bounds.full.top();
    R = display.bounds.full.right();
    B = display.bounds.full.bottom();
    W = display.bounds.full.width();
    H = display.bounds.full.height();

    while(display.calculating()) {
        // Border
        display.drawRect( L, T, W, H, display.colors.BLACK );      
        // Cross           
        display.drawLine( L, T, R, B, display.colors.BLACK );  
        display.drawLine( L, B, R, T, display.colors.BLACK );
        // Label
        display.setCursor(  display.bounds.full.centerX() - (display.getTextWidth(MODEL) / 2), 
                            H / 4 );
        display.print(MODEL);
    }
    display.update();
}

void test_depg0290bns800(uint8_t dc, uint8_t cs, uint8_t busy) {
   DEPG0290BNS800 display( dc, cs, busy );

    display.setRotation(display.orientation.PINS_LEFT);

    static const char MODEL[] = "DEPG0290BNS800";
    display.setTextSize(2);

    uint16_t L, T, R, B, W, H;
    L = display.bounds.full.left();
    T = display.bounds.full.top();
    R = display.bounds.full.right();
    B = display.bounds.full.bottom();
    W = display.bounds.full.width();
    H = display.bounds.full.height();

    while(display.calculating()) {
        // Border
        display.drawRect( L, T, W, H, display.colors.BLACK );      
        // Cross           
        display.drawLine( L, T, R, B, display.colors.BLACK );  
        display.drawLine( L, B, R, T, display.colors.BLACK );
        // Label
        display.setCursor(  display.bounds.full.centerX() - (display.getTextWidth(MODEL) / 2), 
                            H / 4 );
        display.print(MODEL);
    }
    display.update();
}

void test_hte029a1(uint8_t dc, uint8_t cs, uint8_t busy) {
    HTE029A1 display( dc, cs, busy );

    display.setRotation(display.orientation.PINS_LEFT);

    static const char MODEL[] = "HTE029A1";
    display.setTextSize(2);

    uint16_t L, T, R, B, W, H;
    L = display.bounds.full.left();
    T = display.bounds.full.top();
    R = display.bounds.full.right();
    B = display.bounds.full.bottom();
    W = display.bounds.full.width();
    H = display.bounds.full.height();

    while(display.calculating()) {
        // Border
        display.drawRect( L, T, W, H, display.colors.BLACK );      
        // Cross           
        display.drawLine( L, T, R, B, display.colors.BLACK );  
        display.drawLine( L, B, R, T, display.colors.BLACK );
        // Label
        display.setCursor(  display.bounds.full.centerX() - (display.getTextWidth(MODEL) / 2), 
                            H / 4 );
        display.print(MODEL);
    }
    display.update();
}


#endif