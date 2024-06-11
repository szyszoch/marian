#include <stdlib.h>
#include <glad/glad.h>
#include "renderer/buffer/buffer.h"
#include <stdio.h>

#define BUF_QUA 0x00
#define BUF_POS 0x01
#define BUF_TIL 0x02
#define BUF_PAL 0x03
#define BUF_COU 0x04

#define BUF_QUA_S (sizeof(float) * 8)
#define BUF_POS_S (sizeof(float) * 2)
#define BUF_TIL_S (sizeof(float))
#define BUF_PAL_S (sizeof(float))

static struct {
    float *pos;
    float *tile;
    float *palette;
    unsigned int count;
} buffer_list;

static unsigned int vao;
static unsigned int buffer[4];
static unsigned int max;

int buffer_init(unsigned int n)
{
    max = n;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(BUF_COU, buffer);

    const float quad[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
    };
    glBindBuffer(GL_ARRAY_BUFFER, buffer[BUF_QUA]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, 0, 0, NULL);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, buffer[BUF_POS]);
    glBufferData(GL_ARRAY_BUFFER, BUF_POS_S * n, NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, 0, 0, NULL);
    glVertexAttribDivisor(1, 1);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, buffer[BUF_TIL]);
    glBufferData(GL_ARRAY_BUFFER, BUF_TIL_S * n, NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(2, 1, GL_FLOAT, 0, 0, NULL);
    glVertexAttribDivisor(2, 1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, buffer[BUF_PAL]);
    glBufferData(GL_ARRAY_BUFFER, BUF_PAL_S * n, NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(3, 1, GL_FLOAT, 0, 0, NULL);
    glVertexAttribDivisor(3, 1);
    glEnableVertexAttribArray(3);

    buffer_list.count = 0;
    buffer_list.pos = malloc(BUF_POS_S * n);
    buffer_list.tile = malloc(BUF_TIL_S * n);
    buffer_list.palette = malloc(BUF_PAL_S * n);

    return glGetError();
}

void buffer_destroy()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(BUF_COU, buffer);
    free(buffer_list.palette);
    free(buffer_list.tile);
    free(buffer_list.pos);
}

void buffer_bind()
{
    glBindVertexArray(vao);
}

void buffer_add(float x, float y, float t, float p)
{
    if (buffer_list.count >= max) {
        buffer_send_to_shader();
        return;
    } 
    buffer_list.pos[buffer_list.count * 2] = x;
    buffer_list.pos[buffer_list.count * 2 + 1] = y;
    buffer_list.tile[buffer_list.count] = t;
    buffer_list.palette[buffer_list.count] = p;
    buffer_list.count++;
}

void buffer_send_to_shader()
{
    glBindBuffer(GL_ARRAY_BUFFER, buffer[BUF_POS]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, BUF_POS_S * buffer_list.count,
                    buffer_list.pos);

    glBindBuffer(GL_ARRAY_BUFFER, buffer[BUF_TIL]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, BUF_TIL_S * buffer_list.count,
                    buffer_list.tile);

    glBindBuffer(GL_ARRAY_BUFFER, buffer[BUF_PAL]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, BUF_PAL_S * buffer_list.count,
                    buffer_list.palette);

    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, buffer_list.count);
    buffer_list.count = 0;
}