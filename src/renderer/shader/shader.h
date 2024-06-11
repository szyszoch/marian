#ifndef SHADER_H
#define SHADER_H

int shader_init();
void shader_destroy();
void shader_bind();
void shader_set_tile_count(int tc);
void shader_set_palette_count(int pc);
void shader_set_tiles_texture(int tt);
void shader_set_palettes_texture(int pt);
void shader_set_game_dims(float gw, float gh);

#endif