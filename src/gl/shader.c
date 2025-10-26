#include <stddef.h>
#include <glad/glad.h>

#include "shader.h"
#include "vertexArray.h"
#include "vertexBuffer.h"

Shader shaderInit() { return (Shader){0}; }

int shaderCreate(Shader *s, GLenum type, GLuint *shader, const GLchar *shaderSource)
{
    int ok = 0;

    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &shaderSource, NULL);
    glCompileShader(*shader);

    glGetShaderiv(*shader, GL_COMPILE_STATUS, &ok);
    if (!ok)
    {
        glGetShaderInfoLog(*shader, 512, NULL, s->infolog);
        glDeleteShader(*shader);
        return 0;
    }

    return 1;
}

int shaderLinkProgram(Shader *s, GLuint vertex, GLuint fragment)
{
    int ok = 0;

    s->id = glCreateProgram();
    glAttachShader(s->id, vertex);
    glAttachShader(s->id, fragment);
    glLinkProgram(s->id);

    glGetProgramiv(s->id, GL_LINK_STATUS, &ok);
    if (!ok)
    {
        glGetProgramInfoLog(s->id, 512, NULL, s->infolog);
        return 0;
    }

    return 1;
}

int shaderCreateProgramVF(Shader *s, const GLchar *vertexSource, const GLchar *fragmentSource)
{
    GLuint vertex;
    GLuint fragment;

    int ok = shaderCreate(s, GL_VERTEX_SHADER, &vertex, vertexSource);
    if (!ok)
        return VERTEX_COMPILATION_ERROR;

    ok = shaderCreate(s, GL_FRAGMENT_SHADER, &fragment, fragmentSource);
    if (!ok)
    {
        glDeleteShader(vertex);
        return FRAGMENT_COMPILATION_ERROR;
    }

    ok = shaderLinkProgram(s, vertex, fragment);
    if (!ok)
    {
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        return PROGRAM_LINKING_ERROR;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return 1;
}

void shaderUse(Shader *s)
{
    glUseProgram(s->id);
}

void shaderDelete(Shader *s)
{
    glDeleteProgram(s->id);
}