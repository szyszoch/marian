#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include "renderer/opengl.h"
#include "renderer/renderer.h"
#include "settings.h"

#define VBO_QUAD    0x00
#define VBO_POS     0x01
#define VBO_TILE    0x02
#define VBO_PALETTE 0x03
#define VBO_COUNT   0x04

#define VBO_QUAD_SIZE       (sizeof(float) * 8)
#define VBO_POS_SIZE        (sizeof(float) * 2)
#define VBO_TILE_SIZE       (sizeof(float))
#define VBO_PALETTE_SIZE    (sizeof(float))

#define TEX_TILES       0x00
#define TEX_PALETTES    0x01
#define TEX_COUNT       0x02

extern const char *vertex_shader;
extern const char *fragment_shader;

static float background_color[3];

static struct {
    unsigned int vao;
    unsigned int vbo[4];
    struct {
        float *pos;
        float *tile;
        float *palette;
        unsigned int count;
        unsigned int max;
    } data;
} buffer;

static unsigned int program; 
static unsigned int texture[2];

static int init_buffers(unsigned int n)
{
    glGenVertexArrays(1, &buffer.vao);
    glBindVertexArray(buffer.vao);

    glGenBuffers(VBO_COUNT, buffer.vbo);

    const float quad[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
    };
    glBindBuffer(GL_ARRAY_BUFFER, buffer.vbo[VBO_QUAD]);
    glBufferData(GL_ARRAY_BUFFER, VBO_QUAD_SIZE, quad, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, 0, 0, NULL);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, buffer.vbo[VBO_POS]);
    glBufferData(GL_ARRAY_BUFFER, VBO_POS_SIZE * n, NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, 0, 0, NULL);
    glVertexAttribDivisor(1, 1);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, buffer.vbo[VBO_TILE]);
    glBufferData(GL_ARRAY_BUFFER, VBO_TILE_SIZE * n, NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(2, 1, GL_FLOAT, 0, 0, NULL);
    glVertexAttribDivisor(2, 1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, buffer.vbo[VBO_PALETTE]);
    glBufferData(GL_ARRAY_BUFFER, VBO_PALETTE_SIZE * n, NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(3, 1, GL_FLOAT, 0, 0, NULL);
    glVertexAttribDivisor(3, 1);
    glEnableVertexAttribArray(3);

    buffer.data.pos = malloc(VBO_POS_SIZE * n);
    buffer.data.tile = malloc(VBO_TILE_SIZE * n);
    buffer.data.palette = malloc(VBO_PALETTE_SIZE * n);
    buffer.data.count = 0;
    buffer.data.max = n;

    return glGetError();
}

int init_program()
{
    program = gl_init_program(vertex_shader, fragment_shader);
    if (!program)
        return -1;
    glUseProgram(program);

    unsigned int tiles = glGetUniformLocation(program, "tiles");
    unsigned int palettes = glGetUniformLocation(program, "palettes");
    unsigned int tile_count = glGetUniformLocation(program, "tile_count");
    unsigned int palette_count = glGetUniformLocation(program, "palette_count");
    unsigned int pixel_size = glGetUniformLocation(program, "pixel_size");

    glUniform1i(tiles, 0);
    glUniform1i(palettes, 1);
    glUniform1f(tile_count, TILE_COUNT);
    glUniform1f(palette_count, PALETTE_COUNT);
    glUniform2f(pixel_size, 2.0f / GAME_WIDTH, 2.0f / GAME_HEIGHT);

    return glGetError();
}

int init_tilemap()
{
    glActiveTexture(GL_TEXTURE0);
    texture[TEX_TILES] = gl_init_texture(GL_R8, GL_UNSIGNED_BYTE,
        8 * TILE_COUNT, 8, NULL);
    for (unsigned char i = 0; i < TILE_COUNT; i++) {
        struct tile_data td = get_tile_data(i);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 8 * i, 0, 8, 8, GL_RED,
                        GL_UNSIGNED_BYTE, &td);
    }
    glActiveTexture(GL_TEXTURE1);
    texture[TEX_PALETTES] = gl_init_texture(GL_RGB8, GL_UNSIGNED_BYTE, 3, 
        PALETTE_COUNT, NULL);
    for (unsigned char i = 0; i < PALETTE_COUNT; i++) {
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, i, 3, 1, GL_RGB,
                        GL_UNSIGNED_BYTE, &palettes[i]);
    }
    return glGetError();
}

int init_renderer()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (init_program()) {
        fprintf(stderr, "Failed to initialize shader program\n");
        return -1;
    }

    if (init_tilemap()) {
        fprintf(stderr, "Failed to initialize tilemap\n");
        return -1;    
    }

    if (init_buffers(BATCH_SIZE)) {
        fprintf(stderr, "Failed to initialize renderer buffers\n");
        return -1;
    }
        
    set_background_color(0, 0, 0);
    return glGetError();
}

void destroy_renderer()
{
    glDeleteBuffers(VBO_COUNT, buffer.vbo);
    glDeleteVertexArrays(1, &buffer.vao);
    glDeleteTextures(TEX_COUNT, texture);
    glDeleteProgram(program);
}

void render_tile(unsigned char tile, short x, short y, unsigned char palette)
{
    if (buffer.data.count >= buffer.data.max) {
        present_renderer();
        return;
    } 
    buffer.data.pos[buffer.data.count * 2] = x;
    buffer.data.pos[buffer.data.count * 2 + 1] = y;
    buffer.data.tile[buffer.data.count] = tile;
    buffer.data.palette[buffer.data.count] = palette;
    buffer.data.count++;
}

void present_renderer()
{
    glBindBuffer(GL_ARRAY_BUFFER, buffer.vbo[VBO_POS]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, VBO_POS_SIZE * buffer.data.count,
        buffer.data.pos);

    glBindBuffer(GL_ARRAY_BUFFER, buffer.vbo[VBO_TILE]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, VBO_TILE_SIZE * buffer.data.count,
        buffer.data.tile);

    glBindBuffer(GL_ARRAY_BUFFER, buffer.vbo[VBO_PALETTE]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, VBO_PALETTE_SIZE * buffer.data.count,
        buffer.data.palette);

    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, buffer.data.count);
    buffer.data.count = 0;
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