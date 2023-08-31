#include <vao.h>

vao_t vao_create()
{
    vao_t vao;
    GL(glGenVertexArrays(1, &vao.id));
    return vao;
}

void vao_destroy(vao_t* vao)
{
    GL(glDeleteVertexArrays(1, &vao->id));
}

void vao_bind(const vao_t* vao)
{
    GL(glBindVertexArray(vao->id));
}

void vao_attributes(const vao_t* vao, const vbo_t* vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset)
{
    vao_bind(vao);
    vbo_bind(vbo);
    GL(glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void*) offset));
    GL(glEnableVertexAttribArray(index));
}