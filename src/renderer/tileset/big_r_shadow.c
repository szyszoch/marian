#include "renderer/tileset/tileset.h"
#include "renderer/data/tiles.h"

const struct tileset big_r_shadow = {
    .width = 2,
    .height = 3,
    .tiles = (unsigned char[]) {
        TILE_BIG_R_SHADOW_1,
        TILE_BIG_R_SHADOW_2,
        TILE_BIG_R_SHADOW_3,
        TILE_BIG_R_SHADOW_4,
        TILE_BIG_R_SHADOW_5,
        TILE_BIG_R_SHADOW_6,
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