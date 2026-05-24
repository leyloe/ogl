#ifndef TEXTURE_H
#define TEXTURE_H
#include "glad/glad.h"

typedef enum {
    texture_success = 0,
    texture_error_load
} texture_result;

typedef struct {
    GLuint id;
} texture;

texture texture_create(void);
void texture_destroy( texture *t);
texture_result load_texture_from_file(const char *path, const texture *t);
void texture_bind(const texture *t);
void texture_unbind(void);

#endif
