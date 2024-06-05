#include "renderer/renderer.h"

extern unsigned char coins;
extern unsigned short time;
extern unsigned char level;
extern unsigned char world;
extern unsigned int score;

void render_1_player_hud()
{
    renderer_render(TILE_M, 24, 16, PALETTE_CASTLE_GROUND_AND_STONE);
    renderer_render(TILE_A, 32, 16, PALETTE_CASTLE_GROUND_AND_STONE);
    renderer_render(TILE_R, 40, 16, PALETTE_CASTLE_GROUND_AND_STONE);
    renderer_render(TILE_I, 48, 16, PALETTE_CASTLE_GROUND_AND_STONE);
    renderer_render(TILE_O, 56, 16, PALETTE_CASTLE_GROUND_AND_STONE);
    renderer_render_number_with_zero_padding(score, 6, 24, 24);
    renderer_render(TILE_COIN_ICON, 88, 24, PALETTE_OVERWORLD_COINS_1);
    renderer_render(TILE_SMALL_X, 96, 24, PALETTE_CASTLE_GROUND_AND_STONE);
    renderer_render_number_with_zero_padding(coins, 2, 104, 24);
    renderer_render(TILE_W, 144, 16, PALETTE_CASTLE_GROUND_AND_STONE);
    renderer_render(TILE_O, 152, 16, PALETTE_CASTLE_GROUND_AND_STONE);
    renderer_render(TILE_R, 160, 16, PALETTE_CASTLE_GROUND_AND_STONE);
    renderer_render(TILE_L, 168, 16, PALETTE_CASTLE_GROUND_AND_STONE);
    renderer_render(TILE_D, 176, 16, PALETTE_CASTLE_GROUND_AND_STONE);
    renderer_render_number_with_zero_padding(world, 1, 152, 24);
    renderer_render(TILE_MINUS, 160, 24, PALETTE_CASTLE_GROUND_AND_STONE);
    renderer_render_number_with_zero_padding(level, 1, 168, 24);
    renderer_render(TILE_T, 200, 16, PALETTE_CASTLE_GROUND_AND_STONE);
    renderer_render(TILE_I, 208, 16, PALETTE_CASTLE_GROUND_AND_STONE);
    renderer_render(TILE_M, 216, 16, PALETTE_CASTLE_GROUND_AND_STONE);
    renderer_render(TILE_E, 224, 16, PALETTE_CASTLE_GROUND_AND_STONE);
    renderer_render_number(time, 224, 24);
}
