#include <stdio.h>
#include "tiles.h"

/**
 * Every tile in the program is an 8x8 texture with only 4 colours.
 * They are also indexed textures, which means they store only indexes to
 * colours instead of the actual colours. This allows me to store them in
 * just 2 bits. Since every tile is built of 64 pixels, I need just four
 * unsigned ints to store one tile.
 */

struct compressed_tile_data {
	unsigned int four_bytes[4];
};

const struct compressed_tile_data tiles[] = {
	{{0x00000000, 0x00000000, 0x00000000, 0x00000000}},
	{{0x55555555, 0x55555555, 0x55555555, 0x55555555}},
	{{0xaaaaaaaa, 0xaaaaaaaa, 0xaaaaaaaa, 0xaaaaaaaa}},
	{{0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}},
	{{0x95556aaa, 0x6aaa6aaa, 0x6aaa6aaa, 0x6aaa6aaa}},
	{{0x7956b6ab, 0xb6abb6ab, 0xb7abbbfe, 0xb55fb6ab}},
	{{0x6aaa6aaa, 0xfaaa5faa, 0x65ff6a57, 0x6aabbffe}},
	{{0xb6abb6ab, 0xdaabdaab, 0x6aab6aab, 0x6aaf7ffe}},
	{{0x05401050, 0x50145014, 0x50141410, 0x05400000}},
	{{0x01400540, 0x01400140, 0x01400140, 0x15540000}},
	{{0x15505014, 0x00540550, 0x15405400, 0x55540000}},
	{{0x15540050, 0x01400550, 0x00145014, 0x15500000}},
	{{0x01500550, 0x14505050, 0x55540050, 0x00500000}},
	{{0x55505000, 0x55500014, 0x00145014, 0x15500000}},
	{{0x05501400, 0x50005550, 0x50145014, 0x15400000}},
	{{0x55545014, 0x00500140, 0x05000500, 0x05000000}},
	{{0x15505014, 0x50141550, 0x50145014, 0x15500000}},
	{{0x15505014, 0x50141554, 0x00140050, 0x15400000}},
	{{0x05401450, 0x50145014, 0x55545014, 0x50140000}},
	{{0x55505014, 0x50145550, 0x50145014, 0x55500000}},
	{{0x05501414, 0x50005000, 0x50001414, 0x05500000}},
	{{0x55405050, 0x50145014, 0x50145050, 0x55400000}},
	{{0x55545000, 0x50005550, 0x50005000, 0x55540000}},
	{{0x55545000, 0x50005550, 0x50005000, 0x50000000}},
	{{0x05541400, 0x50005054, 0x50141414, 0x05540000}},
	{{0x50145014, 0x50145554, 0x50145014, 0x50140000}},
	{{0x15540140, 0x01400140, 0x01400140, 0x15540000}},
	{{0x01540014, 0x00140014, 0x50145014, 0x15500000}},
	{{0x50145050, 0x51405500, 0x55405150, 0x50540000}},
	{{0x14001400, 0x14001400, 0x14001400, 0x15540000}},
	{{0x50145454, 0x55545554, 0x51145014, 0x50140000}},
	{{0x50145414, 0x55145554, 0x51545054, 0x50140000}},
	{{0x15505014, 0x50145014, 0x50145014, 0x15500000}},
	{{0x55505014, 0x50145014, 0x55505000, 0x50000000}},
	{{0x15505014, 0x50145014, 0x51545050, 0x15440000}},
	{{0x55505014, 0x50145054, 0x55405150, 0x50540000}},
	{{0x15405050, 0x50001550, 0x00145014, 0x15500000}},
	{{0x15540140, 0x01400140, 0x01400140, 0x01400000}},
	{{0x50145014, 0x50145014, 0x50145014, 0x15500000}},
	{{0x50145014, 0x50145454, 0x15500540, 0x01000000}},
	{{0x50145014, 0x51145554, 0x55545454, 0x50140000}},
	{{0x50145454, 0x15500540, 0x15505454, 0x50140000}},
	{{0x14141414, 0x14140550, 0x01400140, 0x01400000}},
	{{0x55540054, 0x01500540, 0x15005400, 0x55540000}},
	{{0x00000000, 0x00001554, 0x15540000, 0x00000000}},
	{{0x00000000, 0x10100440, 0x01000440, 0x10100000}},
	{{0x01400550, 0x05500550, 0x01400140, 0x00000140}},
	{{0x00000000, 0x00000000, 0x00000000, 0x01400140}},
	{{0x05501004, 0x41414401, 0x44014141, 0x10040550}},
	{{0x05c01570, 0x15701570, 0x15701570, 0x35e00f80}},
	{{0x15556aaa, 0x6aaa696a, 0x697a6afa, 0x6aaa6aaa}},
	{{0x5555aaaa, 0xaaaaaaaa, 0xaaaaaaaa, 0xaaaaaaaa}},
	{{0x5554aaab, 0xaaaba96b, 0xa97baafb, 0xaaabaaab}},
	{{0xaaaaaaaa, 0xaaaaaaaa, 0xaaaaaaaa, 0xaaaaffff}},
	{{0xaaabaaab, 0xaaaba96b, 0xa97baafb, 0xaaabfffc}},
	{{0x00550155, 0x01550555, 0x05551555, 0x15551555}},
	{{0x15551555, 0x05550555, 0x01550015, 0x00010000}},
	{{0x00004000, 0x54005540, 0x55505550, 0x55541554}},
	{{0x00ff03ff, 0x03ff0fff, 0x0fff3fff, 0x3fff3fff}},
	{{0x3fff3fff, 0x0fff0fff, 0x03ff003f, 0x00030000}},
	{{0x00003000, 0xf300ff30, 0xfff0fff0, 0xfffc3ffc}},
	{{0x15541554, 0x15541554, 0x15541554, 0x15541554}},
	{{0x3ffc3ffc, 0x3ffc3ffc, 0x3ffc3ffc, 0x3ffc3ffc}},
	{{0x15551555, 0x15551555, 0x15551555, 0x15551555}},
	{{0x3fff3fff, 0x3fff3fff, 0x3fff3fff, 0x3fff3fff}},
	{{0x00005550, 0x55505550, 0x55505550, 0x55500000}},
	{{0x0000fff0, 0xfff0fff0, 0xfff0fff0, 0xfff00000}},
	{{0x55545554, 0x55545550, 0x55405550, 0x55545554}},
	{{0xfffcfffc, 0xfffcfff0, 0xffc0fff0, 0xfffcfffc}},
	{{0x40015005, 0x50055415, 0x54155555, 0x55555555}},
	{{0xc003f00f, 0xf00ffc3f, 0xfc3fffff, 0xffffffff}},
	{{0x0aa02aa8, 0x2aa8aaaa, 0xaaaaaaaa, 0x355c0550}},
	{{0x00150055, 0x00fe03ba, 0x03be03ea, 0x002a00f7}},
	{{0x50005540, 0xb800ba80, 0xaea0bfc0, 0xaa00f000}},
	{{0x03f70ff5, 0x0ad90a95, 0x0a550054, 0x03f00ff0}},
	{{0xdfc05ff0, 0x67a056a0, 0x55a01500, 0x0fc00ff0}},
	{{0xaaabaaab, 0xaaabffff, 0xabaaabaa, 0xabaaffff}},
	{{0x5555aaab, 0xaaabffff, 0xabaaabaa, 0xabaaffff}},
	{{0x3fffeaaa, 0xeeaaeaaa, 0xeaaaeaaa, 0xeaaaeaaa}},
	{{0x5500a900, 0xa900a900, 0xa900a900, 0xa900fd55}},
	{{0x015501aa, 0x01aa01aa, 0x01aa01aa, 0x01aa55ff}},
	{{0x55aba9ab, 0xa9aba9ff, 0xa9aaa9aa, 0xa9aafd55}},
	{{0xa955a9aa, 0xa9aafdaa, 0xa9aaa9aa, 0xa9aa55ff}},
	{{0xaabfabff, 0xafffffff, 0xbfffbfff, 0xffffffff}},
	{{0xfeabffeb, 0xfffbffff, 0xfffefffe, 0xffffffff}},
};

static struct tile_data
decompress_tile_data(const struct compressed_tile_data *ctd)
{
	struct tile_data td;
	for (unsigned char i = 0; i < 64; i++)
		td.index[i] = ctd->four_bytes[i / 16] >> (30 - (i * 2 % 32)) &
			      3;
	return td;
}

struct tile_data get_tile_data(unsigned char t)
{
	if (t >= TILE_COUNT) {
		fprintf(stderr, "Given tile id is not valid\n");
		return (struct tile_data){0};
	}
	return decompress_tile_data(&tiles[t]);
}
