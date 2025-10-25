#include <stddef.h>
#include <glad/glad.h>

#include "shader.h"

Shader shaderInit() { return (Shader){0}; }

int shaderCreate(Shader *s, GLenum type, unsigned int *shader, const char *shaderSource)
{
    int success;

    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &shaderSource, NULL);
    glCompileShader(*shader);

    glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(*shader, 512, NULL, s->infolog);
        return -1;
    }

    return 1;
}

int shaderCreateProgramVF(Shader *s, const char *vertexSource, const char *fragmentSource)
{
    unsigned int vertex;
    unsigned int fragment;

    int success = shaderCreate(s, GL_VERTEX_SHADER, &vertex, vertexSource);
    if (!success)
        return success;

    success = shaderCreate(s, GL_FRAGMENT_SHADER, &fragment, fragmentSource);
    if (!success)
        return success;

    s->shaderProgram = glCreateProgram();
    glAttachShader(s->shaderProgram, vertex);
    glAttachShader(s->shaderProgram, fragment);
    glLinkProgram(s->shaderProgram);

    glGetProgramiv(s->shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(s->shaderProgram, 512, NULL, s->infolog);
        return -1;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return 1;
}

void shaderUse(Shader *s)
{
    glUseProgram(s->shaderProgram);
}

void shaderDeinit(Shader *s)
{
    glDeleteProgram(s->shaderProgram);
}