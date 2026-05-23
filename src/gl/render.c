#include <stdlib.h>
#include <glad/glad.h>

#include "render.h"
#include "vertex_buffer.h"
#include "vertex_array.h"
#include "shader.h"



renderer *render_create(void)
{
    const auto r = (renderer*)malloc(sizeof(renderer));
    return r;
}

render_result render_create_scene(renderer *r, const float *vertices, const GLsizeiptr size,
                                 const char *vs_src, const char *fs_src)
{
    const shader_result shader_status = shader_create_program_vf(&r->shader, vs_src, fs_src);
    if (shader_status == shader_error_vertex) {
        return render_shader_error_vertex;
    }
    if (shader_status == shader_error_fragment) {
        return render_shader_error_fragment;
    }
    if (shader_status == shader_error_linking) {
        return render_shader_error_linking;
    }

    r->vbo = vertex_buffer_create(vertices, size, GL_STATIC_DRAW);
    r->vao = vertex_array_create();

    r->vertex_count = (GLsizei)(size / (3 * (GLsizeiptr)sizeof(float)));

    vertex_array_create_attrib(&r->vao, 0, 3, GL_FLOAT, GL_FALSE, 3 * (GLsizei)sizeof(float), nullptr);
    vertex_buffer_unbind();
    vertex_array_unbind();

    return render_success;
}

const GLchar *render_get_shader_info_log(const renderer *r)
{
    return r->shader.info_log;
}

void render_draw(const renderer *r)
{
    shader_use(&r->shader);
    vertex_array_bind(&r->vao);
    glDrawArrays(GL_TRIANGLES, 0, r->vertex_count);
}

void render_destroy(renderer *r)
{
    if (r == nullptr) return;

    if (r->shader.id)
        shader_destroy(&r->shader);

    vertex_buffer_destroy(&r->vbo);
    vertex_array_destroy(&r->vao);
    free(r);
}
