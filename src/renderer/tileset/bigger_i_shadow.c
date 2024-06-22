#include "renderer/tileset/tileset.h"
#include "renderer/data/tiles.h"

const struct tileset bigger_i_shadow = {
    .width = 1,
    .height = 5,
    .tiles = (unsigned char[]) {
        TILE_BIGGER_I_SHADOW_1,
        TILE_BIGGER_I_SHADOW_2,
        TILE_BIGGER_I_SHADOW_3,
        TILE_BIGGER_I_SHADOW_4,
        TILE_BIGGER_I_SHADOW_5,
    },
    .flips = (unsigned char[]) {
        FLIP_NONE,
        FLIP_NONE,
        FLIP_NONE,
        FLIP_NONE,
        FLIP_NONE,
    },
};