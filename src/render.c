#include <stdlib.h>
#include "render.h"

Renderer *renderInit(const float *vertices, GLsizeiptr size,
                     const char *vs_src, const char *fs_src)
{
    Renderer *r = malloc(sizeof(Renderer));
    if (!r)
        return NULL;

    r->shader = shaderInit();
    if (shaderCreateProgramVF(&r->shader, vs_src, fs_src) != 0)
    {
        free(r);
        return NULL;
    }

    r->vbo = vertexBufferInit(vertices, size, GL_STATIC_DRAW);
    r->vao = vertexArrayInit();

    r->vertex_count = (GLsizei)(size / (2 * sizeof(float)));

    vertexArrayCreateAttrib(&r->vao, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    vertexBufferUnbind();
    vertexArrayUnbind();

    return r;
}

void renderDraw(Renderer *r)
{
    shaderUse(&r->shader);
    vertexArrayBind(&r->vao);
    glDrawArrays(GL_TRIANGLES, 0, r->vertex_count);
    vertexArrayUnbind();
}

void renderDeinit(Renderer *r)
{
    shaderDeinit(&r->shader);
    vertexBufferDeinit(&r->vbo);
    vertexArrayDeinit(&r->vao);
    free(r);
}
