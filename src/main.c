#include "renderer/renderer.h"
#include "window/window.h"
#include "state/state.h"

int main()
{
    window_init("Marian", 1024, 960);
    renderer_init();
    renderer_set_background_color(0x94, 0x94, 0xff);
    state_change(STATE_MENU);

    while (window_is_open())
    {
        window_update();
        state_update();
        state_render();
        renderer_clear();
        renderer_present();
    }
    
    renderer_destroy();
    window_destroy();

    return 0;
}