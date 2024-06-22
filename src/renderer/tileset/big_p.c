#include "renderer/tileset/tileset.h"
#include "renderer/data/tiles.h"

const struct tileset big_p = { 
    .width = 2,
    .height = 3,
    .tiles = (unsigned char[]) {
        TILE_BIG_P_1,
        TILE_BIG_P_2,
        TILE_BIG_P_3,
        TILE_BIG_P_4,
        TILE_BIG_P_5,
        TILE_BIG_P_6,
    },
    .flips = (unsigned char[]) {
        FLIP_NONE,
        FLIP_HORIZONTAL,
        FLIP_NONE,
        FLIP_VERTICAL | FLIP_HORIZONTAL,
        FLIP_NONE,
        FLIP_NONE,
    },
};