#ifndef PALETTE_H
#define PALETTE_H

#include <memory.h>

/* Palette has 4 colors in R3_G3_B2 format */

typedef struct palette {
    unsigned char color[4];
} palette_t;

#define PALETTE_OVERWORLD_GROUND_AND_STONE 0
#define PALETTE_UNDERGROUND_GROUND_AND_STONE 1
#define PALETTE_CASTLE_GROUND_AND_STONE 2
#define PALETTE_UNDERWATER_GROUND_AND_STONE 3

palette_t palette_get(unsigned int palette_id);

#endif