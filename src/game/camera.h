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
    GLfloat pitch;
    GLfloat yaw;
} camera;

camera camera_create(const window *window, GLfloat speed, GLfloat sensitivity, GLfloat pos_x, GLfloat pos_y, GLfloat pos_z);
void camera_get_view_matrix(camera *c, mat4 dest);
void camera_get_projection_matrix(const camera *c, mat4 dest);
void camera_input_controller(camera *c, GLfloat dt);
void camera_update(camera *c, GLfloat dt);

#endif
