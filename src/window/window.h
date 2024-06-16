#ifndef WINDOW_H
#define WINDOW_H

int window_init(const char *t, int w, int h);
void window_destroy();
void window_update();
int window_is_open();
int window_pressed_right_arrow();
int window_pressed_left_arrow();
int window_pressed_down_arrow();
int window_pressed_up_arrow();
int window_pressed_escape();

#endif