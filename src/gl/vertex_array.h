#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <glad/glad.h>

typedef struct vertex_array {
    GLuint id;
} vertex_array;

vertex_array vertex_array_create(void);
void vertex_array_destroy(vertex_array *va);
void vertex_array_bind(const vertex_array *va);
void vertex_array_unbind(void);
void vertex_array_create_attrib(const vertex_array *va, GLuint index, GLint size, GLenum type, GLboolean normalized,
                                GLsizei stride, const void *pointer);

#endif
