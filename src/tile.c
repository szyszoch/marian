#include <tile.h>

tile_t tile_get(unsigned int tile_id)
{
    const unsigned char ground_0[16] = {0x95, 0x55, 0x6a, 0xaa, 0x6a, 0xaa, 0x6a, 0xaa, 0x6a, 0xaa, 0x6a, 0xaa, 0x6a, 0xaa, 0x6a, 0xaa};
    const unsigned char ground_1[16] = {0x79, 0x56, 0xb6, 0xab, 0xb6, 0xab, 0xb6, 0xab, 0xb7, 0xab, 0xbb, 0xfe, 0xb5, 0x57, 0xb6, 0xab};
    const unsigned char ground_2[16] = {0x6a, 0xaa, 0x6a, 0xaa, 0xfa, 0xaa, 0x5f, 0xaa, 0x65, 0xff, 0x6a, 0x57, 0x6a, 0xab, 0xbf, 0xfe};
    const unsigned char ground_3[16] = {0xb6, 0xab, 0xb6, 0xab, 0xda, 0xab, 0xda, 0xab, 0x6a, 0xab, 0x6a, 0xab, 0x6a, 0xaf, 0x7f, 0xfe};

    tile_t tile;

    switch(tile_id) {
        case TILE_GROUND_0: memcpy(tile.data, ground_0, 16); break;
        case TILE_GROUND_1: memcpy(tile.data, ground_1, 16); break;
        case TILE_GROUND_2: memcpy(tile.data, ground_2, 16); break;
        case TILE_GROUND_3: memcpy(tile.data, ground_3, 16); break;
        default: memset(tile.data, 0, 16);
    }

    return tile;
}

unsigned int tile_get_color_index(tile_t tile, unsigned int x, unsigned int y)
{
    const unsigned int data_index = x + y * TILE_HEIGHT;
    const unsigned int byte_index = data_index >> 2;
    const unsigned int byte_offset = (3 - (data_index & 3)) * 2;
    return (tile.data[byte_index] >> byte_offset) & 3;
}