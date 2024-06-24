#ifndef PALETTESET_H
#define PALETTESET_H

#include "biome.h"

#define PALETTESET_STONE 0x00
#define PALETTESET_COINS_1 0x01
#define PALETTESET_COINS_2 0x02
#define PALETTESET_COINS_3 0x03
#define PALETTESET_TEXT 0x04
#define PALETTESET_COUNT 0x05

extern const unsigned char palette_sets[][BIOME_COUNT];

#endif