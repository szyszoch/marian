#include "tileset.h"
#include "tiles.h"

const struct tileset big_u = {
	.width = 2,
	.height = 3,
	.tiles =
		(unsigned char[]){
			TILE_BIG_U_1,
			TILE_BIG_U_2,
			TILE_BIG_U_3,
			TILE_BIG_U_4,
			TILE_BIG_U_5,
			TILE_BIG_U_6,
		},
	.flips =
		(unsigned char[]){
			FLIP_NONE,
			FLIP_NONE,
			FLIP_NONE,
			FLIP_NONE,
			FLIP_VERTICAL,
			FLIP_VERTICAL | FLIP_HORIZONTAL,
		},
};