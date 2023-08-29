#include <sprite.h>

static void fill_pixels(sprite_t sprite, unsigned int tile_id, palette_t palette, unsigned int x_offset, unsigned int y_offset)
{
    tile_t tile = tile_get(tile_id);

    for (int x = 0; x < TILE_WIDTH; x++) {
        for (int y = 0; y < TILE_HEIGHT; y++) {
            unsigned int sprite_y = y + y_offset;
            unsigned int sprite_x = x + x_offset;
            unsigned int color_index = tile_get_color_index(tile, x, y);
            sprite.pixels[sprite_y * sprite.width + sprite_x] = palette.color[color_index];
        }
    }
}

static void flip_pixels_upside_down(sprite_t sprite) 
{
    unsigned int size = sprite.height * sprite.width;
    unsigned char buffer[size];
    memcpy(buffer, sprite.pixels, size);

    for(unsigned int y = 0; y < sprite.height; y++) {
        for (unsigned int x = 0; x < sprite.width; x++) {
            sprite.pixels[y * sprite.width + x] = buffer[(sprite.height - y - 1) * sprite.width + x];
        }
    }
}

sprite_t sprite_get(unsigned int sprite_id, palette_t palette)
{
    sprite_t sprite;
    
    switch(sprite_id) {
        case SPRITE_GROUND:
            sprite.width = 16;
            sprite.height = 16;
            sprite.pixels = malloc(sprite.width * sprite.height);
            fill_pixels(sprite, TILE_GROUND_0, palette, 0, 0);
            fill_pixels(sprite, TILE_GROUND_1, palette, 8, 0);
            fill_pixels(sprite, TILE_GROUND_2, palette, 0, 8);
            fill_pixels(sprite, TILE_GROUND_3, palette, 8, 8);
            break;
    }

    flip_pixels_upside_down(sprite);
    return sprite;
}

void sprite_destroy(sprite_t sprite)
{
    free(sprite.pixels);
    memset(&sprite, 0, sizeof(sprite_t));
}