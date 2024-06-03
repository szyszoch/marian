#include <glad/glad.h>
#include "renderer.h"
#include <stdio.h>
#include <stdlib.h>
#include "settings.h"

static unsigned int shader;

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

int renderer_init()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    const char *vertex_src = data_get_shader(SHADER_VERTEX_2D_TEXTURES);
    const char *frag_src = data_get_shader(SHADER_FRAGMENT_INDEXED_TILEMAP);

    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_src, NULL);
    glCompileShader(vertex_shader);

    int result = 0;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &result);
    if (!result) {
        int length;
        glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &length);
        char *buffer = malloc(length);
        glGetShaderInfoLog(vertex_shader, length, NULL, buffer);
        fprintf(stderr, "Vertex shader error:\n%s\n", buffer);
        free(buffer);
        glDeleteShader(vertex_shader);
        return -1;
    }

    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &frag_src, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &result);
    if (!result) {
        int length;
        glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &length);
        char *buffer = malloc(length);
        glGetShaderInfoLog(fragment_shader, length, NULL, buffer);
        fprintf(stderr, "Fragment shader error:\n%s\n", buffer);
        free(buffer);
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        return -1;
    }

    shader = glCreateProgram();
    glAttachShader(shader, vertex_shader);
    glAttachShader(shader, fragment_shader);
    glLinkProgram(shader);

    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if (!result) {
        int length;
        glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &length);
        char *buffer = malloc(length);
        glGetProgramInfoLog(shader, length, NULL, buffer);
        fprintf(stderr, "%s\n", buffer);
        free(buffer);
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        glDeleteProgram(shader);
        return -1;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
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
        data_get_tile(i, tile);
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
        palette_t palette;
        data_get_palette(i, &palette);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, i, 3, 1, GL_RGB,
                        GL_UNSIGNED_BYTE, &palette);
    }

    return glGetError();
}

void renderer_destroy()
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

void renderer_render(unsigned char tile, short x, short y,
                     unsigned char palette)
{
    if (render_list.count >= BATCH_SIZE) {
        renderer_present();
    }
    else {
        render_list.pos[render_list.count][0] = (float) x;
        render_list.pos[render_list.count][1] = (float) y;
        render_list.tile[render_list.count] = (float) tile;
        render_list.palette[render_list.count] = (float) palette;
        render_list.count++;
    }
}

void renderer_present()
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