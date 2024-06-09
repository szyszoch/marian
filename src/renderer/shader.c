#include <glad/glad.h>
#include <stdlib.h>
#include <stdio.h>

const char *vertex_shader =
    "#version 330 core\n"
    "layout (location = 0) in vec2 quad;\n"
    "layout (location = 1) in vec2 pos;\n"
    "layout (location = 2) in float tile;\n"
    "layout (location = 3) in float palette;\n"
    "uniform vec2 pixel_size;\n"
    "uniform float tile_count;\n"
    "out vec2 ui;\n"
    "out float fpalette;\n"
    "void main()\n"
    "{\n"
        "fpalette = palette;\n"
        "vec2 texture_offset = vec2(tile / tile_count, 0.0);\n"
        "vec2 texture_scale = vec2(1.0 / tile_count, 1.0);\n"
        "ui = quad * texture_scale + texture_offset;\n"
        "vec2 clip_offset = pos * pixel_size - 1;\n"
        "float tile_width = 8.0;\n"
        "vec2 position = quad * tile_width * pixel_size + clip_offset;\n"
        "position.y *= -1.0;\n"
        "gl_Position = vec4(position, 0.0, 1.0);\n"
    "}\n";

const char *fragment_shader =
    "#version 330 core\n"
    "uniform sampler2D tiles;\n"
    "uniform sampler2D palettes;\n"
    "uniform float palette_count;\n"
    "in vec2 ui;\n"
    "in float fpalette;\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
        "float index = texture(tiles, ui).r * 255.0;\n"
        "if (index == 0.0) color = vec4(0.0, 0.0, 0.0, 0.0);\n"
        "else {\n"
            "vec2 vpalette = vec2(index / 3.0, fpalette/(palette_count - 1));\n"
            "color = texture(palettes, vpalette);\n"
        "}\n"
    "}\n";

static unsigned int program;

static struct {
    unsigned int pixel_size;
    unsigned int tiles;
    unsigned int tile_count;
    unsigned int palettes;
    unsigned int palette_count;
} uniforms;

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
    uniforms.tiles = glGetUniformLocation(program, "tiles");
    uniforms.palettes = glGetUniformLocation(program, "palettes");
    uniforms.tile_count = glGetUniformLocation(program, "tile_count");
    uniforms.palette_count = glGetUniformLocation(program, "palette_count");
    uniforms.pixel_size = glGetUniformLocation(program, "pixel_size");
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
    glUniform1f(uniforms.tile_count, (float) tc);
}

void shader_set_palette_count(int pc)
{
    glUniform1f(uniforms.palette_count, (float) pc);
}

void shader_set_tiles(int t)
{
    glUniform1i(uniforms.tiles, t);
}

void shader_set_palettes(int p)
{
    glUniform1i(uniforms.palettes, p);
}

void shader_set_pixel_size(float w, float h)
{
    glUniform2f(uniforms.pixel_size, w, h);
}