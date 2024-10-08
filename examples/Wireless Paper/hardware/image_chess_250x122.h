// XBitmap Image used in example: "xbitmap_bw.ino"
// Image description: "chessboard"

// See https://github.com/todd-herbert/heltec-eink-modules/blob/main/docs/XBitmapTutorial/README.md

#define chess_width 250
#define chess_height 122
PROGMEM const static unsigned char chess_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0xfc,
   0x30, 0x00, 0x3f, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x80, 0x3e, 0x80, 0xff, 0x38, 0x80, 0x3f, 0x7e,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x7e, 0x00, 0xff, 0x70, 0x80, 0x3f, 0x7c, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x7f, 0x00, 0x7f,
   0x7c, 0x80, 0x3f, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x80, 0x7f, 0x00, 0x7e, 0xf8, 0x80, 0x1f, 0x3c,
   0xc0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x80, 0x3f, 0x00, 0x7e, 0xfc, 0x80, 0x0f, 0x1c, 0xe0, 0x01, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x3f, 0x00, 0x7e,
   0xfc, 0x80, 0x1f, 0x3c, 0xe0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x78, 0x00, 0x3f, 0x00, 0x7e, 0xfc, 0x80, 0x1f, 0x38,
   0xe0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70,
   0x00, 0x3f, 0x00, 0x7c, 0xfc, 0x80, 0x3f, 0x7a, 0xe0, 0x01, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x3f, 0x00, 0x7e,
   0xfc, 0x80, 0x3f, 0x7e, 0xe0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x70, 0x00, 0x3e, 0x00, 0xfc, 0xf8, 0x80, 0x3e, 0x7e,
   0xe0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8,
   0x00, 0x7f, 0x00, 0x7f, 0x38, 0xc0, 0x3e, 0x7f, 0xe0, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x7f, 0x00, 0x3c,
   0x30, 0x80, 0x7f, 0x78, 0xe1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xf8, 0x81, 0x7f, 0x00, 0x3c, 0x78, 0x80, 0x9f, 0xff,
   0xe4, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8,
   0x01, 0x7f, 0x00, 0x3c, 0xd8, 0x03, 0x7f, 0xfe, 0xeb, 0x03, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0xfc, 0x01, 0x1e, 0x00, 0x7c,
   0xd8, 0x8b, 0xfe, 0xff, 0xf7, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x0f, 0x00, 0xf8, 0x03, 0x3c, 0x00, 0x7c, 0xfc, 0xd7, 0xff, 0xf9,
   0xff, 0x57, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1d, 0x00, 0xfc,
   0x01, 0x3e, 0x00, 0x7f, 0xfc, 0xeb, 0xbf, 0xfd, 0xf1, 0x0b, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0xf8, 0x03, 0x3e, 0x80, 0xff,
   0xfc, 0xc7, 0xff, 0xfc, 0xfd, 0x7f, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x1f, 0x00, 0xfc, 0x03, 0x3e, 0xc0, 0xff, 0xdf, 0x53, 0xff, 0xfe,
   0xf4, 0xab, 0x56, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9e, 0x01, 0xf8,
   0x03, 0x7e, 0xe0, 0xff, 0xfe, 0x97, 0xfe, 0xff, 0xab, 0xea, 0xbf, 0x2a,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x01, 0xf8, 0x03, 0x7f, 0xe0, 0xff,
   0xff, 0x7f, 0xff, 0xff, 0x2f, 0xf5, 0xff, 0xab, 0x02, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xfe, 0x01, 0xf0, 0x00, 0xfa, 0xe0, 0xff, 0xff, 0x7f, 0xff, 0xff,
   0x7f, 0xfd, 0xff, 0xbf, 0x2a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x01, 0xe0,
   0x01, 0xfd, 0xca, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0x4f,
   0x45, 0x01, 0x00, 0x00, 0x00, 0x00, 0x84, 0x02, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xc0, 0x07, 0x00, 0xfe, 0x00, 0xf0, 0x01, 0xfe, 0x91, 0xff,
   0xdf, 0xbf, 0xff, 0xff, 0xbf, 0xd1, 0xff, 0x17, 0x54, 0x2a, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x05, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x1f,
   0x00, 0xfe, 0x00, 0xf0, 0x81, 0xff, 0xf5, 0xff, 0xf9, 0xd7, 0xff, 0xfe,
   0x41, 0x2e, 0x7d, 0xa0, 0x82, 0x84, 0x02, 0x00, 0x00, 0x00, 0x83, 0x0a,
   0x80, 0x05, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x1f, 0x00, 0xfe, 0x01, 0xe0,
   0x03, 0xfe, 0xe3, 0xff, 0xe7, 0x5f, 0xff, 0xea, 0x8a, 0xa8, 0xea, 0x0a,
   0x94, 0x38, 0x2a, 0x00, 0x00, 0x04, 0x02, 0x0b, 0x00, 0x45, 0x00, 0x00,
   0x00, 0x00, 0xf8, 0x1f, 0x00, 0xff, 0x03, 0xf0, 0xa7, 0xff, 0xcb, 0xff,
   0xef, 0x8f, 0x54, 0xff, 0x52, 0x42, 0x7a, 0x55, 0x41, 0xfe, 0x41, 0x01,
   0x00, 0x14, 0xc1, 0x06, 0x20, 0x1d, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x1f,
   0x00, 0xfe, 0x83, 0xff, 0x8f, 0xfd, 0xdf, 0xff, 0xff, 0x2f, 0x41, 0xfc,
   0x97, 0x54, 0xfd, 0x17, 0x4a, 0xff, 0x5f, 0x2a, 0x00, 0x14, 0x42, 0x3d,
   0x20, 0x3a, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x1f, 0x00, 0xff, 0xc7, 0xff,
   0xaf, 0xfd, 0xdf, 0xdf, 0xff, 0xbf, 0x80, 0xff, 0x7f, 0x45, 0xff, 0xff,
   0xd0, 0xff, 0xff, 0x52, 0x01, 0x15, 0x40, 0x05, 0x48, 0x2f, 0x00, 0x00,
   0x00, 0x00, 0xe0, 0x1f, 0x00, 0xfe, 0xc7, 0xff, 0xbf, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xeb, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xf7, 0xff, 0xff, 0x57,
   0x15, 0x15, 0xd0, 0x3b, 0xa8, 0x1e, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x3f,
   0x00, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xcf, 0xff, 0xff, 0xff, 0xf7, 0xff,
   0xff, 0xe7, 0xff, 0xff, 0x81, 0xff, 0xff, 0x90, 0x8a, 0x0a, 0xa0, 0xc6,
   0xab, 0x0a, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1f, 0x00, 0xf2, 0xe7, 0xff,
   0xff, 0xff, 0xff, 0xbf, 0xff, 0xff, 0x4b, 0xff, 0xff, 0x08, 0xfe, 0xff,
   0x0a, 0xf8, 0x7f, 0x25, 0x88, 0x0a, 0xa0, 0x1d, 0x55, 0x0f, 0x00, 0x00,
   0x00, 0x00, 0xe0, 0x1f, 0x00, 0xfc, 0xeb, 0xff, 0x1f, 0xff, 0xff, 0xbf,
   0xfe, 0x5f, 0xb5, 0xfe, 0x5f, 0xa5, 0xf0, 0x1f, 0x80, 0xc2, 0x8f, 0x14,
   0x0a, 0x05, 0x5a, 0x65, 0x95, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0f,
   0x30, 0xfc, 0x8f, 0xff, 0xff, 0xfe, 0xf5, 0x7f, 0xf1, 0x0b, 0xa5, 0xe8,
   0x2f, 0x89, 0x02, 0xaf, 0x0a, 0x14, 0x2c, 0x05, 0x0a, 0x0d, 0xb4, 0x4d,
   0x15, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0f, 0xfc, 0xf8, 0xdf, 0xff,
   0x7f, 0xff, 0xf9, 0xff, 0xd6, 0xa0, 0x48, 0xab, 0x53, 0x52, 0x54, 0x02,
   0x50, 0x41, 0x57, 0x08, 0x95, 0x0a, 0xda, 0xaa, 0xca, 0x01, 0x00, 0x00,
   0x00, 0x00, 0x80, 0x1f, 0xfc, 0xfc, 0xdf, 0xff, 0xff, 0xfe, 0xe3, 0xff,
   0xd5, 0x8b, 0x12, 0xa4, 0x57, 0x55, 0x81, 0x7f, 0x05, 0x14, 0xff, 0x8a,
   0x8a, 0x82, 0xb4, 0xab, 0x8a, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0x1f,
   0xff, 0xff, 0xff, 0xdf, 0x7f, 0xff, 0xa3, 0x7f, 0xff, 0x57, 0xa4, 0xea,
   0xbf, 0xaa, 0xea, 0xff, 0x52, 0xe1, 0x1f, 0x4b, 0x41, 0xa1, 0xda, 0xa6,
   0x46, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3f, 0xfe, 0xff, 0xff, 0x1f,
   0xfa, 0xff, 0x0f, 0x50, 0xff, 0xbf, 0x4a, 0xfa, 0xff, 0x4b, 0xfa, 0xff,
   0x17, 0xea, 0x1f, 0x4c, 0x01, 0x07, 0xb4, 0x4d, 0x4d, 0x07, 0x00, 0x00,
   0x00, 0x00, 0xc0, 0x7f, 0xff, 0xff, 0xff, 0x5f, 0x7d, 0xff, 0x1f, 0xea,
   0xff, 0xff, 0x95, 0xff, 0xff, 0x97, 0xfe, 0xff, 0xff, 0xfc, 0x87, 0x8b,
   0x40, 0x55, 0x74, 0x25, 0xab, 0x03, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff,
   0xfe, 0xff, 0xbf, 0x7f, 0xff, 0xff, 0xff, 0xf4, 0xff, 0xff, 0xd7, 0xff,
   0xff, 0x7f, 0xff, 0xff, 0xff, 0xf5, 0x07, 0x85, 0x00, 0x2a, 0xa8, 0x46,
   0xaa, 0x07, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0xfd, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0x1f, 0xfd, 0xff,
   0x3f, 0xc8, 0xa3, 0x4a, 0xc8, 0x1a, 0x76, 0x95, 0xe3, 0x05, 0x00, 0x00,
   0x00, 0x00, 0xc0, 0xff, 0xfd, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xf4,
   0xff, 0xff, 0x8b, 0xfe, 0xff, 0x57, 0xc0, 0xff, 0x5f, 0x09, 0xa2, 0x8a,
   0x88, 0x15, 0xd4, 0xa5, 0x46, 0x5f, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xaf, 0xd5, 0xff, 0xbf, 0xa8, 0xfa,
   0xff, 0x89, 0x2a, 0xff, 0x03, 0x42, 0xa5, 0xc5, 0x48, 0x0b, 0xaa, 0x4a,
   0xd9, 0xa7, 0x02, 0x00, 0x00, 0x00, 0xe0, 0xff, 0xff, 0xff, 0xef, 0xff,
   0xf2, 0xff, 0x53, 0x95, 0xfe, 0xaf, 0x22, 0xa2, 0xff, 0x2a, 0x00, 0xf0,
   0xab, 0x40, 0x55, 0x45, 0xd1, 0x1a, 0xba, 0xda, 0xb1, 0x5e, 0x15, 0x00,
   0x00, 0x00, 0xf4, 0xff, 0xff, 0xff, 0xf5, 0xff, 0xc5, 0x3f, 0x08, 0x55,
   0xfd, 0x4b, 0x94, 0x94, 0x1e, 0x51, 0x55, 0x45, 0x10, 0x98, 0xa0, 0x81,
   0xa8, 0xb5, 0x6a, 0x69, 0xd5, 0x57, 0x55, 0x00, 0x00, 0x00, 0xe1, 0xff,
   0xfb, 0xbf, 0xe0, 0xff, 0x1b, 0x16, 0x50, 0x50, 0xd1, 0x95, 0x92, 0x00,
   0x28, 0x05, 0x01, 0xd4, 0x27, 0x50, 0x41, 0xa3, 0x69, 0x2b, 0xad, 0xd0,
   0x6a, 0xff, 0xaa, 0x00, 0x00, 0x30, 0xe0, 0xff, 0xff, 0x0f, 0xea, 0xff,
   0x65, 0x4b, 0x00, 0x4a, 0xea, 0xaa, 0x24, 0x09, 0xbf, 0xa8, 0x54, 0xf9,
   0x17, 0xae, 0x20, 0x42, 0xa8, 0x2a, 0xb6, 0xb4, 0xa9, 0xb7, 0x55, 0x00,
   0x00, 0x40, 0xe0, 0xff, 0xff, 0x7f, 0xc0, 0xff, 0xdf, 0x5f, 0x05, 0x90,
   0xf4, 0xaf, 0x4a, 0x52, 0xff, 0x03, 0x01, 0xfd, 0x3f, 0xa8, 0x02, 0xc6,
   0xe8, 0x25, 0x6c, 0x69, 0x53, 0x6d, 0xdd, 0x01, 0x00, 0x80, 0xc0, 0xff,
   0xfd, 0xff, 0x40, 0xff, 0xfd, 0x7f, 0x80, 0x4a, 0xff, 0x5f, 0x92, 0xe4,
   0xff, 0x5f, 0xaa, 0xfe, 0x1f, 0x57, 0x90, 0x55, 0x50, 0x09, 0xab, 0xdd,
   0xad, 0x56, 0x6b, 0x01, 0x00, 0x00, 0x84, 0xff, 0xff, 0xff, 0x07, 0xe8,
   0xff, 0xff, 0x2b, 0x48, 0xff, 0x7f, 0x25, 0xf9, 0xff, 0xbf, 0xa0, 0xff,
   0x3f, 0x54, 0x01, 0x6b, 0x50, 0x13, 0x6d, 0xfb, 0x5f, 0x55, 0x55, 0x01,
   0x00, 0x00, 0x04, 0xfe, 0xfe, 0xff, 0x07, 0xd0, 0xff, 0xff, 0x97, 0xf2,
   0xff, 0xff, 0x8b, 0xfe, 0xff, 0xff, 0xeb, 0xff, 0xbf, 0xab, 0xc0, 0x2a,
   0x68, 0x0d, 0xd5, 0xfe, 0xff, 0x55, 0xf5, 0x00, 0x08, 0x00, 0x30, 0xf0,
   0xfe, 0xff, 0x3f, 0xe0, 0xff, 0xff, 0xbf, 0xfc, 0xff, 0xff, 0xbf, 0xff,
   0xff, 0xff, 0xef, 0xff, 0x1f, 0x6a, 0x90, 0x2a, 0xd0, 0x0d, 0x5d, 0xfd,
   0xff, 0xab, 0xaa, 0x01, 0x28, 0x00, 0x40, 0xfe, 0xff, 0xff, 0xff, 0xfe,
   0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0x4f, 0xff, 0xff, 0xff, 0xc1, 0xe1,
   0x1f, 0x2d, 0xc8, 0x3e, 0xa8, 0x82, 0xea, 0xff, 0x7f, 0x55, 0x75, 0x01,
   0xa8, 0x00, 0x80, 0xfe, 0xfe, 0xff, 0xbf, 0xfc, 0xff, 0xff, 0x7f, 0xfd,
   0xff, 0xff, 0x0b, 0xfc, 0xff, 0x7f, 0x09, 0x80, 0x1f, 0x2a, 0x88, 0x39,
   0x68, 0x07, 0x5b, 0xfd, 0x7f, 0xdf, 0xd6, 0x02, 0x28, 0x01, 0x00, 0xfe,
   0xff, 0xff, 0x0f, 0xf4, 0xff, 0xff, 0x97, 0xf2, 0xff, 0xff, 0x00, 0xf0,
   0xff, 0x1f, 0x52, 0x74, 0x9f, 0x15, 0x40, 0x3b, 0x54, 0x41, 0xd5, 0xff,
   0xaf, 0xaa, 0xbd, 0x01, 0xa8, 0x02, 0x00, 0xf8, 0xff, 0xff, 0xab, 0xc4,
   0xff, 0xff, 0xa5, 0x84, 0xff, 0xbf, 0x00, 0x80, 0xff, 0x57, 0x04, 0xa8,
   0x3e, 0x35, 0x44, 0xe5, 0x54, 0x03, 0x5b, 0xf5, 0x57, 0x55, 0x6b, 0x03,
   0x50, 0x05, 0x00, 0xe0, 0xfd, 0xff, 0xaa, 0x2a, 0xff, 0x3f, 0x0a, 0xa9,
   0xfe, 0x0f, 0x00, 0x00, 0xfe, 0x83, 0x12, 0xaa, 0x0e, 0x0b, 0xa2, 0x8b,
   0xb4, 0x40, 0xb5, 0xab, 0x8b, 0x54, 0xfd, 0x02, 0x50, 0x15, 0x00, 0x80,
   0xff, 0xbf, 0xab, 0x4a, 0xfc, 0xaf, 0x50, 0x82, 0xf8, 0x0b, 0x00, 0x00,
   0xf0, 0x2a, 0x2a, 0xaa, 0x08, 0x16, 0xa0, 0x5a, 0x54, 0x51, 0x57, 0x5b,
   0x2b, 0xa1, 0xf5, 0x03, 0x40, 0x15, 0x00, 0x00, 0xff, 0x6b, 0x55, 0x95,
   0xfa, 0x13, 0x01, 0x10, 0xe0, 0x00, 0x00, 0x00, 0x45, 0x40, 0x15, 0xad,
   0x82, 0x2a, 0xe0, 0x2b, 0x58, 0xa0, 0xda, 0xad, 0x55, 0xd5, 0xfe, 0x01,
   0x40, 0xb5, 0x00, 0x00, 0xf8, 0x40, 0x55, 0xa9, 0xc0, 0x52, 0x02, 0x00,
   0xc0, 0x00, 0x00, 0x00, 0xf4, 0x4b, 0x55, 0xaa, 0x80, 0x2a, 0x81, 0x6e,
   0x54, 0xc0, 0xb6, 0xeb, 0xaa, 0xaa, 0xfd, 0x03, 0x00, 0x55, 0x01, 0x00,
   0x18, 0x00, 0xaa, 0x2a, 0x75, 0x04, 0x00, 0x00, 0xf0, 0x03, 0x00, 0x80,
   0xfc, 0x21, 0x29, 0xad, 0x42, 0x55, 0xf0, 0x15, 0x2c, 0xa0, 0xad, 0xae,
   0x55, 0x75, 0xff, 0x02, 0x00, 0xaa, 0x06, 0x00, 0x20, 0x80, 0x20, 0x55,
   0xf5, 0x05, 0x00, 0x00, 0xfa, 0x1f, 0x00, 0x80, 0xfe, 0xa0, 0x22, 0x5a,
   0x01, 0xad, 0x40, 0x17, 0x78, 0x40, 0xbb, 0x78, 0xad, 0x6a, 0xff, 0x03,
   0x00, 0x55, 0x09, 0x00, 0xc0, 0x40, 0x48, 0x22, 0xff, 0x07, 0x00, 0x80,
   0xfe, 0x3f, 0x00, 0x54, 0x7f, 0x58, 0x15, 0xb6, 0x41, 0xd5, 0xf8, 0x0a,
   0x56, 0xa8, 0x56, 0x8a, 0xaa, 0xde, 0xdf, 0x02, 0x00, 0x54, 0x15, 0x00,
   0x00, 0x03, 0x89, 0xc4, 0xff, 0x3f, 0x00, 0x80, 0xff, 0xff, 0x03, 0xd0,
   0x7f, 0xb0, 0x26, 0x2a, 0x51, 0xad, 0xa1, 0x0a, 0xb4, 0xa8, 0xb5, 0x28,
   0xa9, 0xda, 0xff, 0x02, 0x00, 0xa8, 0x2a, 0x00, 0x00, 0x04, 0x04, 0xf8,
   0xff, 0xff, 0x00, 0xf8, 0xff, 0xff, 0x4b, 0xf5, 0x3f, 0x6a, 0x9f, 0x8a,
   0xa0, 0xf5, 0xdc, 0x0d, 0x6d, 0xf8, 0x6e, 0x47, 0x92, 0xf6, 0xbf, 0x01,
   0x00, 0x60, 0x55, 0x01, 0x00, 0x38, 0x04, 0xfc, 0xff, 0xff, 0x03, 0xfa,
   0xff, 0xff, 0x2f, 0xfc, 0x3f, 0xac, 0x7c, 0x1a, 0x41, 0xd7, 0x50, 0x05,
   0xda, 0xc0, 0xdf, 0x55, 0xa4, 0xee, 0x7f, 0x03, 0x00, 0xc0, 0xaa, 0x02,
   0x00, 0xa0, 0xc0, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff,
   0x3f, 0xb5, 0x1e, 0x96, 0x82, 0x84, 0xe8, 0x03, 0xb5, 0x7e, 0xf5, 0xab,
   0xca, 0xfd, 0xaf, 0x01, 0x00, 0x40, 0xab, 0x0a, 0x00, 0x80, 0xd1, 0xff,
   0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0x3f, 0xfd, 0x3f, 0xad, 0x1e, 0x94,
   0x02, 0x50, 0xa8, 0x86, 0x56, 0xf5, 0xff, 0x5a, 0x55, 0xfb, 0x7f, 0x03,
   0x00, 0x00, 0xaa, 0x12, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xcf, 0xff,
   0xff, 0xff, 0x4f, 0xf4, 0x7f, 0x55, 0x0f, 0x4d, 0x45, 0x56, 0x58, 0x85,
   0xda, 0xff, 0x7f, 0xb7, 0xea, 0xfe, 0xd7, 0x02, 0x00, 0x00, 0x5a, 0x55,
   0x00, 0x00, 0xf8, 0xff, 0xff, 0xff, 0x07, 0xfe, 0xff, 0xff, 0x97, 0xd4,
   0x7f, 0x76, 0x07, 0x4a, 0xad, 0xaa, 0xe9, 0x05, 0xab, 0xfe, 0x7f, 0xd5,
   0xda, 0xfe, 0xdf, 0x02, 0x00, 0x00, 0xb0, 0xaa, 0x00, 0x00, 0xf0, 0xff,
   0xff, 0xff, 0x00, 0xf8, 0xff, 0xff, 0x49, 0xa5, 0x3f, 0xaa, 0x83, 0x4d,
   0x55, 0x55, 0x55, 0x81, 0x6e, 0xff, 0xdf, 0xb6, 0xed, 0xff, 0xaa, 0x01,
   0x00, 0x00, 0x40, 0x55, 0x05, 0x00, 0xc0, 0xff, 0xff, 0x7f, 0x00, 0xc0,
   0xff, 0x7f, 0x91, 0x2a, 0x3c, 0x5c, 0x01, 0x4a, 0x55, 0xd5, 0xd1, 0x80,
   0x5a, 0xfd, 0x4f, 0x55, 0xdd, 0xff, 0x7f, 0x03, 0x00, 0x00, 0xa0, 0x55,
   0x29, 0x00, 0x80, 0xff, 0xff, 0x0f, 0x00, 0x40, 0xff, 0x1f, 0xaa, 0x44,
   0x31, 0xb5, 0x80, 0x56, 0xd5, 0xaa, 0xb8, 0x40, 0xb5, 0xfa, 0x13, 0x55,
   0xeb, 0x7f, 0xd5, 0x02, 0x00, 0x00, 0x00, 0xaa, 0x4a, 0x00, 0x00, 0xfc,
   0xff, 0x07, 0x00, 0x00, 0xfc, 0xaf, 0x24, 0x15, 0x25, 0xad, 0x40, 0x95,
   0xaa, 0xb6, 0x68, 0x41, 0xd7, 0xa2, 0x53, 0xa0, 0xee, 0xff, 0xdb, 0x02,
   0x00, 0x00, 0x00, 0x55, 0x55, 0x01, 0x00, 0xf8, 0xff, 0x00, 0x00, 0x00,
   0xfa, 0x91, 0x4a, 0xa0, 0x94, 0x6a, 0xa0, 0x76, 0x55, 0x55, 0xd4, 0xd0,
   0x5a, 0xad, 0x84, 0x4a, 0xfb, 0x5f, 0x6d, 0x01, 0x00, 0x00, 0x00, 0x50,
   0x55, 0x05, 0x00, 0xe0, 0x7f, 0x00, 0x00, 0x00, 0xc0, 0x45, 0x12, 0x14,
   0x11, 0x5d, 0x80, 0x55, 0xaa, 0x2d, 0xb4, 0x83, 0xd6, 0xd5, 0x55, 0xd2,
   0xf6, 0xff, 0xdb, 0x03, 0x00, 0x00, 0x00, 0x68, 0x55, 0x09, 0x00, 0xc0,
   0x0f, 0x00, 0x00, 0x00, 0x55, 0x52, 0x05, 0xab, 0x04, 0xaa, 0xa0, 0x16,
   0x55, 0x15, 0xd8, 0xd2, 0xbd, 0xb6, 0xaa, 0xa4, 0xfd, 0x57, 0xad, 0x02,
   0x00, 0x00, 0x00, 0xa0, 0x55, 0x15, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00,
   0xf0, 0x4b, 0x04, 0x2d, 0x09, 0xba, 0x40, 0x15, 0x55, 0x35, 0xb2, 0x53,
   0xd5, 0x75, 0x55, 0xb5, 0xfb, 0x7f, 0xdb, 0x02, 0x00, 0x00, 0x00, 0x88,
   0xaa, 0xaa, 0x00, 0x00, 0x05, 0x00, 0x00, 0x80, 0xfe, 0x97, 0x42, 0x5b,
   0x04, 0x6d, 0x91, 0x86, 0x6a, 0x2d, 0x5d, 0xa5, 0xfb, 0xde, 0xaa, 0xda,
   0xfe, 0xab, 0xad, 0x01, 0x00, 0x00, 0x00, 0x00, 0x56, 0x55, 0x01, 0x00,
   0x38, 0x00, 0x15, 0x2a, 0xfe, 0x5f, 0xa4, 0xaa, 0x00, 0x5a, 0xb1, 0x44,
   0xa9, 0x2a, 0xf5, 0x45, 0xfb, 0xbd, 0xad, 0xda, 0xfe, 0x7e, 0x6b, 0x03,
   0x00, 0x00, 0x00, 0x00, 0x58, 0x55, 0x02, 0x00, 0xa0, 0x80, 0xa0, 0xc0,
   0xff, 0x7f, 0xa1, 0x5b, 0x84, 0x35, 0xda, 0xa4, 0xb6, 0x1a, 0xae, 0x0e,
   0xad, 0x56, 0xab, 0x6e, 0xff, 0xd5, 0xae, 0x02, 0x00, 0x00, 0x00, 0x20,
   0x70, 0x55, 0x15, 0x00, 0x80, 0x23, 0x0a, 0xd5, 0xff, 0xff, 0xa7, 0x56,
   0x85, 0x2e, 0xb2, 0xa5, 0x54, 0x35, 0xf8, 0x7a, 0xa8, 0xdb, 0xda, 0xda,
   0xff, 0xdf, 0xda, 0x02, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xaa, 0x4a, 0x00,
   0x00, 0x8a, 0x50, 0xf8, 0xff, 0xff, 0x57, 0x95, 0x43, 0x35, 0x7d, 0x51,
   0xab, 0x8a, 0x56, 0xff, 0xc1, 0xaa, 0xb6, 0xf7, 0x7f, 0xb5, 0xb5, 0x02,
   0x00, 0x00, 0x00, 0x00, 0x20, 0x57, 0x95, 0x00, 0x00, 0x98, 0x4a, 0xfd,
   0xff, 0xff, 0x4f, 0xb5, 0x47, 0x2d, 0xfa, 0x51, 0xaa, 0x3a, 0xfd, 0xfa,
   0x9f, 0xa8, 0x6a, 0xed, 0xff, 0x6f, 0xd7, 0x02, 0x00, 0x00, 0x40, 0x00,
   0x80, 0xaa, 0xaa, 0x02, 0x00, 0x32, 0x91, 0xff, 0xff, 0xff, 0x4f, 0xd5,
   0xa3, 0x3b, 0xa1, 0xa8, 0xaa, 0xd5, 0x56, 0xff, 0x7f, 0x52, 0xd5, 0xfb,
   0x7f, 0xdb, 0x5a, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbc, 0xaa, 0x0a,
   0x00, 0x60, 0xa5, 0xff, 0xff, 0xff, 0x4f, 0xb7, 0x87, 0x36, 0x54, 0x54,
   0x55, 0x8d, 0xfe, 0xff, 0xbf, 0x84, 0x54, 0xfb, 0x6f, 0xdb, 0x56, 0x03,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xd0, 0xaa, 0x0a, 0x00, 0x8a, 0xf9, 0xff,
   0xff, 0xff, 0xcf, 0xea, 0x57, 0x1f, 0xea, 0x4a, 0x55, 0xab, 0xff, 0xff,
   0x0f, 0x29, 0xe9, 0xfe, 0xb7, 0xb6, 0x6d, 0x01, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xc8, 0x55, 0x55, 0x80, 0x10, 0xfd, 0xff, 0xff, 0xff, 0x9f, 0xd6,
   0xdf, 0x3a, 0xac, 0x1f, 0x55, 0xad, 0xff, 0xff, 0x5f, 0x49, 0xda, 0xfe,
   0xef, 0x6d, 0xad, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa0, 0x56, 0x55,
   0x01, 0x4a, 0xf8, 0xff, 0xff, 0xff, 0x4f, 0xd5, 0xff, 0x3f, 0xf5, 0x8a,
   0x6a, 0xfb, 0xff, 0xff, 0x57, 0x95, 0x6a, 0xff, 0x5d, 0xdb, 0xda, 0x02,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xb6, 0xaa, 0x02, 0x88, 0xc2, 0xff,
   0xff, 0xff, 0x8f, 0x2d, 0xfe, 0x3f, 0x55, 0x8b, 0xde, 0xfe, 0xff, 0xff,
   0x57, 0x55, 0x6d, 0xff, 0x75, 0xd5, 0xb6, 0x02, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x10, 0xad, 0x55, 0x05, 0x24, 0xd4, 0xff, 0xff, 0xff, 0x47, 0x5b,
   0xfc, 0x3f, 0xd6, 0x06, 0xb5, 0xf5, 0xff, 0xff, 0xad, 0xaa, 0xb6, 0xff,
   0xae, 0x5b, 0x55, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0xad,
   0x2a, 0x40, 0x09, 0xfe, 0xff, 0xff, 0x83, 0xd6, 0xe0, 0xff, 0xba, 0x0d,
   0xf4, 0xcf, 0xff, 0xff, 0xaa, 0xaa, 0xee, 0xff, 0xbb, 0xb6, 0x6d, 0x03,
   0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa4, 0x55, 0x55, 0x10, 0xa5, 0xf8,
   0xff, 0xff, 0xa1, 0xad, 0xca, 0xff, 0xea, 0x82, 0xba, 0xaa, 0xff, 0x7f,
   0x6d, 0xd5, 0xf5, 0x5f, 0x6d, 0x6d, 0xab, 0x02, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xa0, 0x55, 0x55, 0x41, 0x04, 0xe2, 0xff, 0xff, 0xa0, 0x6d,
   0x09, 0xfe, 0x5a, 0x83, 0xea, 0x0b, 0xfc, 0x5f, 0xab, 0x55, 0xf7, 0xff,
   0x5b, 0xab, 0xaa, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xb6,
   0xaa, 0x92, 0x00, 0xc1, 0xff, 0x3f, 0xa0, 0x5a, 0x01, 0xfc, 0xb4, 0xa0,
   0xb6, 0x56, 0xe9, 0xaf, 0x54, 0xfb, 0xfe, 0x5f, 0xed, 0xb6, 0x56, 0x01,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0xac, 0xaa, 0x2a, 0x00, 0x02,
   0xff, 0x1f, 0xa0, 0xdb, 0x0a, 0xe0, 0xe8, 0xa1, 0xb6, 0x55, 0xa5, 0x8f,
   0xaa, 0xea, 0xfd, 0xff, 0xad, 0xad, 0xaa, 0x02, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xbd, 0x55, 0x15, 0x20, 0x00, 0xfc, 0x07, 0xa8, 0xb6,
   0x12, 0x50, 0xb6, 0x40, 0x6b, 0xaf, 0x8a, 0x52, 0xa4, 0x5a, 0xff, 0xab,
   0xb6, 0x5a, 0x55, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70,
   0x55, 0x55, 0x00, 0x00, 0xf0, 0x03, 0xd0, 0xee, 0x56, 0x00, 0xec, 0xa1,
   0x6e, 0xad, 0xaa, 0x85, 0x94, 0xfa, 0xfe, 0xff, 0xd6, 0xb6, 0xaa, 0x02,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x6d, 0x95, 0x80, 0x00,
   0xf0, 0x00, 0xa8, 0xb5, 0x55, 0x11, 0x5a, 0x51, 0xbb, 0xdb, 0xaa, 0x52,
   0x22, 0xad, 0xff, 0xab, 0xbd, 0xd5, 0xaa, 0x02, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x88, 0x55, 0xab, 0x02, 0x00, 0x80, 0x01, 0x68, 0xb7,
   0xad, 0x12, 0x74, 0xa3, 0x6a, 0xb7, 0xd5, 0x4a, 0x4a, 0xbd, 0xff, 0x7e,
   0xab, 0x56, 0x55, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
   0x6f, 0x55, 0x15, 0x00, 0x00, 0x03, 0xa8, 0xdd, 0x5a, 0x05, 0xad, 0x51,
   0xfb, 0x6b, 0x7b, 0x95, 0x54, 0xf7, 0xff, 0xab, 0xdd, 0xad, 0xaa, 0x02,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd8, 0x56, 0x29, 0x00,
   0x00, 0x0c, 0x68, 0xfb, 0xb7, 0x0a, 0xba, 0x47, 0xfe, 0xdf, 0x56, 0x55,
   0xa5, 0xed, 0xff, 0xbb, 0x55, 0xdb, 0x56, 0x01, 0x00, 0x04, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x20, 0x6c, 0xad, 0x4a, 0x00, 0x00, 0x38, 0xd0, 0xbf,
   0x6a, 0x85, 0xfe, 0x0a, 0x51, 0x55, 0xbd, 0xaa, 0xd4, 0xf6, 0x7f, 0xd7,
   0xde, 0xaa, 0xaa, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xd0, 0xab, 0xaa, 0x00, 0x00, 0xe0, 0x80, 0xfe, 0x56, 0x83, 0xfa, 0x3b,
   0xa5, 0x6d, 0x6f, 0x55, 0xd5, 0xfd, 0xff, 0xbd, 0xb5, 0xb6, 0x6a, 0x01,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc8, 0x6d, 0x55, 0x01,
   0x00, 0x80, 0x2a, 0xa9, 0xed, 0x41, 0xfd, 0xbe, 0x48, 0xaa, 0x5b, 0x55,
   0x75, 0xff, 0xbf, 0x56, 0xdb, 0x6a, 0xab, 0x02, 0x00, 0x00, 0x00, 0x10,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x56, 0x55, 0x05, 0x00, 0x00, 0x4a, 0xaa,
   0xda, 0x03, 0xfd, 0xf5, 0x92, 0x6a, 0xab, 0x55, 0x6d, 0xfd, 0xff, 0xfd,
   0xb6, 0x56, 0xad, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
   0x00, 0xad, 0xaa, 0x0a, 0x00, 0x80, 0xaa, 0x50, 0xf5, 0xc1, 0xbe, 0xff,
   0x4b, 0xc8, 0x6d, 0xab, 0xb6, 0xff, 0x56, 0xab, 0x6d, 0x55, 0xb5, 0x01,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfa, 0x56, 0x55,
   0x00, 0x00, 0x68, 0x05, 0xf5, 0x01, 0x75, 0xf5, 0x9f, 0xd2, 0xaa, 0xda,
   0x76, 0xff, 0xff, 0x6e, 0xab, 0x55, 0xab, 0x02, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xa1, 0xb5, 0x4a, 0x01, 0xa0, 0x52, 0x91,
   0xfc, 0xd1, 0xfe, 0xff, 0x3f, 0x34, 0x55, 0xb5, 0xdb, 0xff, 0x57, 0xd5,
   0x5a, 0x55, 0x55, 0x01, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xc8, 0x56, 0x55, 0x02, 0x00, 0x4a, 0x87, 0xfc, 0x41, 0xfd, 0xf7,
   0xff, 0x31, 0xa1, 0xaa, 0xdb, 0xff, 0xfd, 0xbf, 0x76, 0x55, 0x55, 0x01,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xa0, 0x6b, 0x55,
   0x05, 0x50, 0x11, 0x0a, 0xff, 0xd8, 0xfe, 0xfb, 0xff, 0x4f, 0x4a, 0xd5,
   0xee, 0xff, 0xab, 0x6a, 0xad, 0x55, 0x55, 0x01, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x10, 0x00, 0x10, 0x00, 0xae, 0xaa, 0x2a, 0x10, 0x25, 0xb8,
   0xff, 0xa1, 0xff, 0xff, 0xff, 0x8f, 0x90, 0xd4, 0xfd, 0xff, 0x7e, 0xdb,
   0x5b, 0x55, 0x55, 0x01, 0x00, 0x08, 0x40, 0x00, 0x00, 0x02, 0x00, 0x00,
   0x00, 0x44, 0xb6, 0xaa, 0x4a, 0x4a, 0x08, 0xf2, 0xff, 0xd5, 0xff, 0xff,
   0xff, 0x13, 0x25, 0x75, 0xff, 0x7f, 0xab, 0xad, 0x56, 0xab, 0xaa, 0x02,
   0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x20, 0xf4, 0xaa,
   0xaa, 0x90, 0x22, 0x82, 0xff, 0xab, 0xff, 0xff, 0xff, 0x53, 0xa4, 0xd4,
   0xfd, 0xff, 0x6e, 0xbb, 0x6d, 0xd5, 0x56, 0x00, 0x00, 0x00, 0x00, 0x08,
   0x00, 0x00, 0x40, 0x10, 0x00, 0x80, 0x78, 0xab, 0xaa, 0x2a, 0x90, 0x50,
   0xff, 0xeb, 0xff, 0xff, 0xff, 0x84, 0x48, 0xbd, 0xfe, 0xbf, 0xdd, 0x56,
   0x5b, 0xab, 0xaa, 0x02, 0x00, 0x00, 0x00, 0x12, 0x04, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x40, 0xab, 0xaa, 0xa2, 0x00, 0x01, 0xfc, 0xef, 0xff, 0xff,
   0xff, 0x2a, 0x49, 0xea, 0xff, 0xef, 0xb5, 0x75, 0xb5, 0xaa, 0xaa, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x56,
   0x55, 0x0d, 0x20, 0xaa, 0xf8, 0xff, 0xff, 0xff, 0xbf, 0x52, 0x92, 0x5f,
   0xff, 0x7b, 0x57, 0xab, 0x6b, 0x57, 0x25, 0x01, 0x00, 0x00, 0x20, 0x40,
   0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0xbc, 0x55, 0x55, 0x41, 0x00,
   0xe1, 0xff, 0xff, 0xff, 0xbf, 0x4a, 0x25, 0xf5, 0xff, 0x6b, 0xf5, 0xbe,
   0xd6, 0x54, 0x55, 0x02, 0x00, 0x00, 0x00, 0x08, 0x10, 0x00, 0x00, 0x00,
   0x01, 0x20, 0x10, 0x5a, 0xad, 0x2a, 0x8a, 0xaa, 0xc4, 0xff, 0xff, 0xff,
   0x5f, 0x55, 0xaa, 0xef, 0xff, 0xdd, 0xad, 0xd5, 0x5a, 0x5b, 0x55, 0x01,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0xd0,
   0x6a, 0xd5, 0x08, 0x80, 0x08, 0xfe, 0xff, 0xff, 0xdf, 0xaa, 0x6a, 0xed,
   0xff, 0x5b, 0x6b, 0xdb, 0xd6, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x20, 0x08, 0x10, 0x00, 0xd4, 0xd5, 0x2a, 0xa5, 0x14,
   0x25, 0xfd, 0xff, 0xff, 0xb7, 0xaa, 0xea, 0xfb, 0x7f, 0xf7, 0xde, 0xb6,
   0x5a, 0xb5, 0x4a, 0x01 };
