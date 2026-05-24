#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>

#include "vertex_array.h"
#include "vertex_buffer.h"
#include "element_buffer.h"

#define MESH_MAX_ATTRIBUTES 8

typedef struct {
    vertex_array vao;
    vertex_buffer vbo_positions;
    element_buffer ebo;
    vertex_buffer attribute_vbo_array[MESH_MAX_ATTRIBUTES];
    int attribute_count;
    GLsizei index_count;
} mesh;

mesh mesh_create(const float *positions, GLsizeiptr positions_size, GLint floats_per_position,
                 const unsigned int *indices, GLsizeiptr index_size);
void mesh_add_attribute(mesh *m, GLuint location, const float *data, GLsizeiptr data_size, GLint floats_per_element);
void mesh_draw(const mesh *m);
void mesh_destroy(mesh *m);

#endif
