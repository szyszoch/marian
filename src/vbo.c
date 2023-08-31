#include <vbo.h>

vbo_t vbo_create(GLuint type, GLuint usage)
{
    vbo_t new_vbo;
    new_vbo.type = type;
    new_vbo.usage = usage;
    GL(glGenBuffers(1, &new_vbo.id));
    return new_vbo;
}

void vbo_destroy(vbo_t* vbo)
{
    GL(glDeleteBuffers(1, &vbo->id));
}

void vbo_bind(const vbo_t* vbo)
{
    GL(glBindBuffer(vbo->type, vbo->id));
}

void vbo_data(const vbo_t* vbo, void* data, unsigned int size)
{
    vbo_bind(vbo);
    GL(glBufferData(vbo->type, size, data, vbo->usage));
}