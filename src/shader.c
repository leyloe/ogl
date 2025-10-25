#include <stddef.h>
#include <glad/glad.h>

#include "shader.h"

Shader shaderInit() { return (Shader){0}; }

GLint shaderCreate(Shader *s, GLenum type, unsigned int *shader, const char *shaderSource)
{
    GLint success = 0;

    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &shaderSource, NULL);
    glCompileShader(*shader);

    glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
    if (success != 0)
    {
        glGetShaderInfoLog(*shader, 512, NULL, s->infolog);
        return -1;
    }

    return 0;
}

GLint shaderCreateProgramVF(Shader *s, const char *vertexSource, const char *fragmentSource)
{
    unsigned int vertex;
    unsigned int fragment;

    GLint success = shaderCreate(s, GL_VERTEX_SHADER, &vertex, vertexSource);
    if (success != 0)
        return success;

    success = shaderCreate(s, GL_FRAGMENT_SHADER, &fragment, fragmentSource);
    if (success != 0)
        return success;

    s->id = glCreateProgram();
    glAttachShader(s->id, vertex);
    glAttachShader(s->id, fragment);
    glLinkProgram(s->id);

    glGetProgramiv(s->id, GL_LINK_STATUS, &success);
    if (success != 0)
    {
        glGetProgramInfoLog(s->id, 512, NULL, s->infolog);
        return -2;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return 0;
}

void shaderUse(Shader *s)
{
    glUseProgram(s->id);
}

void shaderDeinit(Shader *s)
{
    glDeleteProgram(s->id);
}