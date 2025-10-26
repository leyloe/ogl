#include <glad/glad.h>

#include "vertexBuffer.h"

VertexBuffer vertexBufferInit(const void *data, GLsizeiptr size, GLenum usage)
{
    VertexBuffer vb;

    glGenBuffers(1, &vb.id);
    glBindBuffer(GL_ARRAY_BUFFER, vb.id);
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);

    return vb;
}

void vertexBufferDelete(VertexBuffer *vb)
{
    glDeleteBuffers(1, &vb->id);
}

void vertexBufferUnbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}