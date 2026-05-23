#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

typedef enum {
    shader_success = 1,
    shader_error_vertex = 0,
    shader_error_fragment = -1,
    shader_error_linking = -2
} shader_result;

typedef struct shader {
    GLchar info_log[512];
    GLuint id;
} shader;

shader shader_create(void);
shader_result shader_create_program_vf(shader *s, const GLchar *vertex_source, const GLchar *fragment_source);
void shader_use(const shader *s);
void shader_destroy(shader *s);

#endif
