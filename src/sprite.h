#ifndef SPRITE_H
#define SPRITE_H

#include <palette.h>
#include <tile.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#define SPRITE_GROUND 0

typedef struct sprite {
    unsigned char* pixels;
    unsigned int width;
    unsigned int height;
} sprite_t;

sprite_t sprite_get(unsigned int sprite_id, palette_t palette);
void sprite_destroy(sprite_t sprite);

#endif