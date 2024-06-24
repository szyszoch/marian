#ifndef TILE_SET_H
#define TILE_SET_H

#define TILESET_LOGO_BOARD 0x00
#define TILESET_BIG_E 0x01
#define TILESET_BIG_P 0x02
#define TILESET_BIG_R 0x03
#define TILESET_BIG_S 0x04
#define TILESET_BIG_U 0x05
#define TILESET_BIGGER_A 0x06
#define TILESET_BIGGER_B 0x07
#define TILESET_BIGGER_I 0x08
#define TILESET_BIGGER_M 0x09
#define TILESET_BIGGER_O 0x0a
#define TILESET_BIGGER_R 0x0b
#define TILESET_BIGGER_S 0x0c
#define TILESET_BIG_E_SHADOW 0x0d
#define TILESET_BIG_P_SHADOW 0x0e
#define TILESET_BIG_R_SHADOW 0x0f
#define TILESET_BIG_S_SHADOW 0x10
#define TILESET_BIG_U_SHADOW 0x11
#define TILESET_BIGGER_A_SHADOW 0x12
#define TILESET_BIGGER_B_SHADOW 0x13
#define TILESET_BIGGER_I_SHADOW 0x14
#define TILESET_BIGGER_M_SHADOW 0x15
#define TILESET_BIGGER_O_SHADOW 0x16
#define TILESET_BIGGER_R_SHADOW 0x17
#define TILESET_BIGGER_S_SHADOW 0x18
#define TILESET_COUNT 0x19

struct tileset {
    unsigned char width;
    unsigned char height;
    unsigned char *tiles;
    unsigned char *flips;
};

extern const struct tileset *tilesets[];

#endif