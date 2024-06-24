#ifndef RENDERER_H
#define RENDERER_H

#include "biome.h"

#define TEXTURE_LOGO 0x00
#define TEXTURE_COUNT 0x01

int renderer_init();
void renderer_destroy();
void renderer_present();
void renderer_clear();
void renderer_1_player_hud();
void renderer_texture(unsigned char t, short x, short y);
void renderer_set_biome(unsigned char b);

#endif