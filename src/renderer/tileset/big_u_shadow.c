#include "tileset.h"
#include "tiles.h"

const struct tileset big_u_shadow = {
	.width = 2,
	.height = 3,
	.tiles =
		(unsigned char[]){
			TILE_BIG_U_SHADOW_1,
			TILE_BIG_U_SHADOW_2,
			TILE_BIG_U_SHADOW_3,
			TILE_BIG_U_SHADOW_4,
			TILE_BIG_U_SHADOW_5,
			TILE_BIG_U_SHADOW_6,
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