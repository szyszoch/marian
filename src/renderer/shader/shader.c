#include <glad/glad.h>
#include <stdlib.h>
#include <stdio.h>

extern const char *vertex_shader;
extern const char *fragment_shader;

static unsigned int program;

static struct {
    unsigned int pixel_size;
    unsigned int tiles;
    unsigned int tile_count;
    unsigned int palettes;
    unsigned int palette_count;
} uniform;

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

static unsigned int init_program(const char *vs, const char *fs)
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

int shader_init()
{
    program = init_program(vertex_shader, fragment_shader);
    if (!program)
        return -1;
    uniform.tiles = glGetUniformLocation(program, "tiles");
    uniform.palettes = glGetUniformLocation(program, "palettes");
    uniform.tile_count = glGetUniformLocation(program, "tile_count");
    uniform.palette_count = glGetUniformLocation(program, "palette_count");
    uniform.pixel_size = glGetUniformLocation(program, "pixel_size");
    return 0;
}

void shader_destroy()
{
    glDeleteProgram(program);
}

void shader_bind()
{
    glUseProgram(program);
}

void shader_set_tile_count(int tc)
{
    glUniform1f(uniform.tile_count, (float) tc);
}

void shader_set_palette_count(int pc)
{
    glUniform1f(uniform.palette_count, (float) pc);
}

void shader_set_tiles_texture(int tt)
{
    glUniform1i(uniform.tiles, tt);
}

void shader_set_palettes_texture(int pt)
{
    glUniform1i(uniform.palettes, pt);
}

void shader_set_game_dims(float gw, float gh)
{
    glUniform2f(uniform.pixel_size, 2.0f / gw, 2.0f / gh);
}