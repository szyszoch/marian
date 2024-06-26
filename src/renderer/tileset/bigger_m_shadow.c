#include "tileset.h"
#include "tiles.h"

const struct tileset bigger_m_shadow = {
	.width = 3,
	.height = 5,
	.tiles =
		(unsigned char[]){
			TILE_BIGGER_M_SHADOW_1,
			TILE_BIGGER_M_SHADOW_2,
			TILE_BIGGER_M_SHADOW_3,
			TILE_BIGGER_M_SHADOW_4,
			TILE_BIGGER_M_SHADOW_5,
			TILE_BIGGER_M_SHADOW_6,
			TILE_BIGGER_M_SHADOW_7,
			TILE_BIGGER_M_SHADOW_8,
			TILE_BIGGER_M_SHADOW_9,
			TILE_BIGGER_M_SHADOW_10,
			TILE_BIGGER_M_SHADOW_11,
			TILE_BIGGER_M_SHADOW_12,
			TILE_BIGGER_M_SHADOW_13,
			TILE_BIGGER_M_SHADOW_14,
			TILE_BIGGER_M_SHADOW_15,
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