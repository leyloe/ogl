#ifndef SHADER_H
#define SHADER_H

#define VERTEX_COMPILATION_ERROR 0
#define FRAGMENT_COMPILATION_ERROR -1
#define PROGRAM_LINKING_ERROR -2

typedef unsigned int GLLuint;

typedef struct Shader
{
    GLchar infolog[512];
    GLLuint id;
} Shader;

Shader shaderInit();
int shaderCreateProgramVF(Shader *s, const GLchar *vertexSource, const GLchar *fragmentSource);
void shaderUse(Shader *s);
void shaderDelete(Shader *s);

#endif