#ifndef STATE_H
#define STATE_H

#define STATE_QUIT 0x00
#define STATE_MENU 0x01

void state_render();
void state_update();
void state_change(unsigned char s);

#endif