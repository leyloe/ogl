#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

typedef struct VertexBuffer
{
    unsigned int id;
} VertexBuffer;

VertexBuffer vertexBufferInit(const void *data, GLsizeiptr size, GLenum usage);
void vertexBufferDeinit(VertexBuffer *vb);
void vertexBufferUnbind();

#endif