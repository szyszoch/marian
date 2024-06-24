#include "tileset.h"
#include "tiles.h"

const struct tileset big_r = {
    .width = 2,
    .height = 3,
    .tiles = (unsigned char[]) {
        TILE_BIG_R_1,
        TILE_BIG_R_2,
        TILE_BIG_R_3,
        TILE_BIG_R_4,
        TILE_BIG_R_5,
        TILE_BIG_R_6,
    },
    .flips = (unsigned char[]) {
        FLIP_NONE,
        FLIP_HORIZONTAL,
        FLIP_NONE,
        FLIP_NONE,
        FLIP_NONE,
        FLIP_NONE,
    },
};