#include "renderer/tileset/tileset.h"
#include "renderer/data/tiles.h"

const struct tileset bigger_s = {
    .width = 2,
    .height = 5,
    .tiles = (unsigned char[]) {
        TILE_BIGGER_S_1,
        TILE_BIGGER_S_2,
        TILE_BIGGER_S_3,
        TILE_BIGGER_S_4,
        TILE_BIGGER_S_5,
        TILE_BIGGER_S_6,
        TILE_BIGGER_S_7,
        TILE_BIGGER_S_8,
        TILE_BIGGER_S_9,
        TILE_BIGGER_S_10,
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