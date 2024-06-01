#ifndef DATA_H
#define DATA_H

#define FLIP_NONE       0x00
#define FLIP_RIGHT      0x01
#define FLIP_HORIZONTAL 0x02
#define FLIP_VERTICAL   0x04

#define TILE_NONE           0x00
#define TILE_FIRST_COLOR    0x01
#define TILE_SECOND_COLOR   0x02
#define TILE_THIRD_COLOR    0x03

#define TILE_GROUND_1       0x04
#define TILE_GROUND_2       0x05
#define TILE_GROUND_3       0x06
#define TILE_GROUND_4       0x07

#define TILE_COUNT          0x08

#define PALETTE_OVERWORLD_GROUND_AND_STONE      0x00
#define PALETTE_UNDERGROUND_GROUND_AND_STONE    0x01
#define PALETTE_CASTLE_GROUND_AND_STONE         0x02
#define PALETTE_UNDERWATER_GROUND_AND_STONE     0x03
#define PALETTE_COUNT                           0x04

#define TEXTURE_GROUND  0x00
#define TEXTURE_COUNT   0x01

#define SHADER_VERTEX_2D_TEXTURES           0x00
#define SHADER_FRAGMENT_INDEXED_TILEMAP     0x01
#define SHADER_COUNT                        0x02

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

typedef struct texture {
    unsigned char width;
    unsigned char height;
    unsigned char *tiles;
    unsigned char *flips;
} texture_t;

void data_get_tile(unsigned char tile, unsigned char output[64]);
void data_get_palette(unsigned char palette, palette_t *output);
void data_get_texture(unsigned char texture, texture_t *output);
const char *data_get_shader(unsigned char shader);

#endif