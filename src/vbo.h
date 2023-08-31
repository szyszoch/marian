#ifndef VBO_H
#define VBO_H

#include <debug.h>
#include <glad/glad.h>

typedef struct vbo {
    GLuint id;
    GLuint type;
    GLuint usage;
} vbo_t;

vbo_t vbo_create(GLuint type, GLuint usage);
void vbo_destroy(vbo_t* vbo);
void vbo_bind(const vbo_t* vbo);
void vbo_data(const vbo_t* vbo, void* data, unsigned int size);

#endif