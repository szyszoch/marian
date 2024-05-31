#include "data.h"

/**
 *  Textures are sets of tiles combined together with available rotations for
 *  each tile. The order of tiles is from left to right and then from top to
 *  bottom. There are three possible flags for rotations: FLIP_RIGHT,
 *  FLIP_VERTICAL and FLIP_HORIZONTAL. Those rotations allow to reduce
 *  count of many tiles, especially for characters who can change their
 *  direction.
*/

static const texture_t textures[] = {
    {
        .width = 2,
        .height = 2,
        .tiles = (unsigned char[]) {
            TILE_GROUND_1,
            TILE_GROUND_2,
            TILE_GROUND_3,
            TILE_GROUND_4,
        },
        .flips = (unsigned char[]) {
            FLIP_NONE,
            FLIP_NONE,
            FLIP_NONE,
            FLIP_NONE,
        },
    },
};

void data_get_texture(unsigned char texture, texture_t *output)
{
    if (texture >= TEXTURE_COUNT)
        return;
    *output = textures[texture];
}