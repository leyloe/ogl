#include <glad/glad.h>

#include "shader.h"

static int shader_compile(shader *s, const GLenum type, GLuint *shader, const GLchar *source) {
    int ok = 0;

    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &source, nullptr);
    glCompileShader(*shader);

    glGetShaderiv(*shader, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        glGetShaderInfoLog(*shader, 512, nullptr, s->info_log);
        glDeleteShader(*shader);
        return 0;
    }

    return 1;
}

static int shader_link_program(shader *s, const GLuint vertex, const GLuint fragment) {
    int ok = 0;

    s->id = glCreateProgram();
    glAttachShader(s->id, vertex);
    glAttachShader(s->id, fragment);
    glLinkProgram(s->id);

    glGetProgramiv(s->id, GL_LINK_STATUS, &ok);
    if (!ok) {
        glGetProgramInfoLog(s->id, 512, nullptr, s->info_log);
        return 0;
    }

    return 1;
}

shader_result shader_create_program_vf(shader *s, const GLchar *vertex_source, const GLchar *fragment_source) {
    GLuint vertex;
    GLuint fragment;

    int ok = shader_compile(s, GL_VERTEX_SHADER, &vertex, vertex_source);
    if (!ok) {
        return shader_error_vertex;
    }

    ok = shader_compile(s, GL_FRAGMENT_SHADER, &fragment, fragment_source);
    if (!ok) {
        glDeleteShader(vertex);
        return shader_error_fragment;
    }

    ok = shader_link_program(s, vertex, fragment);
    if (!ok) {
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        return shader_error_linking;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return shader_success;
}

void shader_use(const shader *s) {
    glUseProgram(s->id);
}

void shader_set_int(const shader *s, const char *name, const GLint value) {
    glUseProgram(s->id);
    glUniform1i(glGetUniformLocation(s->id, name), value);
}

void shader_destroy(shader *s) {
    glDeleteProgram(s->id);
    s->id = 0;
}
