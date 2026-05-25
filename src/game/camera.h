#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include "glad/glad.h"

typedef struct {
    GLfloat speed;
    GLfloat screen_width;
    GLfloat screen_height;
    GLfloat sensitivity;
    vec3 position;
    vec3 up; // UnitY
    vec3 front; // UnitZ
    vec3 right; // UnitX
} camera;

camera camera_create(GLfloat speed, GLfloat screen_width, GLfloat screen_height, GLfloat sensitivity);
void camera_get_view_matrix(camera *c, mat4 dest);
void camera_get_projection_matrix(const camera *c, mat4 dest);
void camera_input_controller();
void camera_update();

#endif
