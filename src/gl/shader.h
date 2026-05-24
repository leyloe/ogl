#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

typedef enum {
    shader_success = 0,
    shader_error_vertex,
    shader_error_fragment,
    shader_error_linking
} shader_result;

typedef struct shader {
    GLchar info_log[512];
    GLuint id;
} shader;

shader_result shader_create_program_vf(shader *s, const GLchar *vertex_source, const GLchar *fragment_source);
void shader_use(const shader *s);
void shader_set_int(const shader *s, const char *name, GLint value);
void shader_destroy(shader *s);

#endif
