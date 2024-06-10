#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include "settings.h"
#include "renderer/renderer.h"
#include "renderer/shader.h"
#include "renderer/tilemap.h"

static struct {
    float pos[BATCH_SIZE][2];
    float tile[BATCH_SIZE];
    float palette[BATCH_SIZE];
    unsigned int count;
} render_list;

static struct {
    unsigned int vao;
    unsigned int quad;
    unsigned int pos;
    unsigned int palette;
    unsigned int tile;
} buffers;

static float background_color[3];

int init_renderer()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (shader_init())
        return -1;
    shader_bind();

    if (tilemap_init())
        return -1;
    tilemap_bind();

    glGenVertexArrays(1, &buffers.vao);
    glBindVertexArray(buffers.vao);

    const float quad[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
    };
    glGenBuffers(1, &buffers.quad);
    glBindBuffer(GL_ARRAY_BUFFER, buffers.quad);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad) * BATCH_SIZE, quad,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, 0, 0, NULL);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &buffers.pos);
    glBindBuffer(GL_ARRAY_BUFFER, buffers.pos);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * BATCH_SIZE, 
                 NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, 0, 0, NULL);
    glVertexAttribDivisor(1, 1);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &buffers.tile);
    glBindBuffer(GL_ARRAY_BUFFER, buffers.tile);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * BATCH_SIZE, NULL,
                 GL_DYNAMIC_DRAW);
    glVertexAttribPointer(2, 1, GL_FLOAT, 0, 0, NULL);
    glVertexAttribDivisor(2, 1);
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &buffers.palette);
    glBindBuffer(GL_ARRAY_BUFFER, buffers.palette);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * BATCH_SIZE, NULL,
                 GL_DYNAMIC_DRAW);
    glVertexAttribPointer(3, 1, GL_FLOAT, 0, 0, NULL);
    glVertexAttribDivisor(3, 1);
    glEnableVertexAttribArray(3);

    shader_set_palette_count(PALETTE_COUNT);
    shader_set_tile_count(TILE_COUNT);
    shader_set_pixel_size(2.0f / GAME_WIDTH, 2.0f / GAME_HEIGHT);
    shader_set_tiles(0);
    shader_set_palettes(1);
    set_background_color(0, 0, 0);
    return glGetError();
}

void destroy_renderer()
{
    glDeleteBuffers(1, &buffers.quad);
    glDeleteBuffers(1, &buffers.pos);
    glDeleteBuffers(1, &buffers.tile);
    glDeleteBuffers(1, &buffers.palette);
    glDeleteVertexArrays(1, &buffers.vao);
    tilemap_destroy();
    shader_destroy();
}

void render_tile(unsigned char tile, short x, short y, unsigned char palette)
{
    if (render_list.count >= BATCH_SIZE) {
        present_renderer();
    }
    else {
        render_list.pos[render_list.count][0] = (float) x;
        render_list.pos[render_list.count][1] = (float) y;
        render_list.tile[render_list.count] = (float) tile;
        render_list.palette[render_list.count] = (float) palette;
        render_list.count++;
    }
}

void present_renderer()
{
    glBindBuffer(GL_ARRAY_BUFFER, buffers.pos);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 2 *
                    render_list.count, render_list.pos);

    glBindBuffer(GL_ARRAY_BUFFER, buffers.tile);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) *
                    render_list.count, render_list.tile);

    glBindBuffer(GL_ARRAY_BUFFER, buffers.palette);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 
                    render_list.count, render_list.palette);

    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, render_list.count);
    render_list.count = 0;
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