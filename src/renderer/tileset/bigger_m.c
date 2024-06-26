#include "tileset.h"
#include "tiles.h"

const struct tileset bigger_m = {
	.width = 3,
	.height = 5,
	.tiles =
		(unsigned char[]){
			TILE_BIGGER_M_1,
			TILE_BIGGER_M_2,
			TILE_BIGGER_M_3,
			TILE_BIGGER_M_4,
			TILE_BIGGER_M_5,
			TILE_BIGGER_M_6,
			TILE_BIGGER_M_7,
			TILE_BIGGER_M_8,
			TILE_BIGGER_M_9,
			TILE_BIGGER_M_10,
			TILE_BIGGER_M_11,
			TILE_BIGGER_M_12,
			TILE_BIGGER_M_13,
			TILE_BIGGER_M_14,
			TILE_BIGGER_M_15,
		},
	.flips =
		(unsigned char[]){
			FLIP_NONE,
			FLIP_NONE,
			FLIP_HORIZONTAL,
			FLIP_NONE,
			FLIP_NONE,
			FLIP_NONE,
			FLIP_NONE,
			FLIP_NONE,
			FLIP_NONE,
			FLIP_NONE,
			FLIP_NONE,
			FLIP_NONE,
			FLIP_NONE,
			FLIP_NONE,
			FLIP_NONE,
		},
};