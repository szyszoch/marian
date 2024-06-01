#include <stddef.h>
#include "data.h"

static const char *shaders[] = {
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
    "}\n",

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
    "}\n",
};

const char *data_get_shader(unsigned char shader)
{
    if (shader >= SHADER_COUNT)
        return NULL;
    return shaders[shader];
}