const char *fragment_shader =
	"#version 330 core\n"
	"uniform sampler2D tiles;\n"
	"uniform sampler2D palettes;\n"
	"uniform float palette_count;\n"
	"in vec2 ui;\n"
	"flat in int fpalette;\n"
	"out vec4 color;\n"
	"void main()\n"
	"{\n"
	"	float index = texture(tiles, ui).r * 255.0;\n"
	"	if (index == 0.0) color = vec4(0.0, 0.0, 0.0, 0.0);\n"
	"	else {\n"
	"	vec2 vpalette = vec2(index / 3.0, fpalette/(palette_count - 1));\n"
	"	color = texture(palettes, vpalette);\n"
	"}\n"
	"}\n";