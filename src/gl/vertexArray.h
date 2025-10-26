#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

typedef struct VertexArray
{
    unsigned int id;
} VertexArray;

VertexArray vertexArrayInit();
void vertexArrayDelete(VertexArray *va);
void vertexArrayUnbind();
void vertexArrayCreateAttrib(VertexArray *va, GLint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);

#endif