#include "tileset.h"
#include "tiles.h"

const struct tileset bigger_a = {
	.width = 2,
	.height = 5,
	.tiles =
		(unsigned char[]){
			TILE_BIGGER_A_1,
			TILE_BIGGER_A_2,
			TILE_BIGGER_A_3,
			TILE_BIGGER_A_4,
			TILE_BIGGER_A_5,
			TILE_BIGGER_A_6,
			TILE_BIGGER_A_7,
			TILE_BIGGER_A_8,
			TILE_BIGGER_A_9,
			TILE_BIGGER_A_10,
		},
	.flips =
		(unsigned char[]){
			FLIP_NONE,
			FLIP_HORIZONTAL,
			FLIP_NONE,
			FLIP_NONE,
			FLIP_NONE,
			FLIP_NONE,
			FLIP_NONE,
			FLIP_HORIZONTAL,
			FLIP_NONE,
			FLIP_NONE,
		},
};