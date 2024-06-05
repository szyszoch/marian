#include "renderer/renderer.h"

extern unsigned char coins;
extern unsigned short time;
extern unsigned char level;
extern unsigned char world;
extern unsigned int score;

void render_1_player_hud()
{
    render_text("MARIO", 24, 16);
    render_number_with_zero_padding(score, 6, 24, 24);
    render_tile(TILE_COIN_ICON, 88, 24, PALETTE_OVERWORLD_COINS_1);
    render_tile(TILE_SMALL_X, 96, 24, PALETTE_CASTLE_GROUND_AND_STONE);
    render_number_with_zero_padding(coins, 2, 104, 24);
    render_text("WORLD", 144, 16);
    render_number_with_zero_padding(world, 1, 152, 24);
    render_tile(TILE_MINUS, 160, 24, PALETTE_CASTLE_GROUND_AND_STONE);
    render_number_with_zero_padding(level, 1, 168, 24);
    render_text("TIME", 200, 16);
    render_number(time, 224, 24);
}
