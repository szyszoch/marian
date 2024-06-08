#ifndef SHADER_H
#define SHADER_H

extern const char *fragment_shader;
extern const char *vertex_shader;

unsigned int init_program(const char *vs, const char *fs);

#endif