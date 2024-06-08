#ifndef DATA_PALETTES_H
#define DATA_PALETTES_H

#define PALETTE_OVERWORLD_GROUND_AND_STONE 0x00
#define PALETTE_UNDERGROUND_GROUND_AND_STONE 0x01
#define PALETTE_CASTLE_GROUND_AND_STONE 0x02
#define PALETTE_UNDERWATER_GROUND_AND_STONE 0x03
#define PALETTE_OVERWORLD_COINS_1 0x04
#define PALETTE_OVERWORLD_COINS_2 0x05
#define PALETTE_OVERWORLD_COINS_3 0x06
#define PALETTE_UNDERGROUND_COINS_1 0x07
#define PALETTE_UNDERGROUND_COINS_2 0x08
#define PALETTE_UNDERGROUND_COINS_3 0x09
#define PALETTE_CASTLE_COINS_1 0x0a
#define PALETTE_CASTLE_COINS_2 0x0b
#define PALETTE_CASTLE_COINS_3 0x0c
#define PALETTE_UNDERWATER_COINS_1 0x0d
#define PALETTE_UNDERWATER_COINS_2 0x0e
#define PALETTE_UNDERWATER_COINS_3 0x0f

#define PALETTE_COUNT 0x10

struct color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

struct palette {
    struct color c1;
    struct color c2;
    struct color c3;
};

extern const struct palette palettes[];

#endif