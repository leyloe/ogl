#include <stdlib.h>
#include <stddef.h>
#include <glad/glad.h>

#include "render.h"
#include "vertexBuffer.h"
#include "vertexArray.h"
#include "shader.h"

struct Renderer
{
    VertexArray vao;
    VertexBuffer vbo;
    Shader shader;
    GLsizei vertex_count;
};

Renderer *renderInit()
{
    Renderer *r = malloc(sizeof(Renderer));
    if (!r)
    {
        return NULL;
    }

    return r;
}

GLint renderCreate(Renderer *r, const float *vertices, GLsizeiptr size,
                   const char *vs_src, const char *fs_src)
{
    r->shader = shaderInit();
    GLint status = shaderCreateProgramVF(&r->shader, vs_src, fs_src);
    if (status)
    {
        return 0;
    }

    r->vbo = vertexBufferInit(vertices, size, GL_STATIC_DRAW);
    r->vao = vertexArrayInit();

    r->vertex_count = (GLsizei)(size / (3 * sizeof(float)));

    vertexArrayCreateAttrib(&r->vao, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    vertexBufferUnbind();
    vertexArrayUnbind();

    return 1;
}

const GLchar *renderShaderInfolog(Renderer *r)
{
    return r->shader.infolog;
}

void renderDraw(Renderer *r)
{
    shaderUse(&r->shader);
    vertexArrayBind(&r->vao);
    glDrawArrays(GL_TRIANGLES, 0, r->vertex_count);
}

void renderDeinit(Renderer *r)
{
    shaderDelete(&r->shader);
    vertexBufferDelete(&r->vbo);
    vertexArrayDelete(&r->vao);
    free(r);
}
