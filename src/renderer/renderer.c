#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include "renderer/renderer.h"
#include "renderer/data/palettes.h"
#include "renderer/data/tiles.h"
#include "settings.h"

#define GAME_WIDTH 256
#define GAME_HEIGHT 240

#define BATCH_SIZE 256

#define VBO_QUAD    0x00
#define VBO_POS     0x01
#define VBO_TILE    0x02
#define VBO_PALETTE 0x03
#define VBO_COUNT   0x04

#define VBO_QUAD_SIZE       (sizeof(float) * 8)
#define VBO_POS_SIZE        (sizeof(float) * 2)
#define VBO_TILE_SIZE       (sizeof(float))
#define VBO_PALETTE_SIZE    (sizeof(float))

#define TEX_TILES       0x00
#define TEX_PALETTES    0x01
#define TEX_COUNT       0x02

extern const char *vertex_shader;
extern const char *fragment_shader;

extern unsigned char coins;
extern unsigned short time;
extern unsigned char level;
extern unsigned char world;
extern unsigned int score;

static const unsigned char digits_tiles[10] = {
    TILE_0, TILE_1, TILE_2, TILE_3, TILE_4,
    TILE_5, TILE_6, TILE_7, TILE_8, TILE_9,
};

static float background_color[3];

static struct {
    unsigned int vao;
    unsigned int vbo[4];
    struct {
        float *pos;
        float *tile;
        float *palette;
        unsigned int count;
        unsigned int max;
    } data;
} buffer;

static unsigned int program; 
static unsigned int texture[2];

static unsigned int get_texture_base_format(unsigned int f)
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

static unsigned int init_texture(unsigned int f, int w, int h, const void *d)
{
    unsigned int tx;
    glGenTextures(1, &tx);
    glBindTexture(GL_TEXTURE_2D, tx);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    unsigned int bf = get_texture_base_format(f);
    glTexImage2D(GL_TEXTURE_2D, 0, f, w, h, 0, bf, GL_UNSIGNED_BYTE, d);
    return tx;
} 

static void change_texture(int x, int y, int w, int h, unsigned int f,
    const void *d)
{
    glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, w, h, f, GL_UNSIGNED_BYTE, d);
}

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

static int init_buffers(unsigned int n)
{
    glGenVertexArrays(1, &buffer.vao);
    glBindVertexArray(buffer.vao);

    glGenBuffers(VBO_COUNT, buffer.vbo);

    const float quad[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
    };
    glBindBuffer(GL_ARRAY_BUFFER, buffer.vbo[VBO_QUAD]);
    glBufferData(GL_ARRAY_BUFFER, VBO_QUAD_SIZE, quad, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, 0, 0, NULL);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, buffer.vbo[VBO_POS]);
    glBufferData(GL_ARRAY_BUFFER, VBO_POS_SIZE * n, NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, 0, 0, NULL);
    glVertexAttribDivisor(1, 1);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, buffer.vbo[VBO_TILE]);
    glBufferData(GL_ARRAY_BUFFER, VBO_TILE_SIZE * n, NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(2, 1, GL_FLOAT, 0, 0, NULL);
    glVertexAttribDivisor(2, 1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, buffer.vbo[VBO_PALETTE]);
    glBufferData(GL_ARRAY_BUFFER, VBO_PALETTE_SIZE * n, NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(3, 1, GL_FLOAT, 0, 0, NULL);
    glVertexAttribDivisor(3, 1);
    glEnableVertexAttribArray(3);

    buffer.data.pos = malloc(VBO_POS_SIZE * n);
    buffer.data.tile = malloc(VBO_TILE_SIZE * n);
    buffer.data.palette = malloc(VBO_PALETTE_SIZE * n);
    buffer.data.count = 0;
    buffer.data.max = n;

    return glGetError();
}

static int init_uniforms()
{
    unsigned int tiles = glGetUniformLocation(program, "tiles");
    unsigned int palettes = glGetUniformLocation(program, "palettes");
    unsigned int tile_count = glGetUniformLocation(program, "tile_count");
    unsigned int palette_count = glGetUniformLocation(program, "palette_count");
    unsigned int pixel_size = glGetUniformLocation(program, "pixel_size");

    glUniform1i(tiles, 0);
    glUniform1i(palettes, 1);
    glUniform1f(tile_count, TILE_COUNT);
    glUniform1f(palette_count, PALETTE_COUNT);
    glUniform2f(pixel_size, 2.0f / GAME_WIDTH, 2.0f / GAME_HEIGHT);

    return glGetError();
}

static int init_tilemap()
{
    glActiveTexture(GL_TEXTURE0);
    texture[TEX_TILES] = init_texture(GL_R8, 8 * TILE_COUNT, 8, NULL);
    for (unsigned char i = 0; i < TILE_COUNT; i++) {
        struct tile_data td = get_tile_data(i);
        change_texture(8 * i, 0, 8, 8, GL_RED, &td);
    }

    glActiveTexture(GL_TEXTURE1);
    texture[TEX_PALETTES] = init_texture(GL_RGB8, 3, PALETTE_COUNT, NULL);
    for (unsigned char i = 0; i < PALETTE_COUNT; i++)
        change_texture(0, i, 3, 1, GL_RGB, &palettes[i]);

    return glGetError();
}

static void render_tile(unsigned char tile, short x, short y,
    unsigned char palette)
{
    if (buffer.data.count >= buffer.data.max) {
        renderer_present();
        return;
    } 
    buffer.data.pos[buffer.data.count * 2] = x;
    buffer.data.pos[buffer.data.count * 2 + 1] = y;
    buffer.data.tile[buffer.data.count] = tile;
    buffer.data.palette[buffer.data.count] = palette;
    buffer.data.count++;
}

static void render_number_zero_padding(unsigned int number,
    unsigned char size, short x, short y)
{
    while(size--) {
        render_tile(digits_tiles[number % 10], x + size * 8, y,
            PALETTE_CASTLE_GROUND_AND_STONE);
        number /= 10;
    } 
}

static void render_number(unsigned int number, short end_x, short y)
{
    do {
        render_tile(digits_tiles[number % 10], end_x, y,
                    PALETTE_CASTLE_GROUND_AND_STONE);
        end_x -= 8;
    } while (number /= 10);
}

static unsigned char letter_to_tile(char letter)
{
    switch(letter) {
        case 'A': return TILE_A;
        case 'B': return TILE_B;
        case 'C': return TILE_C;
        case 'D': return TILE_D;
        case 'E': return TILE_E;
        case 'F': return TILE_F;
        case 'G': return TILE_G;
        case 'H': return TILE_H;
        case 'I': return TILE_I;
        case 'J': return TILE_J;
        case 'K': return TILE_K;
        case 'L': return TILE_L;
        case 'M': return TILE_M;
        case 'N': return TILE_N;
        case 'O': return TILE_O;
        case 'P': return TILE_P;
        case 'Q': return TILE_Q;
        case 'R': return TILE_R;
        case 'S': return TILE_S;
        case 'T': return TILE_T;
        case 'U': return TILE_U;
        case 'V': return TILE_V;
        case 'W': return TILE_W;
        case 'X': return TILE_X;
        case 'Y': return TILE_Y;
        case 'Z': return TILE_Z;
        case '-': return TILE_MINUS;
        case 'x': return TILE_SMALL_X;
        case '!': return TILE_EXCLAMATION_MARK;
        case 'c': return TILE_COPYRIGHT;
        default: return TILE_NONE;
    }
}

static void render_text(const char *text, short x, short y)
{
    int i = 0;
    while (text[i]) {
        unsigned char tile = letter_to_tile(text[i]);
        render_tile(tile, x + 8 * i, y, PALETTE_CASTLE_GROUND_AND_STONE);
        i++;
    }
}

int renderer_init()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    program = init_program(vertex_shader, fragment_shader);

    if (!program) {
        fprintf(stderr, "Failed to initialize shader program\n");
        return -1;
    }

    glUseProgram(program);

    if (init_uniforms()) {
        fprintf(stderr, "Failed to initialize shader uniforms\n");
        return -1;  
    }

    if (init_tilemap()) {
        fprintf(stderr, "Failed to initialize tilemap\n");
        return -1;    
    }

    if (init_buffers(BATCH_SIZE)) {
        fprintf(stderr, "Failed to initialize renderer buffers\n");
        return -1;
    }
        
    renderer_set_background_color(0, 0, 0);
    return glGetError();
}

void renderer_destroy()
{
    glDeleteBuffers(VBO_COUNT, buffer.vbo);
    glDeleteVertexArrays(1, &buffer.vao);
    glDeleteTextures(TEX_COUNT, texture);
    glDeleteProgram(program);
}

void renderer_present()
{
    glBindBuffer(GL_ARRAY_BUFFER, buffer.vbo[VBO_POS]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, VBO_POS_SIZE * buffer.data.count,
        buffer.data.pos);

    glBindBuffer(GL_ARRAY_BUFFER, buffer.vbo[VBO_TILE]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, VBO_TILE_SIZE * buffer.data.count,
        buffer.data.tile);

    glBindBuffer(GL_ARRAY_BUFFER, buffer.vbo[VBO_PALETTE]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, VBO_PALETTE_SIZE * buffer.data.count,
        buffer.data.palette);

    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, buffer.data.count);
    buffer.data.count = 0;
}

void renderer_clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(background_color[0], background_color[1], background_color[2],
                 1.0f);
}

void renderer_set_background_color(unsigned char r, unsigned char g,
    unsigned char b)
{
    background_color[0] = (float) r / 0xff;
    background_color[1] = (float) g / 0xff;
    background_color[2] = (float) b / 0xff;
}

void renderer_1_player_hud()
{
    render_text("MARIO", 24, 16);
    render_number_zero_padding(score, 6, 24, 24);
    render_tile(TILE_COIN_ICON, 88, 24, PALETTE_OVERWORLD_COINS_1);
    render_tile(TILE_SMALL_X, 96, 24, PALETTE_CASTLE_GROUND_AND_STONE);
    render_number_zero_padding(coins, 2, 104, 24);
    render_text("WORLD", 144, 16);
    render_number_zero_padding(world, 1, 152, 24);
    render_tile(TILE_MINUS, 160, 24, PALETTE_CASTLE_GROUND_AND_STONE);
    render_number_zero_padding(level, 1, 168, 24);
    render_text("TIME", 200, 16);
    render_number(time, 224, 24);
}

void renderer_texture(unsigned char t, short x, short y)
{
    switch(t) {
        case TEXTURE_GROUND: {
            render_tile(TILE_GROUND_1, x, y, 
                PALETTE_OVERWORLD_GROUND_AND_STONE);
            render_tile(TILE_GROUND_2, x + 8, y, 
                PALETTE_OVERWORLD_GROUND_AND_STONE);
            render_tile(TILE_GROUND_3, x, y + 8, 
                PALETTE_OVERWORLD_GROUND_AND_STONE);
            render_tile(TILE_GROUND_4, x + 8, y + 8, 
                PALETTE_OVERWORLD_GROUND_AND_STONE);
            break;
        }
    }
}