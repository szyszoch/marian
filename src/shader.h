#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <stdio.h>

typedef struct shader {
    GLuint id;
} shader_t;

shader_t shader_create(const char* vertex_shader_source, const char* fragment_shader_source);
void shader_destroy(shader_t shader);
void shader_bind(shader_t shader);
void shader_set_int(shader_t shader, const char* name, int value);
void shader_set_uint(shader_t shader, const char* name, unsigned int value);
void shader_set_float(shader_t shader, const char* name, float value);
void shader_set_vec2(shader_t shader, const char* name, float value1, float value2);
void shader_set_vec3(shader_t shader, const char* name, float value1, float value2, float value3);
void shader_set_vec4(shader_t shader, const char* name, float value1, float value2, float value3, float value4);

#endif