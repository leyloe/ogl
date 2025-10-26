#include <stddef.h>
#include <glad/glad.h>

#include "shader.h"
#include "vertexArray.h"
#include "vertexBuffer.h"

Shader shaderInit() { return (Shader){0}; }

int shaderCreate(Shader *s, GLenum type, GLuint *shader, const GLchar *shaderSource)
{
    GLint status = 0;

    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &shaderSource, NULL);
    glCompileShader(*shader);

    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        glGetShaderInfoLog(*shader, 512, NULL, s->infolog);
        glDeleteShader(*shader);
        return 0;
    }

    return 1;
}

int shaderCreateProgramVF(Shader *s, const GLchar *vertexSource, const GLchar *fragmentSource)
{
    GLLuint vertex;
    GLLuint fragment;

    GLint status = shaderCreate(s, GL_VERTEX_SHADER, &vertex, vertexSource);
    if (status)
        return VERTEX_COMPILATION_ERROR;

    status = shaderCreate(s, GL_FRAGMENT_SHADER, &fragment, fragmentSource);
    if (status)
        return FRAGMENT_COMPILATION_ERROR;

    s->id = glCreateProgram();
    glAttachShader(s->id, vertex);
    glAttachShader(s->id, fragment);
    glLinkProgram(s->id);

    glGetProgramiv(s->id, GL_LINK_STATUS, &status);
    if (!status)
    {
        glGetProgramInfoLog(s->id, 512, NULL, s->infolog);
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