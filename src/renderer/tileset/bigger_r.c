#include "renderer/tileset/tileset.h"
#include "renderer/data/tiles.h"

const struct tileset bigger_r = {
    .width = 2,
    .height = 5,
    .tiles = (unsigned char[]) {
        TILE_BIGGER_R_1,
        TILE_BIGGER_R_2,
        TILE_BIGGER_R_3,
        TILE_BIGGER_R_4,
        TILE_BIGGER_R_5,
        TILE_BIGGER_R_6,
        TILE_BIGGER_R_7,
        TILE_BIGGER_R_8,
        TILE_BIGGER_R_9,
        TILE_BIGGER_R_10,
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
        FLIP_NONE,
        FLIP_NONE,
    },
};