#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <stdio.h>

typedef struct shader {
    GLuint id;
} shader_t;

shader_t shader_create(const char* vertex_shader_source, const char* fragment_shader_source);
void shader_bind(shader_t shader);

#endif