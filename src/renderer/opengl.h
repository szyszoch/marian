#ifndef OPENGL_H
#define OPENGL_H

unsigned int gl_init_program(const char *vs, const char *fs);
unsigned int gl_init_texture(unsigned int f, unsigned int t, int w, int h, 
                             const void *d);

#endif