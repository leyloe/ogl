#include "gl/element_buffer.h"

element_buffer element_buffer_create(const void *data, const GLsizeiptr size, const GLenum usage) {
    element_buffer eb = {0};
    glGenBuffers(1, &eb.id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eb.id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
    return eb;
}

void element_buffer_destroy(element_buffer *eb) {
    if (eb->id) {
        glDeleteBuffers(1, &eb->id);
        eb->id = 0;
    }
}

void element_buffer_unbind(void) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
