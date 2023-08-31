#ifndef SHADER_H
#define SHADER_H

#include <debug.h>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <stdio.h>
#include <cglm/cglm.h>

typedef struct shader {
    GLuint id;
} shader_t;

shader_t shader_create(const char* vertex_shader_source, const char* fragment_shader_source);
void shader_destroy(const shader_t* shader);
void shader_bind(const shader_t* shader);
void shader_set_mat4(const shader_t* shader, const char* name, mat4 value);

#endif