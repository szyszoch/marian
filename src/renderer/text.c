#include "renderer/renderer.h"

static const unsigned char copyright[14] = {
    TILE_COPYRIGHT, TILE_1, TILE_9, TILE_8, TILE_5, TILE_NONE, TILE_N,
    TILE_I, TILE_N, TILE_T, TILE_E, TILE_N, TILE_D, TILE_O,
};

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
        default: return TILE_NONE;
    }
}

void render_text(const char *text, short x, short y)
{
    int i = 0;
    while (text[i]) {
        unsigned char tile = letter_to_tile(text[i]);
        render_tile(tile, x + 8 * i, y, PALETTE_CASTLE_GROUND_AND_STONE);
        i++;
    }
}

void render_copyright(short x, short y)
{
    render_set_of_tiles(copyright, x, y, 14, 1,
                        PALETTE_OVERWORLD_GROUND_AND_STONE);
}