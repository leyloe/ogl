#ifndef ELEMENT_BUFFER_H
#define ELEMENT_BUFFER_H

#include <glad/glad.h>

typedef struct element_buffer {
    GLuint id;
} element_buffer;

element_buffer element_buffer_create(const void *data, GLsizeiptr size, GLenum usage);
void element_buffer_destroy(element_buffer *eb);
void element_buffer_unbind(void);

#endif
