#include "renderer/renderer.h"
#include "window/window.h"

int main()
{
    window_init();
    init_renderer();
    set_background_color(0x94, 0x94, 0xff);

    while (window_is_open())
    {
        window_update();
        clear_renderer();
        render_1_player_hud();
        present_renderer();
    }
    
    destroy_renderer();
    window_destroy();

    return 0;
}