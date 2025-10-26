#ifndef SHADER_H
#define SHADER_H

typedef unsigned int GLLuint;

typedef struct Shader
{
    GLchar infolog[512];
    GLLuint id;
} Shader;

Shader shaderInit();
GLint shaderCreateProgramVF(Shader *s, const GLchar *vertexSource, const GLchar *fragmentSource);
void shaderUse(Shader *s);
void shaderDelete(Shader *s);

#endif