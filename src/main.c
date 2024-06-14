#include "renderer/renderer.h"
#include "window/window.h"

int main()
{
    window_init();
    renderer_init();
    renderer_set_background_color(0x94, 0x94, 0xff);

    while (window_is_open())
    {
        window_update();
        renderer_clear();
        renderer_1_player_hud();
        renderer_present();
    }
    
    renderer_destroy();
    window_destroy();

    return 0;
}