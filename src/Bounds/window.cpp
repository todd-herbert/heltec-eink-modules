#include "window.h"

// Helper methods to find window bounds
// ======================================

uint16_t WindowBounds::top() {
    return getWindowBounds(T);
}

uint16_t WindowBounds::right() {
    return getWindowBounds(R);
}

uint16_t WindowBounds::bottom() {
    return getWindowBounds(B);
}

uint16_t WindowBounds::left() {
    return getWindowBounds(L);
}

uint16_t WindowBounds::getWindowBounds(WindowBounds::side request) {

    // Boolean LUT (x:side, y:rotation): after considering rotation, does requested edge need to measure from opposite edge.
    static const uint8_t rotswap_lut[4] = { B0000,
                                            B0101,
                                            B1111,
                                            B1010 };

    // Handle setFlip() - first part
    // If flipping, we need to find the opposite edge, and right at the end, measure from the opposite side
    if ( (request % 2) && (*imgflip & Flip::HORIZONTAL) ) {  // If we're flipping horizontal, and this edge needs flipping
        request = (WindowBounds::side)((request + 2) % 4);
    }
    if ( !(request % 2) && (*imgflip & Flip::VERTICAL) ) {  // If vertical flip
        request = (WindowBounds::side)((request + 2) % 4);      
    } // -------------- End Flip Part 1 -----------

    uint16_t rotated_request = (request + *rotation) % 4;    // Rotate the WindowBounds::side value
    uint16_t result;    // Build in this varaible    

    // Given our request side and rotation, do we need to measure from opposite edge
    bool rotswap = rotswap_lut[*rotation] & (1 << request);

    // Start by simply picking a rotated edge
    result = *edges[rotated_request];

    // If required by LUT, find display width or height, and subtract the edge distance
    if (rotswap) {
        uint16_t minuend = (rotated_request % 2) ? (drawing_width - 1) : (drawing_height - 1);
        result = minuend - result;
    }

    // Handle setFlip() - 2nd part
    if ( (request % 2) && (*imgflip & Flip::HORIZONTAL) ) {  // If we're flipping horizontal, and this edge needs flipping
        uint16_t minuend = (rotated_request % 2) ? (drawing_width - 1) : (drawing_height - 1);
        result = minuend - result;
    }
    if ( !(request % 2) && (*imgflip & Flip::VERTICAL) ) {  // If vertical flip
        uint16_t minuend = (rotated_request % 2) ? (drawing_width - 1) : (drawing_height - 1);
        result = minuend - result;    
    } // ----------- end flip part 2 -------------

    return result;
}