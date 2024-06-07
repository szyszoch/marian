#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include "settings.h"
#include "renderer.h"

extern const char *assets_fragment_shader;
extern const char *assets_vertex_shader;
extern const unsigned int assets_tiles[][4];
extern const unsigned char assets_palettes[][3][3];

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

static struct {
    unsigned int pixel_size;
    unsigned int tiles;
    unsigned int tile_count;
    unsigned int palettes;
    unsigned int palette_count;
} uniforms;

static struct {
    unsigned int tiles;
    unsigned int palettes;
} textures;

static unsigned int shader;
static float background_color[3];

static void parse_tile_data(unsigned char *dst, const unsigned int *src)
{
    for (unsigned char i = 0; i < 64; i++)
        dst[i] = src[i / 16] >> (30 - (i * 2 % 32)) & 3;
}

static unsigned int init_shader(unsigned int t, const char *src)
{
    unsigned int sh = glCreateShader(t);
    glShaderSource(sh, 1, &src, NULL);
    glCompileShader(sh);
    int ll;
    glGetShaderiv(sh, GL_INFO_LOG_LENGTH, &ll);
    if (ll) {
        char *b = malloc(ll);
        glGetShaderInfoLog(sh, ll, NULL, b);
        fprintf(stderr, "Shader error:\n%s\n", b);
        free(b);
        glDeleteShader(sh);
        sh = 0;
    }
    return sh;
}

static unsigned int init_program(const char *vs, const char *fs)
{
    unsigned int v = init_shader(GL_VERTEX_SHADER, vs);
    unsigned int f = init_shader(GL_FRAGMENT_SHADER, fs);
    unsigned int p = glCreateProgram();
    glAttachShader(p, v);
    glAttachShader(p, f);
    glLinkProgram(p);
    glDeleteShader(v);
    glDeleteShader(f);
    int ll;
    glGetProgramiv(p, GL_INFO_LOG_LENGTH, &ll);
    if (ll) {
        char *b = malloc(ll);
        glGetProgramInfoLog(p, ll, NULL, b);
        fprintf(stderr, "program error:\n%s\n", b);
        free(b);
        glDeleteProgram(p);
        p = 0;
    }
    return p;
}

int init_renderer()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    shader = init_program(assets_vertex_shader, assets_fragment_shader);
    if (!shader)
        return -1;
    glUseProgram(shader);

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

    uniforms.pixel_size = glGetUniformLocation(shader, "pixel_size");
    uniforms.tiles = glGetUniformLocation(shader, "tiles");
    uniforms.palettes = glGetUniformLocation(shader, "palettes");
    uniforms.tile_count = glGetUniformLocation(shader, "tile_count");
    uniforms.palette_count = glGetUniformLocation(shader, "palette_count");

    glUniform2f(uniforms.pixel_size, 2.0f / GAME_WIDTH, 2.0f / GAME_HEIGHT);
    glUniform1i(uniforms.tiles, 0);
    glUniform1i(uniforms.palettes, 1);
    glUniform1f(uniforms.tile_count, (float) TILE_COUNT);
    glUniform1f(uniforms.palette_count, (float) PALETTE_COUNT);

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &textures.tiles);
    glBindTexture(GL_TEXTURE_2D, textures.tiles);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, 8 * TILE_COUNT, 8, 0, GL_RED,
                 GL_UNSIGNED_BYTE, NULL);
    for (unsigned char i = 0; i < TILE_COUNT; i++) {
        unsigned char tile[64];
        parse_tile_data(tile, assets_tiles[i]);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 8 * i, 0, 8, 8, GL_RED,
                        GL_UNSIGNED_BYTE, tile);
    }

    glActiveTexture(GL_TEXTURE1);
    glGenTextures(1, &textures.palettes);
    glBindTexture(GL_TEXTURE_2D, textures.palettes);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 3, PALETTE_COUNT, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, NULL);
    for (unsigned char i = 0; i < PALETTE_COUNT; i++) {
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, i, 3, 1, GL_RGB,
                        GL_UNSIGNED_BYTE, assets_palettes[i]);
    }

    set_background_color(0, 0, 0);
    return glGetError();
}

void destroy_renderer()
{
    glDeleteTextures(1, &textures.tiles);
    glDeleteTextures(1, &textures.palettes);
    glDeleteBuffers(1, &buffers.quad);
    glDeleteBuffers(1, &buffers.pos);
    glDeleteBuffers(1, &buffers.tile);
    glDeleteBuffers(1, &buffers.palette);
    glDeleteVertexArrays(1, &buffers.vao);
    glDeleteProgram(shader);
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