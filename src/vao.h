#ifndef VAO_H
#define VAO_H

#include <stddef.h>
#include <glad/glad.h>
#include <debug.h>
#include <vbo.h>

typedef struct vao {
    GLuint id;
} vao_t;

vao_t vao_create();
void vao_destroy(vao_t* vao);
void vao_bind(const vao_t* vao);
void vao_attributes(const vao_t* vao, const vbo_t* vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset);

#endif