#ifndef RENDER_H
#define RENDER_H

#include <glad/glad.h>
#include "vertexBuffer.h"
#include "vertexArray.h"
#include "shader.h"

typedef struct
{
    VertexArray vao;
    VertexBuffer vbo;
    Shader shader;
    GLsizei vertex_count;
} Renderer;

Renderer *renderInit(const float *vertices, GLsizeiptr size,
                     const char *vs_src, const char *fs_src);
void renderDraw(Renderer *r);
void renderDeinit(Renderer *r);

#endif
