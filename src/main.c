#include "renderer.h"
#include "window.h"
#include "state.h"

int main()
{
    window_init("Marian", 1024, 960);
    renderer_init();
    state_change(STATE_MENU);
    renderer_set_biome(BIOME_OVERWORLD);

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