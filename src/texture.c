#include <texture.h>

texture_t texture_load_image(const sprite_t* sprite)
{
    texture_t new_texture;
    glGenTextures(1, &new_texture.id);
    glBindTexture(GL_TEXTURE_2D, new_texture.id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R3_G3_B2, sprite->width, sprite->height, 0, GL_RGB, GL_UNSIGNED_BYTE_3_3_2, sprite->pixels);
    return new_texture;
}

void texture_bind(texture_t texture)
{
    glBindTexture(GL_TEXTURE_2D, texture.id);
}