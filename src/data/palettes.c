#include "data.h"

/**
 *  Each tile is composed of four different colors. One of these colors
 *  is always set to 100% transparency. Therefore, only three colors per
 *  palette are stored.
 */

static const palette_t palettes[] = {
    {
        .first_color =  {0xff, 0xce, 0xc5},
        .second_color = {0x9c, 0x4a, 0x00},
        .third_color =  {0x00, 0x00, 0x00},
    },
};

void data_get_palette(unsigned char palette, palette_t *output)
{
    if (palette >= PALETTE_COUNT)
        return;
    *output = palettes[palette];
}