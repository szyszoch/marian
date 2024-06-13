#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int init_shader(unsigned int t, const char *s)
{
    unsigned int sh = glCreateShader(t);
    glShaderSource(sh, 1, &s, NULL);
    glCompileShader(sh);
    int ll;
    glGetShaderiv(sh, GL_INFO_LOG_LENGTH, &ll);
    if (ll) {
        char *b = malloc(ll);
        glGetShaderInfoLog(sh, ll, NULL, b);
        fprintf(stderr, "Shader error:\n%s\n", b);
        free(b);
        glDeleteShader(sh);
        sh = 0;
    }
    return sh;
}

static unsigned int get_base_format(unsigned int f)
{
    switch(f) {
        case GL_R8: return GL_RED;
        case GL_RGB8: return GL_RGB;
        default: {
            fprintf(stderr, "Unknown texture format\n");
            return 0;
        }
    }
}

unsigned int gl_init_program(const char *vs, const char *fs)
{
    unsigned int v = init_shader(GL_VERTEX_SHADER, vs);
    unsigned int f = init_shader(GL_FRAGMENT_SHADER, fs);
    unsigned int p = glCreateProgram();
    glAttachShader(p, v);
    glAttachShader(p, f);
    glLinkProgram(p);
    glDeleteShader(v);
    glDeleteShader(f);
    int ll;
    glGetProgramiv(p, GL_INFO_LOG_LENGTH, &ll);
    if (ll) {
        char *b = malloc(ll);
        glGetProgramInfoLog(p, ll, NULL, b);
        fprintf(stderr, "program error:\n%s\n", b);
        free(b);
        glDeleteProgram(p);
        p = 0;
    }
    return p;
}

unsigned int gl_init_texture(unsigned int f, unsigned int t, int w, int h, 
                             const void *d)
{
    unsigned int tx;
    glGenTextures(1, &tx);
    glBindTexture(GL_TEXTURE_2D, tx);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    unsigned int bf = get_base_format(f);
    glTexImage2D(GL_TEXTURE_2D, 0, f, w, h, 0, bf, t, d);
    return tx;
} 
