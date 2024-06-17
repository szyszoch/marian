#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include "renderer/renderer.h"
#include "renderer/data/palettes.h"
#include "renderer/data/palette_set.h"
#include "renderer/data/tiles.h"

#define GAME_WIDTH 256
#define GAME_HEIGHT 240
#define BATCH_SIZE 256

#define FLIP_NONE       0x00
#define FLIP_RIGHT      0x01
#define FLIP_HORIZONTAL 0x02
#define FLIP_VERTICAL   0x04

struct vec2 {
    float x;
    float y;
};

extern const char *vertex_shader;
extern const char *fragment_shader;

extern unsigned char coins;
extern unsigned short time;
extern unsigned char level;
extern unsigned char world;
extern unsigned int score;

static unsigned int program; 

static unsigned int tiles_atlas;
static unsigned int palettes_atlas;

static unsigned int u_tiles;
static unsigned int u_palettes;
static unsigned int u_tile_count;
static unsigned int u_palette_count;
static unsigned int u_pixel_size;

static unsigned int vao;
static unsigned int b_quad;
static unsigned int b_pos;
static unsigned int b_tile;
static unsigned int b_palette;
static unsigned int b_flip;

static struct vec2 bd_pos[BATCH_SIZE];
static unsigned int bd_tile[BATCH_SIZE];
static unsigned int bd_palette[BATCH_SIZE];
static unsigned int bd_flip[BATCH_SIZE];
static unsigned int bd_count;

static unsigned char biome;

static float bg_color[3];

static void set_default_2d_texture_parameters()
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

static int init_tiles_atlas()
{
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &tiles_atlas);
    glBindTexture(GL_TEXTURE_2D, tiles_atlas);
    set_default_2d_texture_parameters();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, TILE_COUNT * 8, 8, 0, GL_RED,    
        GL_UNSIGNED_BYTE, NULL);
    for (unsigned char i = 0; i < TILE_COUNT; i++) {
        struct tile_data td = get_tile_data(i);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 8 * i, 0, 8, 8, GL_RED, 
            GL_UNSIGNED_BYTE, &td);
    }
    return glGetError();
}

static int init_palettes_atlas()
{
    glActiveTexture(GL_TEXTURE1);
    glGenTextures(1, &tiles_atlas);
    glBindTexture(GL_TEXTURE_2D, tiles_atlas);
    set_default_2d_texture_parameters();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 3, PALETTE_COUNT, 0, GL_RGB, 
        GL_UNSIGNED_BYTE, NULL);
    for (unsigned char i = 0; i < PALETTE_COUNT; i++)
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, i, 3, 1, GL_RGB, GL_UNSIGNED_BYTE, 
            &palettes[i]);
    return glGetError();
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

static int init_uniforms()
{
    u_tiles = glGetUniformLocation(program, "tiles");
    u_palettes = glGetUniformLocation(program, "palettes");
    u_tile_count = glGetUniformLocation(program, "tile_count");
    u_palette_count = glGetUniformLocation(program, "palette_count");
    u_pixel_size = glGetUniformLocation(program, "pixel_size");

    glUniform1i(u_tiles, 0);
    glUniform1i(u_palettes, 1);
    glUniform1f(u_tile_count, TILE_COUNT);
    glUniform1f(u_palette_count, PALETTE_COUNT);
    glUniform2f(u_pixel_size, 2.0f / GAME_WIDTH, 2.0f / GAME_HEIGHT);

    return glGetError();
}

static int init_buffers()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &b_quad);
    const float quad[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
    };
    glBindBuffer(GL_ARRAY_BUFFER, b_quad);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, 0, 0, NULL);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &b_pos);
    glBindBuffer(GL_ARRAY_BUFFER, b_pos);
    glBufferData(GL_ARRAY_BUFFER, sizeof(struct vec2) * BATCH_SIZE, NULL,
        GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, 0, 0, NULL);
    glVertexAttribDivisor(1, 1);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &b_tile);
    glBindBuffer(GL_ARRAY_BUFFER, b_tile);
    glBufferData(GL_ARRAY_BUFFER, sizeof(int) * BATCH_SIZE, NULL,
        GL_DYNAMIC_DRAW);
    glVertexAttribIPointer(2, 1, GL_INT, 0, NULL);
    glVertexAttribDivisor(2, 1);
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &b_palette);
    glBindBuffer(GL_ARRAY_BUFFER, b_palette);
    glBufferData(GL_ARRAY_BUFFER, sizeof(int) * BATCH_SIZE, NULL,
        GL_DYNAMIC_DRAW);
    glVertexAttribIPointer(3, 1, GL_INT, 0, NULL);
    glVertexAttribDivisor(3, 1);
    glEnableVertexAttribArray(3);

    glGenBuffers(1, &b_flip);
    glBindBuffer(GL_ARRAY_BUFFER, b_flip);
    glBufferData(GL_ARRAY_BUFFER, sizeof(int) * BATCH_SIZE, NULL,
        GL_DYNAMIC_DRAW);
    glVertexAttribIPointer(4, 1, GL_INT, 0, NULL);
    glVertexAttribDivisor(4, 1);
    glEnableVertexAttribArray(4);

    return glGetError();
}

static void render(unsigned char t, unsigned char ps, short x, short y,
    unsigned char f)
{
    if (bd_count >= BATCH_SIZE) {
        fprintf(stderr, "The limit of instances has been exceeded\n");
        return;
    } 
    bd_pos[bd_count].x = x;
    bd_pos[bd_count].y = y;
    bd_tile[bd_count] = t;
    bd_palette[bd_count] = palette_sets[ps][biome];
    bd_flip[bd_count] = f;
    bd_count++;
}

static unsigned char convert_digit_to_tile(unsigned int d)
{
    const unsigned char dt[10] = {
        TILE_0, TILE_1, TILE_2, TILE_3, TILE_4,
        TILE_5, TILE_6, TILE_7, TILE_8, TILE_9,
    };
    return dt[d % 10];
}

static void render_number_zero_padding(unsigned int number,
    unsigned char size, short x, short y)
{
    while(size--) {
        unsigned char d = convert_digit_to_tile(number);
        render(d, PALETTE_SET_TEXT, x + size * 8, y, 0);
        number /= 10;
    };
}

static void render_number(unsigned int number, short end_x, short y)
{
    while (number) {
        end_x -= 8;
        unsigned char d = convert_digit_to_tile(number);
        render(d, PALETTE_SET_TEXT, end_x, y, 0);
        number /= 10;
    };
}

static unsigned char convert_letter_to_tile(char letter)
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
        unsigned char tile = convert_letter_to_tile(text[i]);
        render(tile, PALETTE_SET_TEXT, x + 8 * i, y, 0);
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

    if (init_tiles_atlas()) {
        fprintf(stderr, "Failed to initialize tiles atlas\n");
        return -1;
    }

    if (init_palettes_atlas()) {
        fprintf(stderr, "Failed to initialize palettes atlas\n");
        return -1;
    }

    if (init_buffers()) {
        fprintf(stderr, "Failed to initialize buffers\n");
        return -1;
    }

    renderer_set_biome(BIOME_OVERWORLD);
    renderer_set_background_color(0, 0, 0);
    return glGetError();
}

void renderer_destroy()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &b_quad);
    glDeleteBuffers(1, &b_pos);
    glDeleteBuffers(1, &b_tile);
    glDeleteBuffers(1, &b_palette);
    glDeleteBuffers(1, &b_flip);
    glDeleteTextures(1, &tiles_atlas);
    glDeleteTextures(1, &palettes_atlas);
    glDeleteProgram(program);
}

void renderer_present()
{
    glBindBuffer(GL_ARRAY_BUFFER, b_pos);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(struct vec2) * bd_count, bd_pos);

    glBindBuffer(GL_ARRAY_BUFFER, b_tile);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(int) * bd_count, bd_tile);

    glBindBuffer(GL_ARRAY_BUFFER, b_palette);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(int) * bd_count, bd_palette);

    glBindBuffer(GL_ARRAY_BUFFER, b_flip);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(int) * bd_count, bd_flip);

    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, bd_count);
    bd_count = 0;
}

void renderer_clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(bg_color[0], bg_color[1], bg_color[2], 1.0f);
}

void renderer_set_biome(unsigned char b)
{
    biome = b;
}

void renderer_set_background_color(unsigned char r, unsigned char g,
    unsigned char b)
{
    bg_color[0] = (float) r / 0xff;
    bg_color[1] = (float) g / 0xff;
    bg_color[2] = (float) b / 0xff;
}

void renderer_texture(unsigned char t, short x, short y)
{
    switch(t) {
        case TEXTURE_GROUND: {
            render(TILE_K, PALETTE_SET_GROUND_AND_STONE, x, y, 0);
            render(TILE_GROUND_2, PALETTE_SET_GROUND_AND_STONE, x + 8, y, 0);
            render(TILE_GROUND_3, PALETTE_SET_GROUND_AND_STONE, x, y + 8, 0);
            render(TILE_GROUND_4, PALETTE_SET_GROUND_AND_STONE, x + 8, y + 8,  
                0);
            break;
        }
    }
}

void renderer_1_player_hud()
{
    render_text("MARIO", 24, 16);
    render_number_zero_padding(score, 6, 24, 24);
    render(TILE_COIN_ICON, PALETTE_SET_COINS_1, 88, 24, 0);
    render(TILE_SMALL_X, PALETTE_SET_TEXT, 96, 24, 0);
    render_number_zero_padding(coins, 2, 104, 24);
    render_text("WORLD", 144, 16);
    render_number_zero_padding(world, 1, 152, 24);
    render(TILE_MINUS, PALETTE_SET_TEXT, 160, 24, 0);
    render_number_zero_padding(level, 1, 168, 24);
    render_text("TIME", 200, 16);
    render_number(time, 232, 24);
}