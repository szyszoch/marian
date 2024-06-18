#ifndef TILES_H
#define TILES_H

#define TILE_NONE 0x00
#define TILE_FIRST_COLOR 0x01
#define TILE_SECOND_COLOR 0x02
#define TILE_THIRD_COLOR 0x03

#define TILE_GROUND_1 0x04
#define TILE_GROUND_2 0x05
#define TILE_GROUND_3 0x06
#define TILE_GROUND_4 0x07

#define TILE_0 0x08
#define TILE_1 0x09
#define TILE_2 0x0a
#define TILE_3 0x0b
#define TILE_4 0x0c
#define TILE_5 0x0d
#define TILE_6 0x0e
#define TILE_7 0x0f
#define TILE_8 0x10
#define TILE_9 0x11
#define TILE_A 0x12
#define TILE_B 0x13
#define TILE_C 0x14
#define TILE_D 0x15
#define TILE_E 0x16
#define TILE_F 0x17
#define TILE_G 0x18
#define TILE_H 0x19
#define TILE_I 0x1a
#define TILE_J 0x1b
#define TILE_K 0x1c
#define TILE_L 0x1d
#define TILE_M 0x1e
#define TILE_N 0x1f
#define TILE_O 0x20
#define TILE_P 0x21
#define TILE_Q 0x22
#define TILE_R 0x23
#define TILE_S 0x24
#define TILE_T 0x25
#define TILE_U 0x26
#define TILE_V 0x27
#define TILE_W 0x28
#define TILE_X 0x29
#define TILE_Y 0x2a
#define TILE_Z 0x2b
#define TILE_MINUS 0x2c
#define TILE_SMALL_X 0x2d
#define TILE_EXCLAMATION_MARK 0x2e
#define TILE_DOT 0x2f
#define TILE_COPYRIGHT 0x30

#define TILE_COIN_ICON 0x31

#define TILE_LOGO_CENTER 0x02
#define TILE_LOGO_LEFT_TOP_CORNER 0x32
#define TILE_LOGO_TOP_EDGE 0x33
#define TILE_LOGO_LEFT_EDGE 0x33
#define TILE_LOGO_RIGHT_TOP_CORNER 0x34
#define TILE_LOGO_LEFT_BOTTOM_CORNER 0x34
#define TILE_LOGO_BOTTOM_EDGE 0x35
#define TILE_LOGO_RIGHT_EDGE 0x35
#define TILE_LOGO_RIGHT_BOTTOM_CORNER 0x36

#define TILE_BIG_S_LEFT_TOP_CORNER 0x37
#define TILE_BIG_S_RIGHT_TOP_CORNER 0x37
#define TILE_BIG_S_LEFT_BOTTOM_CORNER 0x37
#define TILE_BIG_S_RIGHT_BOTTOM_CORNER 0x37
#define TILE_BIG_S_MIDDLE_LEFT 0x38
#define TILE_BIG_S_MIDDLE_RIGHT 0x39

#define TILE_COUNT 0x3a

struct tile_data {
    unsigned char index[64];
};

struct tile_data get_tile_data(unsigned char t);

#endif