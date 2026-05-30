#include <glad/glad.h>

#include "mesh.h"

#include "element_buffer.h"

mesh mesh_create(const float *positions, const GLsizeiptr positions_size, const GLint floats_per_position,
                 const unsigned int *indices, const GLsizeiptr index_size) {
    mesh m = {0};

    m.vao = vertex_array_create();

    m.vbo_positions = vertex_buffer_create(positions, positions_size, GL_STATIC_DRAW);
    vertex_array_create_attrib(0, floats_per_position, GL_FLOAT, GL_FALSE,
                               floats_per_position * (GLsizei)sizeof(float), nullptr);

    m.ebo = element_buffer_create(indices, index_size, GL_STATIC_DRAW);

    m.index_count = (GLsizei)(index_size / (GLsizeiptr)sizeof(unsigned int));

    return m;
}

mesh mesh_create_interleaved(const float *positions, const GLsizeiptr positions_size, const unsigned int *indices, const GLsizeiptr index_size) {
    mesh m = {0};
    const GLsizei stride = 5 * (GLsizei)sizeof(float);

    m.vao = vertex_array_create();
    m.vbo_positions = vertex_buffer_create(positions, positions_size, GL_STATIC_DRAW);


    // position -> location 0
    vertex_array_create_attrib(0, 3, GL_FLOAT, GL_FALSE, stride, nullptr);
    // texture coords -> location 1 (offset 3 floats into each vertex)
    vertex_array_create_attrib(1, 2, GL_FLOAT, GL_FALSE, stride, (const void *)(3 * sizeof(float)));

    m.ebo = element_buffer_create(indices, index_size, GL_STATIC_DRAW);
    m.index_count = (GLsizei)(index_size / (GLsizeiptr)sizeof(unsigned int));

    return m;
}

void mesh_add_attribute(mesh *m, const GLuint location, const float *data, const GLsizeiptr data_size, const GLint floats_per_element) {
    if (m->attribute_count >= MESH_MAX_ATTRIBUTES) return;
    vertex_array_bind(&m->vao);
#pragma clang unsafe_buffer_usage begin
    m->attribute_vbo_array[m->attribute_count] = vertex_buffer_create(data, data_size, GL_STATIC_DRAW);
#pragma clang unsafe_buffer_usage end
    vertex_array_create_attrib(location, floats_per_element, GL_FLOAT, GL_FALSE,
                               floats_per_element * (GLsizei)sizeof(float), nullptr);
    m->attribute_count++;
}

void mesh_draw(const mesh *m) {
    vertex_array_bind(&m->vao);
    glDrawElements(GL_TRIANGLES, m->index_count, GL_UNSIGNED_INT, nullptr);
}

void mesh_destroy(mesh *m) {
    vertex_buffer_destroy(&m->vbo_positions);
#pragma clang unsafe_buffer_usage begin
    for (int i = 0; i < m->attribute_count; i++) {
        vertex_buffer_destroy(&m->attribute_vbo_array[i]);
    }
#pragma clang unsafe_buffer_usage end
    vertex_array_destroy(&m->vao);
    element_buffer_destroy(&m->ebo);
    m->index_count = 0;
    m->attribute_count = 0;
}
