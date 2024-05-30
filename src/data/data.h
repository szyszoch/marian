#ifndef DATA_H
#define DATA_H

#define TILE_NONE           0x00
#define TILE_FIRST_COLOR    0x01
#define TILE_SECOND_COLOR   0x02
#define TILE_THIRD_COLOR    0x03

#define TILE_GROUND_1       0x04
#define TILE_GROUND_2       0x05
#define TILE_GROUND_3       0x06
#define TILE_GROUND_4       0x07

#define TILE_COUNT          0x08

void data_get_tile(unsigned char tile, unsigned char output[64]);

#endif