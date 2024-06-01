#ifndef RENDERER_H
#define RENDERER_H

#include "data/data.h"

int renderer_init();
void renderer_destroy();
void renderer_render(unsigned char tile, short x, short y,
                     unsigned char palette);

#endif