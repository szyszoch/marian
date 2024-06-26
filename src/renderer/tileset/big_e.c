#include "tileset.h"
#include "tiles.h"

const struct tileset big_e = {
	.width = 2,
	.height = 3,
	.tiles =
		(unsigned char[]){
			TILE_BIG_E_1,
			TILE_BIG_E_2,
			TILE_BIG_E_3,
			TILE_BIG_E_4,
			TILE_BIG_E_5,
			TILE_BIG_E_6,
		},
	.flips =
		(unsigned char[]){
			FLIP_NONE,
			FLIP_HORIZONTAL,
			FLIP_NONE,
			FLIP_NONE,
			FLIP_VERTICAL,
			FLIP_HORIZONTAL,
		},
};