#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <cglm/cglm.h>

#include "window.h"
#include "glad/glad.h"

typedef struct {
    const window *window;
    GLfloat speed;
    GLfloat screen_width;
    GLfloat screen_height;
    GLfloat sensitivity;
    vec3 position;
    vec3 up; // UnitY
    vec3 front; // UnitZ
    vec3 right; // UnitX
    GLfloat view_pitch;
    GLfloat view_yaw;
    bool view_first_move;
    vec2 view_last_position;
    GLfloat fov;
} camera;

camera camera_create(const window *window, GLfloat speed, GLfloat sensitivity, vec3 position, GLfloat fov);
void camera_get_view_matrix(camera *c, mat4 dest);
void camera_get_projection_matrix(const camera *c, mat4 dest);
void camera_input_controller(camera *c, GLfloat dt);
void camera_update_vectors(camera *c);
void camera_update(camera *c, GLfloat dt);

#endif
