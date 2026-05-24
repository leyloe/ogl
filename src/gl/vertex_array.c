#include <glad/glad.h>

#include "vertex_array.h"

vertex_array vertex_array_create(void) {
    vertex_array va;
    glGenVertexArrays(1, &va.id);
    glBindVertexArray(va.id);
    return va;
}

void vertex_array_destroy(vertex_array *va) {
    glDeleteVertexArrays(1, &va->id);
    va->id = 0;
}

void vertex_array_unbind(void) {
    glBindVertexArray(0);
}

void vertex_array_bind(const vertex_array *va) {
    glBindVertexArray(va->id);
}

void vertex_array_create_attrib(const GLuint index, const GLint size, const GLenum type, const GLboolean normalized,
                                const GLsizei stride, const void *pointer) {
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(index);
}
