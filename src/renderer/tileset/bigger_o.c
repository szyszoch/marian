#include "tileset.h"
#include "tiles.h"

const struct tileset bigger_o = {
    .width = 2,
    .height = 5,
    .tiles = (unsigned char[]) {
        TILE_BIGGER_O_1,
        TILE_BIGGER_O_2,
        TILE_BIGGER_O_3,
        TILE_BIGGER_O_4,
        TILE_BIGGER_O_5,
        TILE_BIGGER_O_6,
        TILE_BIGGER_O_7,
        TILE_BIGGER_O_8,
        TILE_BIGGER_O_9,
        TILE_BIGGER_O_10,
    },
    .flips = (unsigned char[]) {
        FLIP_NONE,
        FLIP_HORIZONTAL,
        FLIP_NONE,
        FLIP_NONE,
        FLIP_NONE,
        FLIP_NONE,
        FLIP_NONE,
        FLIP_NONE,
        FLIP_VERTICAL,
        FLIP_VERTICAL | FLIP_HORIZONTAL,
    },
};