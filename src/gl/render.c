#include <stdlib.h>
#include <glad/glad.h>

#include "render.h"
#include "shader.h"



renderer *render_create(void)
{
    const auto r = (renderer*)malloc(sizeof(renderer));
    return r;
}

render_result render_load_shader(renderer *r, const char *vs_src, const char *fs_src)
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

    return render_success;
}

const GLchar *render_get_shader_info_log(const renderer *r)
{
    return r->shader.info_log;
}

void render_draw(const renderer *r, const mesh *m)
{
    shader_use(&r->shader);
    mesh_draw(m);
}

void render_destroy(renderer *r)
{
    if (r == nullptr) return;

    if (r->shader.id)
        shader_destroy(&r->shader);

    free(r);
}
