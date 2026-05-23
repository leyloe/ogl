#ifndef RENDER_H
#define RENDER_H

#include <glad/glad.h>

#include "vertex_array.h"
#include "vertex_buffer.h"
#include "shader.h"

typedef enum {
    render_success = 0,
    render_shader_error_vertex,
    render_shader_error_fragment,
    render_shader_error_linking
} render_result;

typedef struct renderer {
    vertex_array vao;
    vertex_buffer vbo;
    shader shader;
    GLsizei vertex_count;
} renderer;

renderer *render_create(void);
render_result render_create_scene(renderer *r, const float *vertices, GLsizeiptr size, const char *vs_src,
                                  const char *fs_src);
const GLchar *render_get_shader_info_log(const renderer *r);
void render_draw(const renderer *r);
void render_destroy(renderer *r);

#endif
