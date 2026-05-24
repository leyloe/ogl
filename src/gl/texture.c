#include "gl/texture.h"

#include <stb_image.h>
#include <glad/glad.h>

void texture_init(void) {
    stbi_set_flip_vertically_on_load(1);
}

texture texture_create(void) {
    texture t;

    glGenTextures(1, &t.id);
    glBindTexture(GL_TEXTURE_2D, t.id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

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
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    return texture_success;
}

void texture_unbind(void) {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void texture_bind(const texture *t) {
    glBindTexture(GL_TEXTURE_2D, t->id);
}

void texture_destroy(texture *t) {
    glDeleteTextures(1, &t->id);
    t->id = 0;
}
