#ifndef SHADER_H
#define SHADER_H

typedef struct Shader
{
    char infolog[512];
    unsigned int id;
} Shader;

Shader shaderInit();
GLint shaderCreateProgramVF(Shader *s, const char *vertexSource, const char *fragmentSource);
void shaderUse(Shader *s);

#endif