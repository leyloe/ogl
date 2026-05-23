#include <glad/glad.h>

#include "vertex_buffer.h"

vertex_buffer vertex_buffer_create(const void *data, const GLsizeiptr size, const GLenum usage) {
    vertex_buffer vb;
    glGenBuffers(1, &vb.id);
    glBindBuffer(GL_ARRAY_BUFFER, vb.id);
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    return vb;
}

void vertex_buffer_destroy(vertex_buffer *vb) {
    glDeleteBuffers(1, &vb->id);
    vb->id = 0;
}

void vertex_buffer_unbind(void) {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
