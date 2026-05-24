#ifndef TEXTURE_H
#define TEXTURE_H
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "glad/glad.h"

typedef enum {
    texture_success = 0,
    texture_error_load
} texture_result;

typedef struct {
    GLuint id;
    vertex_buffer vbo;
} texture;

texture texture_create(const vertex_array *vao, const GLfloat* tex_coords, GLsizeiptr text_coords_size, GLint floats_per_tex_coord);
void texture_destroy( texture *t);
texture_result load_texture_from_file(const char *path, const texture *t);
void texture_bind(const texture *t);
void texture_unbind(void);

#endif
