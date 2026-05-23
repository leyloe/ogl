#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <glad/glad.h>

typedef struct vertex_buffer {
    GLuint id;
} vertex_buffer;

vertex_buffer vertex_buffer_create(const void *data, GLsizeiptr size, GLenum usage);
void vertex_buffer_destroy(vertex_buffer *vb);
void vertex_buffer_unbind(void);

#endif
