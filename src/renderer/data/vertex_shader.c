const char *vertex_shader =
	"#version 330 core\n"
	"layout (location = 0) in vec2 quad;\n"
	"layout (location = 1) in vec2 pos;\n"
	"layout (location = 2) in int tile;\n"
	"layout (location = 3) in int palette;\n"
	"layout (location = 4) in int flip;\n"
	"uniform vec2 pixel_size;\n"
	"uniform float tile_count;\n"
	"out vec2 ui;\n"
	"flat out int fpalette;\n"
	"void main()\n"
	"{\n"
	"	float tile_width = 8.0;\n"
	"	vec2 texture_offset = vec2(tile / tile_count, 0.0);\n"
	"	vec2 texture_scale = vec2(1.0 / tile_count, 1.0);\n"

	// scaling
	"	ui = quad * texture_scale;\n"

	// rotation
	"	vec2 center = vec2(texture_scale.x / 2, texture_scale.y / 2);\n"
	"	ui -= center;\n"
	"	if ((flip & 0x01) != 0) {\n"
	"	float aspect_ratio = 1.0 / tile_count;\n"
	"	ui = vec2(ui.y * aspect_ratio, -ui.x / aspect_ratio);\n"
	"}\n"
	"if ((flip & 0x02) != 0) ui.x = -ui.x;\n"
	"if ((flip & 0x04) != 0) ui.y = -ui.y;\n"
	"ui += center;\n"

	// translation
	"ui += texture_offset;\n"

	"fpalette = palette;\n"
	"vec2 clip_offset = pos * pixel_size - 1;\n"
	"vec2 position = quad * tile_width * pixel_size + clip_offset;\n"
	"position.y *= -1.0;\n"
	"gl_Position = vec4(position, 0.0, 1.0);\n"
	"}\n";