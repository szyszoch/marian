#ifndef RENDERER_H
#define RENDERER_H

#include <debug.h>
#include <glad/glad.h>
#include <cglm/cglm.h>
#include <vao.h>
#include <shader.h>
#include <texture.h>

typedef struct renderer {
    vao_t vao;
    shader_t shader;
} renderer_t;

void renderer_init();
void renderer_render(texture_t texture, vec2 position, vec2 size);

#endif