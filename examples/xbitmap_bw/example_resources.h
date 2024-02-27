/*
    This file only exists to make the example simpler to run
    It picks the class name and image size to suit your display

    Normally, you would have written something like this instead:

    #include "pencils_200x200.h"
    DEPG0150BNS810 display(2, 4, 5);    // Pins for DC, CS, BUSY
*/

#if defined USING_DEPG0150BNS810
    #define     DISPLAY_CLASS       DEPG0150BNS810    
    #define     CHESS_H             "chess_200x200.h"

#elif defined USING_DEPG0154BNS800
    #define     DISPLAY_CLASS       DEPG0154BNS800
    #define     CHESS_H             "chess_152x152.h"

#elif defined USING_GDEP015OC1
    #define     DISPLAY_CLASS       GDEP015OC1
    #define     CHESS_H             "chess_200x200.h"

#elif defined USING_DEPG0213RWS800
    #define     DISPLAY_CLASS       QYEG0213RWS800    
    #define     CHESS_H             "chess_250x122.h"    

#elif defined USING_QYEG0213RWS800
    #define     DISPLAY_CLASS       QYEG0213RWS800    
    #define     CHESS_H             "chess_250x122.h"

#elif defined USING_DEPG0290BNS75A
    #define     DISPLAY_CLASS       DEPG0290BNS75A    
    #define     CHESS_H             "chess_296x128.h"

#elif defined USING_DEPG0290BNS800
    #define     DISPLAY_CLASS       DEPG0290BNS800   
    #define     CHESS_H             "chess_296x128.h"

#elif defined USING_GDE029A1
    #define     DISPLAY_CLASS       GDE029A1    
    #define     CHESS_H             "chess_296x128.h"

#elif defined USING_DEPG0213BNS800
    #define     DISPLAY_CLASS       DEPG0213BNS800
    #define     CHESS_H             "chess_250x122.h"

#elif defined USING_LCMEN2R13EFC1
    #define     DISPLAY_CLASS       LCMEN2R13EFC1  
    #define     CHESS_H             "chess_250x122.h"  

#endif