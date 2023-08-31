#ifndef DEBUG_H
#define DEBUG_H

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <stdio.h>

#define GL(x) x; check_gl_error(__FILE__, __LINE__)

void check_gl_error(const char* file, unsigned int line);

#endif