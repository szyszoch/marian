#include "renderer/renderer.h"

static const unsigned char digits_tiles[10] = {
    TILE_0, TILE_1, TILE_2, TILE_3, TILE_4,
    TILE_5, TILE_6, TILE_7, TILE_8, TILE_9,
};

void render_number_with_zero_padding(unsigned int number, unsigned char size,
                                     short x, short y)
{
    while(size--) {
        render_tile(digits_tiles[number % 10], x + size * 8, y,
                        PALETTE_CASTLE_GROUND_AND_STONE);
        number /= 10;
    } 
}

void render_number(unsigned int number, short end_x, short y)
{
    do {
        render_tile(digits_tiles[number % 10], end_x, y,
                    PALETTE_CASTLE_GROUND_AND_STONE);
        end_x -= 8;
    } while (number /= 10);
}
