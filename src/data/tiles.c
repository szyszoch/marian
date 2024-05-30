#include "data.h"

/**
 * Every tile in the program is an 8x8 texture with only 4 colours.
 * They are also indexed textures, which means they store only indexes to
 * colours instead of the actual colours. This allows me to store them in
 * just 2 bits. Since every tile is built of 64 pixels, I need just four
 * unsigned ints to store one tile.
 */

static const unsigned int tiles[][4] = {
    {0x00000000, 0x00000000, 0x00000000, 0x00000000},
    {0x55555555, 0x55555555, 0x55555555, 0x55555555},
    {0xaaaaaaaa, 0xaaaaaaaa, 0xaaaaaaaa, 0xaaaaaaaa},
    {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff},
    {0x95556aaa, 0x6aaa6aaa, 0x6aaa6aaa, 0x6aaa6aaa},
    {0x7956b6ab, 0xb6abb6ab, 0xb7abbbfe, 0xb55fb6ab},
    {0x6aaa6aaa, 0xfaaa5faa, 0x65ff6a57, 0x6aabbffe},
    {0xb6abb6ab, 0xdaabdaab, 0x6aab6aab, 0x6aaf7ffe},
};

void data_get_tile(unsigned char tile, unsigned char output[64])
{
    if (tile >= TILE_COUNT)
        return;
    for (unsigned char i = 0; i < 64; i++)
        output[i] = tiles[tile][i / 16] >> (30 - (i * 2 % 32)) & 3;
}