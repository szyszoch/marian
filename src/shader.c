#include <shader.h>

static GLuint compile(GLenum type, const char* source)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char log[512];
        glGetShaderInfoLog(shader, 512, NULL, log);
        fprintf(stderr, "%s\n", log);
    }

    return shader;
}

shader_t shader_create(const char* vertex_shader_source, const char* fragment_shader_source)
{
    GLuint vertex_shader = compile(GL_VERTEX_SHADER, vertex_shader_source);
    GLuint fragment_shader = compile(GL_FRAGMENT_SHADER, fragment_shader_source);
    
    shader_t new_shader;
    new_shader.id = glCreateProgram();

    glAttachShader(new_shader.id, vertex_shader);
    glAttachShader(new_shader.id, fragment_shader);
    glLinkProgram(new_shader.id);
    
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    GLint success;
    glGetProgramiv(new_shader.id, GL_COMPILE_STATUS, &success);

    if (!success) {
        char log[512];
         glGetProgramInfoLog(new_shader.id, 512, NULL, log);
        fprintf(stderr, "%s\n", log);
    }

    return new_shader;
}

void shader_destroy(shader_t shader)
{
    glDeleteProgram(shader.id);
}

void shader_bind(shader_t shader)
{
    glUseProgram(shader.id);
}

void shader_set_int(shader_t shader, const char* name, int value)
{
    glUniform1i(glGetUniformLocation(shader.id, name), value);
}

void shader_set_uint(shader_t shader, const char* name, unsigned int value)
{
    glUniform1ui(glGetUniformLocation(shader.id, name), value);
}

void shader_set_float(shader_t shader, const char* name, float value)
{
    glUniform1f(glGetUniformLocation(shader.id, name), value);
}

void shader_set_vec2(shader_t shader, const char* name, float value1, float value2)
{
    glUniform2f(glGetUniformLocation(shader.id, name), value1, value2);
}

void shader_set_vec3(shader_t shader, const char* name, float value1, float value2, float value3)
{
    glUniform3f(glGetUniformLocation(shader.id, name), value1, value2, value3);
}

void shader_set_vec4(shader_t shader, const char* name, float value1, float value2, float value3, float value4)
{
    glUniform4f(glGetUniformLocation(shader.id, name), value1, value2, value3, value4);
}
