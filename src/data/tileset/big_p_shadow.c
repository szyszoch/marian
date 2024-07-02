#include "tileset.h"
#include "tiles.h"

const struct tileset big_p_shadow = {
	.width = 2,
	.height = 3,
	.tiles =
		(unsigned char[]){
			TILE_BIG_P_SHADOW_1,
			TILE_BIG_P_SHADOW_2,
			TILE_BIG_P_SHADOW_3,
			TILE_BIG_P_SHADOW_4,
			TILE_BIG_P_SHADOW_5,
			TILE_BIG_P_SHADOW_6,
		},
	.flips =
		(unsigned char[]){
			FLIP_NONE,
			FLIP_HORIZONTAL,
			FLIP_NONE,
			FLIP_VERTICAL | FLIP_HORIZONTAL,
			FLIP_NONE,
			FLIP_NONE,
		},
};