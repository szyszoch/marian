#ifndef TILEMAP_H
#define TILEMAP_H

int tilemap_init();
void tilemap_destroy();
void tilemap_bind_tiles(int tex_slot);
void tilemap_bind_palettes(int tex_slot);

#endif