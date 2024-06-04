#ifndef RENDERER_H
#define RENDERER_H

#include "data/data.h"

int renderer_init();
void renderer_destroy();
void renderer_render(unsigned char tile, short x, short y,
                     unsigned char palette);
void renderer_present();
void renderer_clear();
void renderer_set_background_color(unsigned char r, unsigned char g,
                                   unsigned char b);

#endif