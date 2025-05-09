// XBitmap Image used in example: "xbitmap_bw.ino"
// Image description: "chessboard"

// See https://github.com/todd-herbert/heltec-eink-modules/blob/main/docs/XBitmapTutorial/README.md

#define chess_width 296
#define chess_height 128
PROGMEM const static unsigned char chess_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x07, 0xc0, 0x0f,
   0x00, 0xfc, 0xf0, 0x07, 0xf0, 0x07, 0x3c, 0xe0, 0x07, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x07, 0xe0,
   0x0f, 0x00, 0xfe, 0xf0, 0x07, 0xf8, 0x07, 0x3d, 0xc0, 0x03, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x07,
   0xc0, 0x0f, 0x00, 0xfc, 0xf1, 0x07, 0xf0, 0x0f, 0x7f, 0xc0, 0x03, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
   0x03, 0xe0, 0x0f, 0x00, 0xfc, 0xf1, 0x07, 0xfc, 0x8f, 0x3f, 0xe0, 0x07,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x80, 0x07, 0xc0, 0x1f, 0x00, 0xfc, 0xe3, 0x07, 0xd0, 0x4f, 0x3f, 0xe0,
   0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xc0, 0x0f, 0xe0, 0x1f, 0x00, 0xfe, 0xc0, 0x01, 0xdc, 0x8f, 0x3e,
   0xc0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xc0, 0x0f, 0xc0, 0x3f, 0x00, 0xf8, 0xc0, 0x01, 0xf8, 0x9f,
   0x7e, 0xc1, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xc0, 0x1f, 0xf0, 0x3f, 0x00, 0x7c, 0xe0, 0x03, 0xf0,
   0xe7, 0x7f, 0xca, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xc0, 0x1f, 0xe0, 0x3f, 0x00, 0xf8, 0xc0, 0x1f,
   0xf0, 0x9f, 0xff, 0xe9, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1f, 0xc0, 0x0f, 0x00, 0xfc, 0x60,
   0x1e, 0xf1, 0xff, 0xff, 0xe7, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0xe0, 0x3f, 0x80, 0x0f, 0x00, 0xfc,
   0xe0, 0x7f, 0xca, 0xff, 0xfe, 0xe7, 0x5f, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x80, 0x0d, 0x00, 0xe0, 0x3f, 0x80, 0x0f, 0x00,
   0xfc, 0xf8, 0x3f, 0xfd, 0x7f, 0xfe, 0xff, 0x87, 0x02, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x1f, 0x00, 0xe0, 0x3f, 0x80, 0x0f,
   0x00, 0xfe, 0xe1, 0xbf, 0xfc, 0x4f, 0xff, 0xf2, 0xbf, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0xe0, 0x3f, 0x80,
   0x0f, 0xc0, 0xff, 0xf1, 0x3f, 0xfd, 0x3f, 0x7f, 0xfd, 0xaf, 0x2a, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0xe0, 0x3f,
   0x80, 0x1f, 0x80, 0xff, 0xf7, 0x7f, 0xd8, 0x3f, 0x7f, 0xf9, 0x6f, 0xd5,
   0x2a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0f, 0x03, 0xc0,
   0x3f, 0xc0, 0x1f, 0xe0, 0xff, 0x7b, 0xbe, 0xea, 0xff, 0xff, 0xd2, 0x5f,
   0xff, 0xa5, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x03,
   0xe0, 0x3f, 0xc0, 0x3f, 0xe0, 0xff, 0xff, 0xff, 0xea, 0xff, 0xff, 0x17,
   0xa0, 0xff, 0xaf, 0x2a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
   0x03, 0xc0, 0x1f, 0xa0, 0x3f, 0xe0, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xff,
   0x7f, 0xf5, 0xff, 0x7f, 0x45, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xfe, 0x03, 0x00, 0x0f, 0x60, 0x7f, 0xe8, 0xff, 0xff, 0xff, 0xe7, 0xff,
   0xff, 0xff, 0xfd, 0xff, 0xff, 0x5f, 0x2a, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xff, 0x03, 0x80, 0x0f, 0x00, 0x7f, 0xe5, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xfa, 0xff, 0xff, 0xa2, 0x42, 0x01, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8,
   0x00, 0x00, 0xfe, 0x03, 0x00, 0x1f, 0xe0, 0xff, 0x88, 0xff, 0xff, 0xfe,
   0xf7, 0xff, 0xff, 0xbf, 0x45, 0xff, 0xbf, 0x4a, 0x1a, 0x15, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x01, 0x05, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x80,
   0xff, 0x03, 0x00, 0xff, 0x01, 0x80, 0x1f, 0xd0, 0xff, 0xea, 0xff, 0xf7,
   0xff, 0xfe, 0xdf, 0xff, 0x43, 0xb5, 0xfa, 0x2f, 0x24, 0xa1, 0xa0, 0x02,
   0x00, 0x00, 0x00, 0x80, 0x40, 0x05, 0x00, 0xae, 0x00, 0x00, 0x00, 0x00,
   0x80, 0xff, 0x03, 0x00, 0xff, 0x03, 0x80, 0x3f, 0xd0, 0xff, 0xe9, 0xff,
   0x0f, 0xff, 0xfa, 0xbf, 0xfa, 0x94, 0x54, 0xa5, 0x4b, 0x49, 0x04, 0x15,
   0x14, 0x00, 0x00, 0x00, 0x80, 0x80, 0x0e, 0x00, 0x28, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xff, 0x03, 0x00, 0xff, 0x03, 0x00, 0x3f, 0xc8, 0xff, 0xf1,
   0xff, 0xbf, 0x7f, 0xa9, 0xdf, 0x2b, 0x21, 0x41, 0x55, 0x2b, 0x22, 0x51,
   0xfa, 0xa2, 0x00, 0x00, 0x80, 0x40, 0x41, 0x05, 0x00, 0x52, 0x02, 0x00,
   0x00, 0x00, 0x80, 0xff, 0x03, 0x00, 0xff, 0x07, 0x80, 0xff, 0xf2, 0xff,
   0xc5, 0xff, 0xff, 0xff, 0x49, 0xb0, 0xfe, 0x2b, 0x15, 0xd1, 0xdf, 0x24,
   0x84, 0xfe, 0x8f, 0x2a, 0x00, 0x80, 0x43, 0x81, 0x2d, 0x80, 0xe8, 0x02,
   0x00, 0x00, 0x00, 0x80, 0xff, 0x03, 0x00, 0xff, 0x0f, 0xfe, 0x7f, 0x34,
   0xff, 0xd7, 0xff, 0xff, 0xff, 0x12, 0x45, 0xff, 0xaf, 0xa8, 0xfa, 0x7f,
   0x89, 0xd2, 0xff, 0xbf, 0x40, 0x01, 0x40, 0x02, 0x40, 0x2b, 0x20, 0xb5,
   0x01, 0x00, 0x00, 0x00, 0x00, 0xff, 0x03, 0x00, 0xff, 0x0f, 0xfe, 0xff,
   0x75, 0xff, 0xdf, 0xbf, 0xff, 0xff, 0x17, 0xc0, 0xff, 0xff, 0x25, 0xfd,
   0xff, 0x2f, 0xe8, 0xff, 0xff, 0x1f, 0x15, 0xa0, 0x05, 0x50, 0x55, 0x20,
   0xb5, 0x03, 0x00, 0x00, 0x00, 0x00, 0xff, 0x03, 0x80, 0xfe, 0x9f, 0xff,
   0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xfa, 0xff, 0xff, 0xab,
   0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0x6f, 0xa5, 0xa0, 0x02, 0xe8, 0x2a,
   0x50, 0x7d, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x07, 0x80, 0xfe, 0x8f,
   0xff, 0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff,
   0xdf, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0x8b, 0xaa, 0xa2, 0x02, 0x88,
   0x57, 0x55, 0xf1, 0x01, 0x00, 0x00, 0x00, 0x00, 0xff, 0x07, 0x00, 0xfd,
   0xcf, 0xff, 0xff, 0xf7, 0xff, 0xef, 0xff, 0xff, 0xff, 0x7f, 0xf9, 0xff,
   0xff, 0x0b, 0xfe, 0xff, 0x1f, 0x84, 0xff, 0xff, 0x55, 0x42, 0x50, 0x01,
   0x70, 0x55, 0x55, 0x5e, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x07, 0x00,
   0xf2, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0x7f, 0xa5,
   0xff, 0xff, 0xaa, 0xe0, 0xff, 0x5f, 0x01, 0xf4, 0x7f, 0x91, 0x80, 0x51,
   0x01, 0xa4, 0x56, 0xd5, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x03,
   0x00, 0xfe, 0xaf, 0xff, 0xff, 0x63, 0xff, 0xff, 0x7f, 0xf9, 0xff, 0xa5,
   0x55, 0xff, 0x3f, 0x11, 0x8a, 0xff, 0x01, 0x40, 0xd2, 0x9f, 0x2a, 0x50,
   0xa0, 0x02, 0xd5, 0xaa, 0x2a, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8,
   0x01, 0x1c, 0xfc, 0x3f, 0xfe, 0xff, 0xcf, 0xff, 0xf5, 0xff, 0xc5, 0x7f,
   0x24, 0x55, 0xf4, 0x5f, 0xa5, 0x10, 0xf4, 0xaa, 0x42, 0x04, 0x2c, 0x49,
   0x50, 0x51, 0x01, 0x5a, 0xab, 0x6a, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xf8, 0x01, 0x7e, 0xfc, 0xbf, 0xfe, 0xff, 0xff, 0xff, 0xf4, 0xff, 0x2a,
   0x07, 0x48, 0xa4, 0xd5, 0x23, 0x49, 0x45, 0x22, 0x01, 0x14, 0x51, 0xad,
   0x12, 0xa8, 0x50, 0x81, 0xf6, 0xaa, 0x1a, 0x0e, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xf0, 0x03, 0xfe, 0xfc, 0xbf, 0xff, 0xff, 0xdf, 0xff, 0xf5, 0xff,
   0x57, 0xae, 0x92, 0x24, 0x15, 0xaf, 0x2a, 0x49, 0xf4, 0x55, 0x21, 0x04,
   0xfe, 0x52, 0xa8, 0x51, 0x21, 0xad, 0xad, 0x32, 0x3c, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xf8, 0xc3, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xdf, 0xff, 0xd1,
   0xff, 0xdb, 0x5f, 0x4a, 0x92, 0xe8, 0x5f, 0x55, 0x95, 0xfe, 0x2f, 0x8a,
   0xd2, 0xff, 0x17, 0x2a, 0xa8, 0x10, 0x75, 0x4b, 0x2d, 0x0f, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xf8, 0x87, 0xff, 0xff, 0xff, 0xff, 0xf4, 0xdf, 0xff,
   0x05, 0x7d, 0xfb, 0xff, 0x92, 0x94, 0xfa, 0xff, 0x55, 0x25, 0xff, 0x7f,
   0x29, 0xe2, 0x3f, 0x74, 0x14, 0x50, 0x30, 0x6d, 0x5b, 0x35, 0x3c, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xf8, 0xcf, 0xff, 0xff, 0xff, 0x7f, 0x49, 0xff,
   0xff, 0x0b, 0xc0, 0xfe, 0xff, 0xaf, 0x22, 0xff, 0xff, 0x97, 0xd4, 0xff,
   0xff, 0x47, 0xfc, 0x1f, 0x34, 0x0a, 0x68, 0x11, 0xdd, 0x46, 0xaa, 0x1e,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xaa,
   0xef, 0xff, 0x3f, 0x94, 0xff, 0xff, 0x5f, 0xd5, 0xff, 0xff, 0x7f, 0xf5,
   0xff, 0xff, 0x5f, 0xfd, 0x0f, 0x2a, 0x08, 0x50, 0x17, 0x5a, 0xad, 0x2c,
   0x3d, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xbf, 0xff, 0xff, 0xff, 0xfe,
   0xf9, 0xff, 0xff, 0xff, 0xe9, 0xff, 0xff, 0xff, 0xfa, 0xff, 0xff, 0xff,
   0xfa, 0xff, 0xff, 0x7f, 0xfd, 0x07, 0x15, 0x04, 0xa8, 0x04, 0xb5, 0x42,
   0x5a, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xbf, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xff,
   0xff, 0xea, 0xff, 0xff, 0x5f, 0xd1, 0x0f, 0x35, 0x84, 0x49, 0x0d, 0x6d,
   0x57, 0x96, 0x7a, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x7f, 0xfe, 0xff,
   0x7f, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xf8, 0xff, 0xff, 0x7f, 0xe5, 0xff,
   0xff, 0x1f, 0x90, 0xff, 0xff, 0x17, 0x24, 0x47, 0x2d, 0x45, 0xb4, 0x02,
   0xb6, 0x92, 0x4a, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xbf, 0xd5, 0xff, 0xff, 0x5f, 0x0a,
   0xff, 0xff, 0xaf, 0x12, 0xf8, 0xff, 0xa7, 0x24, 0x44, 0x55, 0x8a, 0xd4,
   0x06, 0xea, 0x56, 0x4d, 0x7a, 0x15, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xd7, 0xff, 0xff, 0xd7, 0x2a, 0xff, 0xff, 0x43,
   0x69, 0xfd, 0xff, 0x15, 0x49, 0xe5, 0xff, 0x08, 0x41, 0x45, 0x15, 0x4a,
   0xac, 0x82, 0x5a, 0x45, 0x53, 0xbf, 0x52, 0x00, 0x00, 0x00, 0x00, 0xfe,
   0xff, 0xff, 0xff, 0xbf, 0xff, 0x1f, 0xfe, 0xff, 0x90, 0xaa, 0xf8, 0xff,
   0x15, 0x82, 0xc0, 0x7f, 0x51, 0x12, 0x04, 0xbe, 0x52, 0x90, 0xaa, 0x16,
   0x8a, 0x6a, 0x05, 0xd6, 0xda, 0x42, 0x75, 0x55, 0x05, 0x00, 0x00, 0xa0,
   0xfe, 0xff, 0xff, 0xff, 0xab, 0xff, 0xef, 0xf8, 0x2f, 0x4a, 0xaa, 0xe6,
   0x3f, 0x52, 0x29, 0x15, 0x5f, 0x4a, 0x49, 0x51, 0x19, 0x04, 0x54, 0x42,
   0x05, 0x4a, 0xdf, 0xd6, 0x5a, 0x68, 0xd3, 0x7f, 0x57, 0x05, 0x00, 0x00,
   0x08, 0xfe, 0xff, 0xfe, 0xff, 0xa2, 0xff, 0x9f, 0xc2, 0x0b, 0x88, 0xa0,
   0x54, 0xaf, 0x4a, 0x42, 0x20, 0x98, 0x12, 0x12, 0x05, 0xf9, 0x14, 0xa8,
   0x42, 0x1f, 0x8a, 0xaa, 0x95, 0xd6, 0x68, 0xa7, 0xfa, 0xae, 0x1a, 0x00,
   0x80, 0x02, 0xfe, 0xff, 0xff, 0x0f, 0x94, 0xff, 0xbf, 0xaa, 0x00, 0x40,
   0x48, 0xa5, 0x56, 0x92, 0x14, 0x10, 0x5d, 0xa4, 0x48, 0x28, 0xff, 0x01,
   0x56, 0x80, 0x00, 0x85, 0xb6, 0x86, 0x5d, 0xa8, 0xd5, 0x7f, 0x5b, 0x15,
   0x00, 0x00, 0x01, 0xfe, 0xff, 0xff, 0x5f, 0x80, 0xff, 0xff, 0xea, 0xab,
   0x00, 0x10, 0x89, 0xbf, 0xaa, 0x52, 0x05, 0xff, 0x89, 0x92, 0x42, 0xff,
   0x0f, 0xaa, 0x22, 0x18, 0x0d, 0xad, 0x0c, 0xd5, 0x68, 0x0f, 0xfe, 0xdb,
   0x35, 0x00, 0x00, 0x02, 0xfe, 0xff, 0xff, 0x7f, 0x80, 0xff, 0xbf, 0xfd,
   0x0f, 0x05, 0x4a, 0xf2, 0x7f, 0x95, 0x84, 0xf0, 0xff, 0x17, 0x44, 0xf4,
   0xff, 0x8f, 0xaa, 0x10, 0x96, 0x8a, 0x5a, 0x42, 0xbb, 0xda, 0x52, 0x61,
   0xb5, 0x56, 0x00, 0x00, 0x08, 0xfc, 0x7f, 0xff, 0xff, 0x03, 0xfa, 0xff,
   0xff, 0x7f, 0x80, 0x48, 0xfa, 0xff, 0x25, 0x29, 0xf5, 0xff, 0xff, 0x14,
   0xf1, 0xff, 0x8f, 0xaa, 0x22, 0x3a, 0x85, 0xb6, 0x84, 0xaa, 0xbb, 0xaf,
   0xaa, 0xaa, 0x5d, 0x00, 0x00, 0x10, 0xf4, 0xff, 0xff, 0xff, 0x07, 0x40,
   0xff, 0xff, 0xff, 0x55, 0xa2, 0xfe, 0xff, 0x5f, 0x42, 0xfe, 0xff, 0xff,
   0xa2, 0xfe, 0xff, 0x8f, 0x56, 0x00, 0xd5, 0x82, 0x2a, 0x42, 0x6b, 0xfd,
   0xff, 0x5a, 0x55, 0x35, 0x00, 0x00, 0xc0, 0xa0, 0xbf, 0xff, 0xff, 0x3f,
   0x00, 0xfc, 0xff, 0xff, 0x47, 0xca, 0xff, 0xff, 0xff, 0x4a, 0xff, 0xff,
   0xff, 0x97, 0xfe, 0xff, 0x5f, 0x55, 0x21, 0x96, 0x82, 0xee, 0x82, 0xd6,
   0xfa, 0xff, 0x5f, 0x55, 0x6d, 0x08, 0x00, 0x00, 0x51, 0xbe, 0xff, 0xff,
   0x3f, 0x80, 0xff, 0xff, 0xff, 0x9f, 0xf4, 0xff, 0xff, 0xff, 0xd1, 0xff,
   0xff, 0xff, 0xbf, 0xff, 0xff, 0x8f, 0xea, 0x40, 0x55, 0x01, 0x55, 0x43,
   0xad, 0xff, 0xff, 0x57, 0x55, 0x55, 0x50, 0x00, 0x00, 0x86, 0xfe, 0xff,
   0xff, 0xff, 0xc1, 0xff, 0xff, 0xff, 0x7f, 0xfd, 0xff, 0xff, 0xff, 0xf7,
   0xff, 0xff, 0xff, 0x2f, 0x7c, 0xfd, 0x87, 0x56, 0x20, 0xed, 0x01, 0x6d,
   0x41, 0x6b, 0xfd, 0xff, 0xb7, 0xaa, 0x3e, 0x28, 0x00, 0x00, 0xe8, 0xbf,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff,
   0xc1, 0xff, 0xff, 0xff, 0x8b, 0x12, 0xfa, 0x07, 0x2d, 0x10, 0xeb, 0x40,
   0x55, 0xa0, 0xd6, 0xfd, 0xff, 0x6d, 0xd5, 0x55, 0x50, 0x01, 0x00, 0xe0,
   0xbf, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xbf, 0xf8, 0xff, 0xff,
   0x7f, 0x01, 0xfe, 0xff, 0xff, 0x0b, 0x02, 0xea, 0x87, 0x2a, 0x20, 0xd6,
   0x01, 0xed, 0xa0, 0xb5, 0xfd, 0xff, 0xdb, 0x5b, 0xb7, 0xa8, 0x02, 0x00,
   0xc0, 0xff, 0xff, 0xff, 0x1f, 0x90, 0xff, 0xff, 0xff, 0x4b, 0xe5, 0xff,
   0xff, 0x1f, 0x00, 0xf8, 0xff, 0x7f, 0x50, 0x84, 0xea, 0x47, 0x15, 0x90,
   0xed, 0xa3, 0x5a, 0xa0, 0x6e, 0xff, 0xbf, 0xaa, 0xb6, 0x5d, 0xa0, 0x0a,
   0x00, 0x00, 0xff, 0xff, 0xff, 0x57, 0x25, 0xfe, 0xff, 0xff, 0x95, 0x0a,
   0xff, 0xff, 0x17, 0x00, 0xc0, 0xff, 0x5f, 0x85, 0x00, 0xd5, 0x4f, 0x35,
   0x00, 0x15, 0x4f, 0x55, 0xa0, 0x55, 0xf5, 0xbf, 0xaa, 0x6a, 0xfb, 0x50,
   0x15, 0x00, 0x00, 0x7e, 0xff, 0xff, 0xab, 0x4a, 0xf9, 0xff, 0x5f, 0x24,
   0xa9, 0xfc, 0xff, 0x01, 0x00, 0x00, 0xff, 0x07, 0x28, 0xa1, 0xaa, 0x47,
   0x0b, 0x8c, 0xab, 0xa4, 0x55, 0xa8, 0xd6, 0xab, 0x0f, 0x52, 0xb5, 0x5d,
   0x40, 0x55, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xaa, 0x54, 0xe2, 0xff, 0x97,
   0x24, 0x02, 0xf1, 0x7f, 0x01, 0x00, 0x00, 0xf8, 0xab, 0xa2, 0x42, 0x2b,
   0x42, 0x15, 0x80, 0x5e, 0x81, 0x16, 0xa0, 0xb5, 0xae, 0xac, 0x04, 0x6a,
   0xff, 0xa0, 0xaa, 0x00, 0x00, 0xe0, 0xff, 0x5f, 0x57, 0x95, 0xd4, 0xff,
   0x49, 0x02, 0x54, 0xca, 0x1f, 0x00, 0x00, 0x00, 0xe1, 0x04, 0x54, 0x51,
   0x95, 0x80, 0x0a, 0x40, 0xab, 0x42, 0x05, 0x5c, 0xeb, 0xb5, 0xab, 0xaa,
   0xda, 0xbf, 0x00, 0x55, 0x01, 0x00, 0x80, 0xfe, 0x51, 0x55, 0x55, 0x05,
   0x7e, 0x49, 0x00, 0x40, 0x00, 0x16, 0x00, 0x00, 0x00, 0x8a, 0x51, 0xa9,
   0xd2, 0xaa, 0x00, 0x3b, 0x40, 0x5b, 0x83, 0x0d, 0xe8, 0x5a, 0x6f, 0xab,
   0xaa, 0xb6, 0xff, 0x80, 0xaa, 0x02, 0x00, 0x80, 0x3f, 0x40, 0xaa, 0xaa,
   0x54, 0x0d, 0x22, 0x01, 0x00, 0x00, 0x03, 0x00, 0x00, 0x80, 0xf0, 0x87,
   0x4a, 0x51, 0x15, 0x60, 0x25, 0xa0, 0xad, 0xa2, 0x0a, 0x54, 0xd7, 0xd5,
   0x55, 0x55, 0xed, 0x5f, 0x00, 0x54, 0x0d, 0x00, 0x00, 0x0c, 0x00, 0x52,
   0x55, 0x25, 0xbc, 0x24, 0x00, 0x00, 0x40, 0x3f, 0x00, 0x00, 0x00, 0xfa,
   0x0f, 0x55, 0xa2, 0x55, 0x40, 0x55, 0x40, 0x7b, 0x41, 0x0b, 0x68, 0xb5,
   0xdd, 0xb6, 0xaa, 0xed, 0xff, 0x00, 0x54, 0x15, 0x00, 0x00, 0x10, 0x80,
   0x88, 0xaa, 0xd4, 0x3f, 0x00, 0x00, 0x00, 0xf0, 0xff, 0x00, 0x00, 0x50,
   0xff, 0xa1, 0x92, 0x50, 0x55, 0xa0, 0xaa, 0xa0, 0x55, 0xa0, 0x0a, 0xd4,
   0xaf, 0x72, 0xad, 0xaa, 0xf6, 0x5f, 0x00, 0x54, 0xb5, 0x00, 0x00, 0x60,
   0x00, 0x21, 0x92, 0xd2, 0xff, 0x03, 0x00, 0x00, 0xf4, 0xff, 0x07, 0x00,
   0x40, 0xff, 0xa0, 0x26, 0xc1, 0x77, 0xa0, 0xad, 0x41, 0xd7, 0xa0, 0x0b,
   0xa9, 0x5a, 0xb4, 0xaa, 0xd5, 0xfd, 0xff, 0x00, 0xa8, 0x4a, 0x00, 0x00,
   0x80, 0x00, 0x90, 0x24, 0xfc, 0xff, 0x03, 0x00, 0x00, 0xff, 0xff, 0x17,
   0x00, 0xd5, 0x7f, 0x50, 0x4d, 0xa0, 0x6a, 0x48, 0xd5, 0xb1, 0x2d, 0x60,
   0x85, 0x6a, 0xab, 0x4a, 0x55, 0x6d, 0xff, 0xab, 0x80, 0xa0, 0xaa, 0x02,
   0x00, 0x00, 0x03, 0x92, 0x84, 0xfe, 0xff, 0x1f, 0x00, 0x80, 0xff, 0xff,
   0xbf, 0x00, 0xf0, 0x7f, 0xd0, 0xfa, 0x52, 0x45, 0x54, 0xb5, 0x61, 0x5b,
   0x40, 0x0f, 0xda, 0x5a, 0x0c, 0x48, 0xd9, 0xfe, 0xbf, 0x00, 0x40, 0x55,
   0x05, 0x00, 0x00, 0x0c, 0x04, 0xa0, 0xff, 0xff, 0x7f, 0x00, 0xf0, 0xff,
   0xff, 0xff, 0xaa, 0xfe, 0x7f, 0xb4, 0xfa, 0xd2, 0x12, 0xe8, 0xeb, 0xa8,
   0x2a, 0xb0, 0x0a, 0x7d, 0xb7, 0x53, 0x11, 0xb5, 0xff, 0xd7, 0x00, 0x40,
   0x55, 0x15, 0x00, 0x00, 0x38, 0x08, 0xe8, 0xff, 0xff, 0xff, 0x01, 0xf8,
   0xff, 0xff, 0xff, 0x0b, 0xff, 0x7f, 0xd4, 0xf2, 0xa7, 0x52, 0xa8, 0xd6,
   0x69, 0x2b, 0xa0, 0x5d, 0xf2, 0xef, 0x57, 0x52, 0x75, 0xff, 0xbf, 0x00,
   0x00, 0x57, 0x55, 0x00, 0x00, 0x60, 0x00, 0xfe, 0xff, 0xff, 0xff, 0x07,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x5a, 0xf5, 0x61, 0x21, 0xa0,
   0x0a, 0xd0, 0x2e, 0xa8, 0x8a, 0x5d, 0xf5, 0x55, 0x25, 0xaf, 0xff, 0x6a,
   0x00, 0x00, 0x5d, 0x55, 0x01, 0x00, 0x80, 0x41, 0xff, 0xff, 0xff, 0xff,
   0xaf, 0xff, 0xff, 0xff, 0xff, 0x9f, 0xff, 0x7f, 0x74, 0xf5, 0xc1, 0xa3,
   0x00, 0xe0, 0xd0, 0x2a, 0x68, 0x3b, 0xff, 0xf7, 0xb6, 0x4a, 0xfa, 0xff,
   0xdf, 0x00, 0x10, 0x50, 0x55, 0x02, 0x00, 0x00, 0xd3, 0xff, 0xff, 0xff,
   0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0x27, 0xfe, 0x7f, 0xad, 0x7a, 0x50,
   0x29, 0x20, 0xad, 0xa8, 0x15, 0xd4, 0xea, 0xff, 0x7f, 0xab, 0xaa, 0xf7,
   0xff, 0x6a, 0x00, 0x00, 0xd0, 0xaa, 0x0a, 0x00, 0x00, 0xf8, 0xff, 0xff,
   0xff, 0xff, 0x07, 0xff, 0xff, 0xff, 0xff, 0x49, 0xf8, 0xff, 0xda, 0x7a,
   0x50, 0xe9, 0x25, 0xaa, 0x60, 0x1f, 0xb4, 0xea, 0xff, 0xff, 0xda, 0xaa,
   0xf6, 0xff, 0xde, 0x00, 0x00, 0xa8, 0xaa, 0x14, 0x00, 0x00, 0xf0, 0xff,
   0xff, 0xff, 0xff, 0x00, 0xfc, 0xff, 0xff, 0x7f, 0xa2, 0xea, 0x7f, 0xb4,
   0x3d, 0xd0, 0x28, 0xd5, 0x55, 0xd5, 0x12, 0xd4, 0xed, 0xff, 0x5f, 0xb7,
   0xed, 0xfd, 0xbf, 0xb5, 0x00, 0x00, 0x00, 0x57, 0x55, 0x00, 0x00, 0xc0,
   0xff, 0xff, 0xff, 0xbf, 0x00, 0xe0, 0xff, 0xff, 0x5f, 0x8a, 0x0a, 0x7f,
   0x68, 0x3b, 0xa8, 0xa9, 0xaa, 0xaa, 0xab, 0x06, 0x54, 0xdb, 0xff, 0x5f,
   0x55, 0xab, 0xfd, 0x7f, 0xaf, 0x00, 0x00, 0x80, 0x54, 0x55, 0x01, 0x00,
   0x00, 0xff, 0xff, 0xff, 0x0f, 0x00, 0xa0, 0xff, 0xff, 0x97, 0xb4, 0x54,
   0x3d, 0xb4, 0x0a, 0xb0, 0xa8, 0x55, 0x6b, 0xd1, 0x01, 0x68, 0xd5, 0xff,
   0xa3, 0xaa, 0xfa, 0xff, 0xd7, 0x7a, 0x00, 0x00, 0x00, 0x5a, 0x55, 0x05,
   0x00, 0x00, 0xfc, 0xff, 0xff, 0x0b, 0x00, 0x00, 0xfe, 0xff, 0x97, 0x24,
   0x25, 0x71, 0x68, 0x05, 0xd0, 0x51, 0x55, 0xd5, 0x51, 0x03, 0xd4, 0x36,
   0xfe, 0x0b, 0xaa, 0x56, 0xff, 0xdf, 0xd6, 0x00, 0x00, 0x00, 0x64, 0x55,
   0x0a, 0x00, 0x00, 0xf4, 0xff, 0xff, 0x00, 0x00, 0x00, 0xfd, 0xff, 0x20,
   0x55, 0x4a, 0x4a, 0xd6, 0x02, 0xaa, 0xaa, 0xaa, 0xaa, 0x68, 0x01, 0xb5,
   0xad, 0xfa, 0x50, 0xa9, 0xfa, 0xff, 0xb7, 0x5b, 0x00, 0x00, 0x00, 0xa0,
   0x55, 0x55, 0x00, 0x00, 0xe0, 0xff, 0xbf, 0x00, 0x00, 0x00, 0xe0, 0x7f,
   0xa5, 0x92, 0x48, 0x52, 0xb4, 0x06, 0xaa, 0x55, 0xd5, 0x5a, 0xd0, 0x07,
   0xb5, 0xaa, 0x62, 0x05, 0x89, 0xae, 0xff, 0xb7, 0xda, 0x00, 0x00, 0x00,
   0x40, 0x55, 0x95, 0x00, 0x00, 0x80, 0xff, 0x0f, 0x00, 0x00, 0x00, 0xd4,
   0x0f, 0x28, 0x05, 0x92, 0x04, 0x6a, 0x01, 0x5a, 0x4d, 0x55, 0x2b, 0xa8,
   0x8a, 0x6e, 0x5d, 0xad, 0xaa, 0xa4, 0xf5, 0x7f, 0xdd, 0xb6, 0x00, 0x00,
   0x00, 0x00, 0x56, 0x55, 0x05, 0x00, 0x00, 0xfe, 0x0b, 0x00, 0x00, 0x00,
   0x00, 0xaa, 0x4a, 0x01, 0x25, 0x29, 0xd8, 0x02, 0x74, 0x8b, 0xaa, 0x2a,
   0xb0, 0x0d, 0xda, 0xd5, 0x5a, 0x29, 0x29, 0xef, 0xff, 0xb5, 0xb5, 0x00,
   0x00, 0x00, 0x00, 0xad, 0xaa, 0x0a, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00,
   0x00, 0xaa, 0x07, 0x29, 0x40, 0x9b, 0x04, 0xb4, 0x02, 0xd5, 0x42, 0xb5,
   0x16, 0xe8, 0x86, 0x6a, 0xbb, 0x5d, 0x55, 0xd2, 0xf5, 0x7f, 0x6f, 0x57,
   0x00, 0x00, 0x00, 0x00, 0xb8, 0xaa, 0x12, 0x00, 0x00, 0xb0, 0x00, 0x10,
   0x00, 0x00, 0x80, 0xbf, 0x4a, 0x81, 0xaa, 0x14, 0xe8, 0x06, 0xaa, 0xa2,
   0x6a, 0x35, 0xd0, 0x1e, 0xdd, 0xb6, 0x5e, 0x55, 0x55, 0xf7, 0xff, 0x5a,
   0xdd, 0x00, 0x00, 0x00, 0x00, 0x61, 0x55, 0x55, 0x01, 0x00, 0x60, 0x00,
   0x00, 0x10, 0x00, 0xf5, 0x7f, 0x92, 0xb0, 0x2d, 0x02, 0x5a, 0x05, 0xd5,
   0xa0, 0xaa, 0x2a, 0x6e, 0x45, 0xb5, 0xdd, 0x6b, 0x55, 0xf5, 0xfe, 0xbb,
   0xf7, 0xaa, 0x00, 0x00, 0x00, 0x00, 0xa0, 0x55, 0x55, 0x02, 0x00, 0x80,
   0x03, 0x00, 0x02, 0x52, 0xf0, 0xff, 0x25, 0xa0, 0x55, 0x04, 0xb4, 0x8d,
   0xd4, 0x50, 0x55, 0x2d, 0xd8, 0x9d, 0x6a, 0x5f, 0x6f, 0xab, 0xaa, 0xfd,
   0xbf, 0xd6, 0xb6, 0x00, 0x00, 0x00, 0x00, 0x00, 0xab, 0xaa, 0x04, 0x00,
   0x00, 0x06, 0x40, 0xa9, 0x84, 0xfe, 0xff, 0x4b, 0x74, 0x2b, 0x02, 0x6d,
   0xd1, 0x0b, 0xa8, 0x5a, 0x2b, 0x6d, 0x2b, 0xf4, 0xeb, 0xd5, 0xaa, 0x7a,
   0xff, 0x77, 0xbb, 0x6d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5c, 0x55, 0x15,
   0x00, 0x00, 0x1c, 0x00, 0x02, 0x29, 0xff, 0xff, 0x9f, 0xd4, 0x56, 0x04,
   0x5a, 0x11, 0x9b, 0x28, 0x95, 0x1a, 0xd9, 0xee, 0x80, 0x5a, 0xbb, 0xad,
   0xd6, 0xfe, 0x6f, 0x6b, 0xdb, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa8, 0xaa,
   0x4a, 0x00, 0x00, 0x70, 0xa8, 0x54, 0xe4, 0xff, 0xff, 0x7f, 0xa8, 0x2a,
   0x07, 0xf5, 0xd4, 0x0d, 0xaa, 0x6a, 0x15, 0x76, 0xdb, 0x53, 0xf5, 0x56,
   0xdb, 0x7e, 0xff, 0xf5, 0x56, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb4,
   0x55, 0x55, 0x01, 0x00, 0xc0, 0x81, 0x48, 0xe9, 0xff, 0xff, 0xff, 0xb5,
   0x2a, 0x07, 0xad, 0xb0, 0x1f, 0xaa, 0x8a, 0x36, 0x6a, 0xdb, 0x17, 0x92,
   0x6a, 0xb5, 0xd5, 0xff, 0xaf, 0x6d, 0xb7, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x50, 0xad, 0x4a, 0x02, 0x00, 0x00, 0x2b, 0x25, 0xfa, 0xff, 0xff, 0xff,
   0xa9, 0xea, 0x43, 0xb5, 0xd4, 0x17, 0xaa, 0x6a, 0x4d, 0xdd, 0xf6, 0x7f,
   0xac, 0xaa, 0xd6, 0xfe, 0xff, 0x75, 0xdb, 0xaa, 0x00, 0x00, 0x00, 0x04,
   0x00, 0x00, 0xab, 0xaa, 0x0a, 0x00, 0x00, 0x2c, 0x49, 0xfe, 0xff, 0xff,
   0xff, 0x51, 0xd5, 0x47, 0xed, 0x04, 0x1f, 0xaa, 0xaa, 0x5a, 0xf5, 0xf6,
   0xff, 0x0d, 0xa8, 0xda, 0xea, 0xff, 0x77, 0xb7, 0xad, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x40, 0x57, 0x55, 0x15, 0x00, 0x80, 0x52, 0xa2, 0xff, 0xff,
   0xff, 0xff, 0xd1, 0xf6, 0x43, 0x5b, 0x54, 0xa0, 0x52, 0x55, 0x4b, 0xbf,
   0xff, 0xff, 0x53, 0xa5, 0x6a, 0xff, 0xbf, 0xda, 0x6a, 0x5b, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x7a, 0x55, 0x55, 0x00, 0x00, 0xd4, 0xe4, 0xff,
   0xff, 0xff, 0xff, 0xa1, 0xd5, 0x47, 0xfb, 0xd0, 0xa7, 0xaa, 0xaa, 0x8a,
   0xfe, 0xff, 0xff, 0x07, 0x88, 0xd4, 0xfa, 0xef, 0xdb, 0x5e, 0xd5, 0x00,
   0x00, 0x00, 0x20, 0x00, 0x00, 0xa8, 0x55, 0x55, 0x01, 0x40, 0xa1, 0xf9,
   0xff, 0xff, 0xff, 0xff, 0xdb, 0xf6, 0x97, 0x6e, 0xa8, 0x6a, 0x51, 0xd5,
   0x56, 0xff, 0xff, 0xff, 0xa8, 0x52, 0x75, 0xff, 0xbf, 0xb6, 0xf5, 0x2d,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc8, 0x56, 0x55, 0x05, 0x10, 0x0a,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xb3, 0xea, 0xbf, 0xed, 0xd0, 0xde, 0xa3,
   0xaa, 0x5d, 0xff, 0xff, 0xff, 0x4a, 0x12, 0xd5, 0xfe, 0xff, 0xad, 0x56,
   0xeb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa0, 0x55, 0x55, 0x09, 0x40,
   0x50, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xd3, 0xd6, 0xff, 0xff, 0x54, 0x5b,
   0x51, 0x55, 0xff, 0xff, 0xff, 0x7f, 0x95, 0xa4, 0xbe, 0xff, 0x5b, 0xdb,
   0xad, 0x56, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdf, 0xaa, 0x2a,
   0x40, 0x85, 0xe0, 0xff, 0xff, 0xff, 0xff, 0x51, 0x15, 0xff, 0xff, 0xd0,
   0x76, 0xa1, 0x7d, 0xfd, 0xff, 0xff, 0xff, 0xaa, 0x2a, 0xb5, 0xff, 0x77,
   0x5b, 0xed, 0xda, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x54, 0x55,
   0x55, 0x00, 0x28, 0xd5, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x56, 0xfe, 0xff,
   0xa8, 0xaa, 0xa0, 0xab, 0xfb, 0xff, 0xff, 0x5f, 0x55, 0xd5, 0xee, 0xff,
   0xdb, 0xb6, 0x55, 0xab, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x75,
   0x5b, 0x55, 0x01, 0x41, 0x14, 0xff, 0xff, 0xff, 0xff, 0xa0, 0x5d, 0xf0,
   0xff, 0xe9, 0xad, 0x81, 0xfe, 0xf6, 0xff, 0xff, 0x5f, 0xab, 0xaa, 0xba,
   0xff, 0xbb, 0x6d, 0xdd, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xa8, 0xaa, 0xaa, 0x02, 0x94, 0xa2, 0xfc, 0xff, 0xff, 0x7f, 0xd0, 0xaa,
   0xe4, 0xff, 0xd3, 0x76, 0xa0, 0xba, 0xc5, 0xff, 0xff, 0xb7, 0xaa, 0xea,
   0xf7, 0xbf, 0x76, 0xab, 0xab, 0x56, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xa8, 0x6b, 0x55, 0x15, 0x90, 0x0a, 0xf1, 0xff, 0xff, 0x3f, 0xa8,
   0xb7, 0x04, 0xff, 0xab, 0xdd, 0x80, 0x76, 0x8f, 0xfe, 0xff, 0xd7, 0x5a,
   0x55, 0xed, 0xff, 0x6e, 0x6d, 0xb5, 0xad, 0x00, 0x00, 0x00, 0x08, 0x00,
   0x00, 0x00, 0x00, 0x57, 0x55, 0x15, 0x24, 0x00, 0xea, 0xff, 0xff, 0x0f,
   0x74, 0xad, 0xa8, 0xfe, 0x57, 0x2b, 0x54, 0xad, 0x25, 0xfa, 0xff, 0xaa,
   0xb5, 0xfa, 0xfb, 0xbf, 0xdb, 0xd5, 0x56, 0x55, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x5c, 0xab, 0xaa, 0xa8, 0x00, 0x82, 0xff, 0xff,
   0x0b, 0xa8, 0xb5, 0x01, 0xf0, 0xd3, 0x1a, 0x54, 0xbb, 0xa5, 0xe4, 0xff,
   0xaa, 0xd6, 0x56, 0xfb, 0x7f, 0x5b, 0xb7, 0xd5, 0xaa, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x10, 0x74, 0x55, 0x55, 0x05, 0x80, 0x00, 0xfe,
   0xff, 0x01, 0x74, 0x6f, 0x0a, 0xd0, 0xa3, 0x17, 0xea, 0x56, 0x2b, 0xc9,
   0x3f, 0xaa, 0xaa, 0xfd, 0xfe, 0xbf, 0x6d, 0xad, 0xb6, 0xaa, 0x00, 0x00,
   0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0xe4, 0xb6, 0xaa, 0x0a, 0x80, 0x02,
   0xf8, 0xff, 0x00, 0xd4, 0x5a, 0x09, 0x80, 0xa3, 0x16, 0xd4, 0xf6, 0xae,
   0x12, 0xbd, 0x20, 0x55, 0xd5, 0xfe, 0x6f, 0xdb, 0x6d, 0x55, 0x55, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0xc8, 0x55, 0x55, 0x05, 0x00,
   0x00, 0xf0, 0x3f, 0x00, 0xb5, 0xb7, 0x26, 0x00, 0xd0, 0x0d, 0xa8, 0xad,
   0x55, 0x25, 0x0a, 0x95, 0x54, 0xbf, 0xff, 0xbb, 0xad, 0xda, 0xaa, 0xaa,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x6f, 0xad, 0x2a,
   0x00, 0x00, 0xc0, 0x1f, 0x00, 0x6a, 0xed, 0xad, 0x00, 0xa1, 0x1d, 0x68,
   0xfb, 0x5b, 0xad, 0x56, 0x20, 0x51, 0xb5, 0xff, 0x6b, 0xfb, 0xb6, 0x56,
   0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xd7, 0xaa,
   0x4a, 0x80, 0x00, 0x80, 0x07, 0x00, 0xda, 0x5b, 0x2b, 0x45, 0xd0, 0x16,
   0xaa, 0xad, 0xb6, 0x55, 0x8b, 0x4a, 0xaa, 0xef, 0xff, 0xbf, 0x55, 0x6b,
   0x55, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe,
   0x6a, 0x55, 0x01, 0x00, 0x00, 0x0e, 0x00, 0xb4, 0x76, 0x6b, 0x49, 0xa8,
   0x3d, 0x68, 0xfb, 0x6f, 0x55, 0x2b, 0x91, 0x64, 0xed, 0xff, 0x6b, 0x6f,
   0xad, 0xad, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x40,
   0xe8, 0xd6, 0xaa, 0x04, 0x00, 0x00, 0x18, 0x00, 0xed, 0xdb, 0xad, 0x2a,
   0xe8, 0x56, 0xaa, 0xd6, 0xd5, 0xed, 0x4a, 0x4a, 0xd9, 0xfb, 0xff, 0xde,
   0xda, 0x5d, 0x55, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00,
   0x00, 0xca, 0xad, 0x55, 0x15, 0x00, 0x00, 0x70, 0x00, 0x5a, 0xdb, 0xab,
   0x2a, 0xd0, 0x6d, 0xa8, 0xfd, 0x5d, 0xeb, 0xaa, 0x52, 0x72, 0xfb, 0xff,
   0xb5, 0x5b, 0x75, 0xad, 0xaa, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x40, 0x00, 0xa0, 0x5b, 0x55, 0x09, 0x00, 0x00, 0xc0, 0x01, 0xea, 0x7f,
   0xdd, 0x0a, 0xf4, 0xb7, 0xa0, 0x7f, 0x6b, 0xbd, 0xaa, 0x94, 0xda, 0xfe,
   0xff, 0x6f, 0xb5, 0xad, 0xd5, 0xaa, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xd6, 0x56, 0xab, 0x00, 0x00, 0x00, 0x07, 0xe8,
   0xdf, 0x55, 0x0b, 0xd4, 0xef, 0x00, 0x68, 0x5b, 0xfb, 0xaa, 0xaa, 0xda,
   0xfe, 0x7f, 0x6f, 0x77, 0x5b, 0xad, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x41, 0xbd, 0xaa, 0x54, 0x00, 0x00, 0x00, 0x0c,
   0xd5, 0x6f, 0xdb, 0x06, 0xea, 0x5f, 0xab, 0xaa, 0xb5, 0xae, 0x55, 0x55,
   0x6f, 0xff, 0xbf, 0xb5, 0xad, 0xb6, 0x55, 0xad, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xf0, 0xb6, 0xaa, 0x02, 0x00, 0x00,
   0x78, 0x10, 0xda, 0x56, 0x07, 0xda, 0x7f, 0x0f, 0xa0, 0xd6, 0x5e, 0xab,
   0xaa, 0x6e, 0xff, 0x77, 0x77, 0xdb, 0x55, 0x6d, 0xb5, 0x00, 0x00, 0x00,
   0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x40, 0x54, 0x55, 0x55, 0x05, 0x00,
   0x00, 0xa0, 0x4a, 0x55, 0xed, 0x03, 0xf5, 0xaf, 0xbf, 0x8a, 0xb4, 0xb7,
   0xaa, 0xaa, 0xf5, 0xff, 0xdf, 0xda, 0xb6, 0xae, 0xaa, 0x55, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xad, 0x55, 0x15,
   0x00, 0x00, 0xa0, 0x52, 0xa4, 0xda, 0x07, 0xd4, 0xff, 0xfe, 0x90, 0xa4,
   0xab, 0xad, 0xaa, 0xd7, 0x7f, 0xbb, 0xb7, 0xd5, 0xaa, 0x55, 0xd5, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x10, 0x80, 0x5b, 0x55,
   0x29, 0x00, 0x00, 0x48, 0x27, 0x49, 0xf5, 0x03, 0xbd, 0xaa, 0xff, 0x4b,
   0xea, 0x56, 0xb5, 0xf5, 0xfe, 0xff, 0x6d, 0x6d, 0xbb, 0xb5, 0xaa, 0x36,
   0x08, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0xba,
   0x56, 0x55, 0x01, 0x00, 0x10, 0x2c, 0x11, 0xf4, 0x03, 0xe9, 0xff, 0xfe,
   0x4f, 0xc8, 0x54, 0x6b, 0xed, 0xea, 0xff, 0x6f, 0x5b, 0x6b, 0xab, 0xaa,
   0x6a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20,
   0xd4, 0x5a, 0x95, 0x04, 0x00, 0xa5, 0x5a, 0x44, 0xfd, 0x43, 0xf6, 0xff,
   0xff, 0x1f, 0x35, 0x55, 0xd5, 0x5a, 0xff, 0xff, 0xbb, 0xb6, 0xd5, 0xaa,
   0xaa, 0xaa, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x02, 0xf0, 0xd5, 0x2a, 0x09, 0x01, 0x88, 0xd0, 0x01, 0xfc, 0x83, 0xec,
   0x7f, 0xff, 0xff, 0xb0, 0x44, 0xaa, 0xfe, 0xfd, 0xff, 0xee, 0x6e, 0xb7,
   0xaa, 0x5a, 0x55, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x44, 0xc8, 0xb6, 0xaa, 0x2a, 0x00, 0x55, 0x45, 0x85, 0xff, 0xa3,
   0xfa, 0xff, 0xff, 0xff, 0x0f, 0xa9, 0xaa, 0x55, 0xff, 0x7f, 0x5b, 0xdb,
   0x6a, 0xab, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
   0x00, 0x00, 0x01, 0x80, 0xae, 0xaa, 0xaa, 0x00, 0x40, 0x48, 0x96, 0xff,
   0x43, 0xfb, 0xff, 0xff, 0xff, 0x2f, 0x09, 0x29, 0x7f, 0xff, 0x7f, 0xf7,
   0xb6, 0xd6, 0xaa, 0xaa, 0x2a, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x22, 0x57, 0x55, 0x55, 0xa0, 0x2a, 0x05, 0xed,
   0xff, 0x4b, 0xff, 0xff, 0xff, 0xff, 0x83, 0xa4, 0xd2, 0xd5, 0xff, 0xef,
   0x5a, 0xeb, 0xad, 0x5a, 0x55, 0x55, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00,
   0x01, 0x00, 0x08, 0x00, 0x00, 0x20, 0xda, 0xaa, 0xaa, 0x8a, 0x48, 0x08,
   0xe8, 0xff, 0xab, 0xfe, 0xff, 0xff, 0xff, 0x95, 0x24, 0x94, 0xbf, 0xff,
   0xaf, 0xd7, 0x5e, 0xbb, 0x55, 0x55, 0x55, 0x00, 0x00, 0x00, 0x01, 0x00,
   0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x94, 0xba, 0xaa, 0xaa, 0x52, 0x92,
   0x44, 0xd1, 0xff, 0x57, 0xfd, 0xff, 0xff, 0xff, 0x42, 0x48, 0xe9, 0xea,
   0xff, 0x77, 0xbd, 0xb5, 0x56, 0x55, 0x6d, 0x45 };
