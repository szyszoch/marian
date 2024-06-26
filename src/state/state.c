#include "state.h"
#include "window.h"

static unsigned char current_state;

static void (*render_func)();
static void (*update_func)();

extern void state_menu_render();
extern void state_menu_update();

void state_render()
{
	render_func();
}

void state_update()
{
	update_func();
}

void state_change(unsigned char s)
{
	current_state = s;
	switch (s) {
	case STATE_QUIT:
		window_close();
		break;
	case STATE_MENU:
		render_func = state_menu_render;
		update_func = state_menu_update;
		break;
	}
}