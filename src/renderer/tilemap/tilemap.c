#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include "renderer/tilemap/tiles.h"
#include "renderer/tilemap/palettes.h"

#define TEX_TIL 0x00
#define TEX_PAL 0x01

static unsigned int texture[2];

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
    texture[TEX_TIL] = init_texture(GL_R8, GL_UNSIGNED_BYTE, 8 * TILE_COUNT, 8,
                                 NULL);
    for (unsigned char i = 0; i < TILE_COUNT; i++) {
        struct tile_data td = decompress_tile_data(&tiles[i]);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 8 * i, 0, 8, 8, GL_RED,
                        GL_UNSIGNED_BYTE, &td);
    }
    texture[TEX_PAL] = init_texture(GL_RGB8, GL_UNSIGNED_BYTE, 3, 
                                    PALETTE_COUNT, NULL);
    for (unsigned char i = 0; i < PALETTE_COUNT; i++) {
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, i, 3, 1, GL_RGB,
                        GL_UNSIGNED_BYTE, &palettes[i]);
    }
    return glGetError();
}

void tilemap_destroy()
{
    glDeleteTextures(2, texture);
}

void tilemap_bind_tiles(int tex_slot)
{
    glActiveTexture(GL_TEXTURE0 + tex_slot);
    glBindTexture(GL_TEXTURE_2D, texture[TEX_TIL]);
}

void tilemap_bind_palettes(int tex_slot)
{
    glActiveTexture(GL_TEXTURE0 + tex_slot);
    glBindTexture(GL_TEXTURE_2D, texture[TEX_PAL]);
}