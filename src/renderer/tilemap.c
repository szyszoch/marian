#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include "renderer/tiles.h"
#include "renderer/palettes.h"

static unsigned int tex_tiles;
static unsigned int tex_palettes;

static unsigned int get_base_format(unsigned int f)
{
    switch(f) {
        case GL_R8: return GL_RED;
        case GL_RGB8: return GL_RGB;
        default: {
            printf("Unknown texture format\n");
            return 0;
        }
    }
}

static unsigned int init_texture(unsigned int f, unsigned int t, int w, int h, 
                                 const void *data)
{
    unsigned int tx;
    glGenTextures(1, &tx);
    glBindTexture(GL_TEXTURE_2D, tx);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    unsigned int bf = get_base_format(f);
    glTexImage2D(GL_TEXTURE_2D, 0, f, w, h, 0, bf, t, data);
    return tx;
} 

int tilemap_init()
{
    tex_tiles = init_texture(GL_R8, GL_UNSIGNED_BYTE, 8 * TILE_COUNT, 8, NULL);
    for (unsigned char i = 0; i < TILE_COUNT; i++) {
        struct tile_data td = decompress_tile_data(&tiles[i]);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 8 * i, 0, 8, 8, GL_RED,
                        GL_UNSIGNED_BYTE, &td);
    }
    tex_palettes = init_texture(GL_RGB8, GL_UNSIGNED_BYTE, 3, PALETTE_COUNT, 
                                NULL);
    for (unsigned char i = 0; i < PALETTE_COUNT; i++) {
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, i, 3, 1, GL_RGB,
                        GL_UNSIGNED_BYTE, &palettes[i]);
    }
    return glGetError();
}

void tilemap_destroy()
{
    glDeleteTextures(1, &tex_tiles);
    glDeleteTextures(1, &tex_palettes);
}

void tilemap_bind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex_tiles);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex_palettes);
}