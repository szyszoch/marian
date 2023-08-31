#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <sprite.h>

typedef struct texture {
    GLuint id;
} texture_t;

texture_t texture_load_image(const sprite_t* sprite);
void texture_bind(texture_t texture);

#endif