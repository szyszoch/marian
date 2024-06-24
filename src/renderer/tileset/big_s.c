#include "tileset.h"
#include "tiles.h"

const struct tileset big_s = {
    .width = 2,
    .height = 3,
    .tiles = (unsigned char[]) {
        TILE_BIG_S_1,
        TILE_BIG_S_2,
        TILE_BIG_S_3,
        TILE_BIG_S_4,
        TILE_BIG_S_5,
        TILE_BIG_S_6,
    },
    .flips = (unsigned char[]) {
        FLIP_NONE,
        FLIP_HORIZONTAL,
        FLIP_NONE,
        FLIP_NONE,
        FLIP_VERTICAL,
        FLIP_VERTICAL | FLIP_HORIZONTAL,
    },
};