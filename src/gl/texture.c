#include "gl/texture.h"
#include "gl/vertex_buffer.h"

#include <stb_image.h>
#include "glad/glad.h"

texture texture_create(const vertex_array *vao, const GLfloat* tex_coords, const GLsizeiptr text_coords_size, const GLint floats_per_tex_coord) {
    texture t;

    glGenTextures(1, &t.id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, t.id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    vertex_array_bind(vao);
    t.vbo = vertex_buffer_create(tex_coords, text_coords_size, GL_STATIC_DRAW);
    vertex_array_create_attrib(vao, 1, floats_per_tex_coord, GL_FLOAT, GL_FALSE,
                               floats_per_tex_coord * (GLsizei)sizeof(float), nullptr);

    vertex_buffer_unbind();
    vertex_array_unbind();

    return t;
}

texture_result load_texture_from_file(const char *path, const texture *t) {
    int w, h, channels;
    unsigned char *data = stbi_load(path, &w, &h, &channels, STBI_rgb_alpha);
    if (data == nullptr) {
        return texture_error_load;
    }

    glBindTexture(GL_TEXTURE_2D, t->id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);

    return texture_success;
}

void texture_unbind(void) {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void texture_bind(const texture *t) {
    glBindTexture(GL_TEXTURE_2D, t->id);
}

void texture_destroy( texture *t) {
    vertex_buffer_destroy(&t->vbo);
    glDeleteTextures(1, &t->id);
}
