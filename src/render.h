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

#endif
