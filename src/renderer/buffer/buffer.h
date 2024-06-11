#ifndef BUFFER_H
#define BUFFER_H

int buffer_init(unsigned int n);
void buffer_destroy();
void buffer_bind();
void buffer_add(float x, float y, float t, float p);
void buffer_send_to_shader();

#endif