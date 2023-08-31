#include <debug.h>

void check_gl_error(const char* file, unsigned int line) 
{
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "OpenGL error in file %s at line %d. Error code: %d\n", file, line, error);
    }
}