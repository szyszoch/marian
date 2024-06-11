#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include "settings.h"
#include "renderer/renderer.h"
#include "renderer/shader/shader.h"
#include "renderer/tilemap/tilemap.h"
#include "renderer/buffer/buffer.h"

static float background_color[3];

int init_renderer()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (shader_init())
        return -1;
    shader_bind();
    shader_set_palette_count(PALETTE_COUNT);
    shader_set_tile_count(TILE_COUNT);
    shader_set_game_dims(GAME_WIDTH, GAME_HEIGHT);
    shader_set_tiles_texture(0);
    shader_set_palettes_texture(1);

    if (tilemap_init())
        return -1;
    tilemap_bind_tiles(0);
    tilemap_bind_palettes(1);

    if (buffer_init(BATCH_SIZE))
        return -1;
    buffer_bind();

    set_background_color(0, 0, 0);
    return glGetError();
}

void destroy_renderer()
{
    buffer_destroy();
    tilemap_destroy();
    shader_destroy();
}

void render_tile(unsigned char tile, short x, short y, unsigned char palette)
{
    buffer_add((float) x, (float) y, (float) tile, (float) palette);
}

void present_renderer()
{
    buffer_send_to_shader();
}

void clear_renderer()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(background_color[0], background_color[1], background_color[2],
                 1.0f);
}

void set_background_color(unsigned char r, unsigned char g,
                                   unsigned char b)
{
    background_color[0] = (float) r / 0xff;
    background_color[1] = (float) g / 0xff;
    background_color[2] = (float) b / 0xff;
}

void render_set_of_tiles(const unsigned char *tiles, short x, short y,
                         unsigned char width, unsigned char height,
                         unsigned char palette)
{
    for (unsigned char w = 0; w < width; w++) {
        for (unsigned char h = 0; h < height; h++) {
            render_tile(tiles[w + h * width], x + w * 8, y + h * 8, palette);
        }
    }
}