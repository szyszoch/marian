#include <shader.h>

static GLuint compile(GLenum type, const char* source)
{
    GLuint shader = GL(glCreateShader(type));
    GL(glShaderSource(shader, 1, &source, NULL));
    GL(glCompileShader(shader));

    GLint success;
    GL(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));

    if (!success) {
        char log[512];
        GL(glGetShaderInfoLog(shader, 512, NULL, log));
        fprintf(stderr, "%s\n", log);
    }

    return shader;
}

shader_t shader_create(const char* vertex_shader_source, const char* fragment_shader_source)
{
    GLuint vertex_shader = compile(GL_VERTEX_SHADER, vertex_shader_source);
    GLuint fragment_shader = compile(GL_FRAGMENT_SHADER, fragment_shader_source);
    
    shader_t new_shader;
    new_shader.id = GL(glCreateProgram());

    GL(glAttachShader(new_shader.id, vertex_shader));
    GL(glAttachShader(new_shader.id, fragment_shader));
    GL(glLinkProgram(new_shader.id));
    
    GL(glDeleteShader(vertex_shader));
    GL(glDeleteShader(fragment_shader));

    GLint success;
    GL(glGetProgramiv(new_shader.id, GL_LINK_STATUS, &success));

    if (!success) {
        char log[512];
        GL(glGetProgramInfoLog(new_shader.id, 512, NULL, log));
        fprintf(stderr, "%s\n", log);
    }

    return new_shader;
}

void shader_destroy(const shader_t* shader)
{
    GL(glDeleteProgram(shader->id));
}

void shader_bind(const shader_t* shader)
{
    GL(glUseProgram(shader->id));
}

void shader_set_mat4(const shader_t* shader, const char* name, mat4 value)
{
    GL(glUniformMatrix4fv(glGetUniformLocation(shader->id, name), 1, GL_FALSE, (const GLfloat*) value));
}