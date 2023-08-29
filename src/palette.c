#include <palette.h>

palette_t palette_get(unsigned int palette_id)
{
    unsigned char overworld_ground_and_stone[4] = {0x93, 0xfa, 0x88, 0x00};
    unsigned char underground_ground_and_stone[4] = {0x93, 0xbb, 0x0e, 0x00};
    unsigned char castle_ground_and_stone[4] = {0x93, 0xff, 0xb6, 0x49};
    unsigned char underwater_ground_and_stone[4] = {0x93, 0xbe, 0x10, 0x00};

    palette_t palette;

    switch(palette_id) {
        case PALETTE_OVERWORLD_GROUND_AND_STONE: memcpy(&palette.color, &overworld_ground_and_stone, 4); break;
        case PALETTE_UNDERGROUND_GROUND_AND_STONE: memcpy(&palette.color, &underground_ground_and_stone, 4); break;
        case PALETTE_CASTLE_GROUND_AND_STONE: memcpy(&palette.color, &castle_ground_and_stone, 4); break;
        case PALETTE_UNDERWATER_GROUND_AND_STONE: memcpy(&palette.color, &underwater_ground_and_stone, 4); break;
        default: memset(&palette, 0, 4);
    }

    return palette;
}