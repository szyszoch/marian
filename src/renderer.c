#include <renderer.h>

static renderer_t renderer;

void renderer_init()
{
    const char* vertex_shader_source = 
    "#version 330 core\n"
    "layout (location = 0) in vec4 vertex;\n"
    "out vec2 tex_coords;\n"
    "uniform mat4 model;\n"
    "uniform mat4 projection;\n"
    "void main()\n"
    "{\n"
    "   tex_coords = vertex.zw;\n"
    "   gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);\n"
    "}\n";

    const char* fragment_shader_source = 
    "#version 330 core\n"
    "out vec4 color;\n"
    "in vec2 tex_coords;\n"
    "uniform sampler2D image;\n"
    "void main()\n"
    "{\n"
    "   color = texture(image, tex_coords);\n"
    "}\n";

    renderer.shader = shader_create(vertex_shader_source, fragment_shader_source);
    shader_bind(&renderer.shader);
    mat4 projection;
    glm_ortho(0.0f, 512.0f, 480.0f, 0.0f, -1.0f, 1.0f, projection);
    shader_set_mat4(&renderer.shader, "projection", projection);
    
    float vertices[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };
    
    vbo_t vbo = vbo_create(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    vbo_data(&vbo, vertices, sizeof(vertices));
    
    renderer.vao = vao_create();
    vao_attributes(&renderer.vao, &vbo, 0, 4, GL_FLOAT, 4 * sizeof(float), 0);
}

void renderer_render(texture_t texture, vec2 position, vec2 size)
{
    shader_bind(&renderer.shader);
    
    mat4 model;
    glm_mat4_identity(model);
    glm_translate(model, (vec3){position[0], position[1], 0.0f});
    glm_scale(model, (vec3){size[0], size[1], 1.0f});
    shader_set_mat4(&renderer.shader, "model", model);

    texture_bind(texture);

    vao_bind(&renderer.vao);
    GL(glDrawArrays(GL_TRIANGLES, 0, 6));
}