#include <glad/glad.h>

#include "vertexArray.h"

VertexArray vertexArrayInit()
{
    VertexArray va;

    glGenVertexArrays(1, &va.id);
    glBindVertexArray(va.id);

    return va;
}

void vertexArrayDelete(VertexArray *va)
{
    glDeleteVertexArrays(1, &va->id);
}

void vertexArrayUnbind()
{
    glBindVertexArray(0);
}

void vertexArrayBind(const VertexArray *va)
{
    glBindVertexArray(va->id);
}

void vertexArrayCreateAttrib(VertexArray *va, GLint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)
{
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(index);
}