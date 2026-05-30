#ifndef CHUNK_H
#define CHUNK_H

#include "cglm/ivec3.h"
#include "glad/glad.h"

#define SIZE 16
#define HEIGHT 256

typedef struct {
    vec3 position;
    vec3* chunk_vertices;
    vec2* chunk_uvs;
    GLuint* chunk_indices;
} chunk;

void gen_chunk(chunk* c);
void gen_blocks(chunk* c);


#endif
