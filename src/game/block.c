#include <string.h>
#include "game/block.h"

block block_create(vec3 pos) {
    block b = {0};
    glm_vec3_copy(pos, b.position);

    for (int f = 0; f < count; f++) {
        for (int v = 0; v < VERTICES_PER_FACE; v++) {
#pragma clang unsafe_buffer_usage begin
            b.faces[f].vertices[v][0] = raw_faces[f][v][0] + pos[0]; // X
            b.faces[f].vertices[v][1] = raw_faces[f][v][1] + pos[1]; // Y
            b.faces[f].vertices[v][2] = raw_faces[f][v][2] + pos[2]; // Z
        }
        memcpy(b.faces[f].uv, dirt_uv, sizeof dirt_uv);
#pragma clang unsafe_buffer_usage end
    }

    return b;
}

face_data block_get_face_data(const block *b, const faces f) {
#pragma clang unsafe_buffer_usage begin
    return b->faces[f];
#pragma clang unsafe_buffer_usage end
}
