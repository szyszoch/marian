#ifndef TILE_H
#define TILE_H

#include <memory.h>

/* Tile store 8x8 array of color indices 2 bits per pixel.  */

#define TILE_WIDTH 8
#define TILE_HEIGHT 8

#define TILE_GROUND_0 0
#define TILE_GROUND_1 1
#define TILE_GROUND_2 2
#define TILE_GROUND_3 3

typedef struct tile {
    unsigned char data[16];
} tile_t;

tile_t tile_get(unsigned int tile_id);
unsigned int tile_get_color_index(tile_t tile, unsigned int x, unsigned int y);

#endif