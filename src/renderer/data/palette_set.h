#ifndef PALETTE_SET_H
#define PALETTE_SET_H

#include "renderer/data/biome.h"

#define PALETTE_SET_GROUND_AND_STONE 0x00
#define PALETTE_SET_COINS_1 0x01
#define PALETTE_SET_COINS_2 0x02
#define PALETTE_SET_COINS_3 0x03
#define PALETTE_SET_TEXT 0x04
#define PALETTE_SET_COUNT 0x05

extern const unsigned char palette_sets[][BIOME_COUNT];

#endif