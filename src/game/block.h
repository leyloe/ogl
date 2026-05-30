#ifndef BLOCK_H
#define BLOCK_H
#include "cglm/cglm.h"
#include "glad/glad.h"

#define VERTICES_PER_FACE 4

enum block_types {
    air = 0,
    dirt = 1,
};

typedef enum {
    front = 0, // +X
    back = 1, // -X
    left = 2, // +Y
    right = 3, // -Y
    top = 4, // +Z
    bottom = 5, // -Z
    count = 6
} faces;

typedef struct {
    vec3 vertices[VERTICES_PER_FACE];
    vec2 uv[VERTICES_PER_FACE];
} face_data;

typedef struct {
    vec3 position;
    face_data faces[count];
} block;

// Raw block positions
static const vec3 raw_faces[count][VERTICES_PER_FACE] = {
    [front]  = {{-0.5f,  0.5f,  0.5f}, { 0.5f,  0.5f,  0.5f}, { 0.5f, -0.5f,  0.5f}, {-0.5f, -0.5f,  0.5f}},
    [right]  = {{ 0.5f,  0.5f,  0.5f}, { 0.5f,  0.5f, -0.5f}, { 0.5f, -0.5f, -0.5f}, { 0.5f, -0.5f,  0.5f}},
    [back]   = {{ 0.5f,  0.5f, -0.5f}, {-0.5f,  0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f}, { 0.5f, -0.5f, -0.5f}},
    [left]   = {{-0.5f,  0.5f, -0.5f}, {-0.5f,  0.5f,  0.5f}, {-0.5f, -0.5f,  0.5f}, {-0.5f, -0.5f, -0.5f}},
    [top]    = {{-0.5f,  0.5f, -0.5f}, { 0.5f,  0.5f, -0.5f}, { 0.5f,  0.5f,  0.5f}, {-0.5f,  0.5f,  0.5f}},
    [bottom] = {{-0.5f, -0.5f,  0.5f}, { 0.5f, -0.5f,  0.5f}, { 0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f}},
};

static const vec2 dirt_uv[VERTICES_PER_FACE] = {
    {0.0f, 1.0f},
    {1.0f, 1.0f},
    {1.0f, 0.0f},
    {0.0f, 0.0f},
};

block block_create(vec3 pos);
face_data block_get_face_data(const block *b, faces f);

#endif
