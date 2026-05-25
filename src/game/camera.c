#include <game/camera.h>

camera camera_create(const GLfloat speed, const GLfloat screen_width, const GLfloat screen_height, const GLfloat sensitivity) {
    camera c = {
        .speed = speed,
        .screen_width = screen_width,
        .screen_height = screen_height,
        .sensitivity = sensitivity,
        .up = {0.0F, 1.0F, 0.0F},
        .front = {0.0F, 0.0F, 1.0F},
        .right = {1.0F, 0.0F, 0.0F},
    };
    return c;
}

void camera_get_projection_matrix(const camera *c, mat4 dest) {
    glm_perspective(glm_rad(45.0F), c->screen_width / c->screen_height, 0.1F, 100.0F, dest);
}
