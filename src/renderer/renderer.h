#ifndef RENDERER_H
#define RENDERER_H

#include "renderer/tilemap/tiles.h"
#include "renderer/tilemap/palettes.h"

#define FLIP_NONE 0x00
#define FLIP_RIGHT 0x01
#define FLIP_HORIZONTAL 0x02
#define FLIP_VERTICAL 0x04

int init_renderer();
void destroy_renderer();
void render_tile(unsigned char tile, short x, short y, unsigned char palette);
void present_renderer();
void clear_renderer();
void set_background_color(unsigned char r, unsigned char g,
                                   unsigned char b);
void render_set_of_tiles(const unsigned char *tiles, short x, short y,
                         unsigned char width, unsigned char height,
                         unsigned char palette);
void render_number_with_zero_padding(unsigned int number, unsigned char size,
                                     short x, short y);
void render_number(unsigned int number, short end_x, short y);
void render_text(const char *text, short x, short y);
void render_1_player_hud();
void render_copyright(short x, short y);

#endif