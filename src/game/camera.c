#include <game/camera.h>

camera camera_create(const window *window, const GLfloat speed, const GLfloat sensitivity, const GLfloat pos_x, const GLfloat pos_y, const GLfloat pos_z) {
    const camera c = {
        .window = window,
        .speed = speed,
        .sensitivity = sensitivity,
        .position = {pos_x, pos_y, pos_z},
        .up = {0.0F, 1.0F, 0.0F},
        .front = {0.0F, 0.0F, -1.0F},
        .right = {1.0F, 0.0F, 0.0F},
        .yaw = -90.0F,
    };
    return c;
}

void camera_get_projection_matrix(const camera *c, mat4 dest) {
    glm_perspective(glm_rad(45.0F), (GLfloat)c->window->width / (GLfloat)c->window->height, 0.1F, 100.0F, dest);
}

void camera_get_view_matrix(camera *c, mat4 dest) {
    vec3 center;
    glm_vec3_add(c->position, c->front, center);
    glm_lookat(c->position, center, c->up, dest);
}

void camera_input_controller(camera *c, const GLfloat dt) {
    GLFWwindow *win = c->window->handle;
    float v = c->speed * dt;


    if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
        glm_vec3_muladds(c->front,  v, c->position);
    if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
        glm_vec3_muladds(c->front, -v, c->position);
    if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
        glm_vec3_muladds(c->right, -v, c->position);
    if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
        glm_vec3_muladds(c->right,  v, c->position);

    if (glfwGetKey(win, GLFW_KEY_SPACE) == GLFW_PRESS)
        c->position[1] += v;
    if (glfwGetKey(win, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        c->position[1] -= v;
}

void camera_update(camera *c, const GLfloat dt) {
    camera_input_controller(c, dt);
}

