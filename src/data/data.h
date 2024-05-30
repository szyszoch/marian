#ifndef DATA_H
#define DATA_H

#define TILE_NONE           0x00
#define TILE_FIRST_COLOR    0x01
#define TILE_SECOND_COLOR   0x02
#define TILE_THIRD_COLOR    0x03

#define TILE_GROUND_1       0x04
#define TILE_GROUND_2       0x05
#define TILE_GROUND_3       0x06
#define TILE_GROUND_4       0x07

#define TILE_COUNT          0x08

#define PALETTE_OVERWORLD_GROUND_AND_STONE 0x00
#define PALETTE_COUNT 0x01

typedef struct color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} color_t;

typedef struct palette {
    color_t first_color;
    color_t second_color;
    color_t third_color;
} palette_t;

void data_get_tile(unsigned char tile, unsigned char output[64]);
void data_get_palette(unsigned char palette, palette_t *output);

#endif