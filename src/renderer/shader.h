#ifndef SHADER_H
#define SHADER_H

int shader_init();
void shader_destroy();
void shader_bind();
void shader_set_tile_count(int tc);
void shader_set_palette_count(int pc);
void shader_set_tiles(int t);
void shader_set_palettes(int p);
void shader_set_pixel_size(float w, float h);

#endif