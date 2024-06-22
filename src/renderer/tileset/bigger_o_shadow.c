#include "renderer/tileset/tileset.h"
#include "renderer/data/tiles.h"

const struct tileset bigger_o_shadow = {
    .width = 2,
    .height = 5,
    .tiles = (unsigned char[]) {
        TILE_BIGGER_O_SHADOW_1,
        TILE_BIGGER_O_SHADOW_2,
        TILE_BIGGER_O_SHADOW_3,
        TILE_BIGGER_O_SHADOW_4,
        TILE_BIGGER_O_SHADOW_5,
        TILE_BIGGER_O_SHADOW_6,
        TILE_BIGGER_O_SHADOW_7,
        TILE_BIGGER_O_SHADOW_8,
        TILE_BIGGER_O_SHADOW_9,
        TILE_BIGGER_O_SHADOW_10,
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