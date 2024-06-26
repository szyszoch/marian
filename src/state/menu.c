#include "state.h"
#include "renderer.h"

void state_menu_render()
{
	renderer_1_player_hud();
	renderer_texture(TEXTURE_LOGO, 40, 32);
}

void state_menu_update()
{
}