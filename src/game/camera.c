#include <game/camera.h>

camera camera_create(const window *window, const GLfloat speed, const GLfloat sensitivity, vec3 position, GLfloat fov) {
    const camera c = {
        .window = window,
        .speed = speed,
        .sensitivity = sensitivity,
        .up = {0.0F, 1.0F, 0.0F},
        .front = {0.0F, 0.0F, -1.0F},
        .right = {1.0F, 0.0F, 0.0F},
        .view_yaw = -90.0F,
        .view_pitch = 0.0F,
        .fov = fov,
        .view_first_move = true,
    };

    glm_vec3_copy(position, c.position);


    return c;
}

void camera_get_projection_matrix(const camera *c, mat4 dest) {
    glm_perspective(glm_rad(c->fov), (GLfloat)c->window->width / (GLfloat)c->window->height, 0.1F, 100.0F, dest);
}

void camera_get_view_matrix(camera *c, mat4 dest) {
    vec3 center;
    glm_vec3_add(c->position, c->front, center);
    glm_lookat(c->position, center, c->up, dest);
}

void camera_update_vectors(camera *c) {
    const float yaw_r = glm_rad(c->view_yaw);
    const float pitch_r = glm_rad(c->view_pitch);
    const float cp = cosf(pitch_r);

    c->front[0] = cp * cosf(yaw_r);
    c->front[1] = sinf(pitch_r);
    c->front[2] = cp * sinf(yaw_r);
    glm_vec3_normalize(c->front);

    glm_vec3_crossn(c->front, GLM_YUP, c->right);
    glm_vec3_crossn(c->right, c->front, c->up);
}

void camera_input_controller(camera *c, const GLfloat dt) {
    GLFWwindow *win = c->window->handle;
    const float v = c->speed * dt;
    double mouse_x, mouse_y;

    glfwGetCursorPos(win, &mouse_x, &mouse_y);

    // FOV control
    if (glfwGetKey(win, GLFW_KEY_X) == GLFW_PRESS)
        c->fov += 100.0F * dt;
    if (glfwGetKey(win, GLFW_KEY_C) == GLFW_PRESS)
        c->fov -= 100.0F * dt;

    // Supported FOV range: 10-170 degrees
    if (c->fov < 10.0F) c->fov = 10.0F;
    if (c->fov > 170.0F) c->fov = 170.0F;

    // Position control
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

    // View control
    if (c->view_first_move) {
        c->view_last_position[0] = (GLfloat)mouse_x;
        c->view_last_position[1] = (GLfloat)mouse_y;
        c->view_first_move = false;
    } else {
        const GLfloat dx = (GLfloat)mouse_x - c->view_last_position[0];
        const GLfloat dy = (GLfloat)mouse_y - c->view_last_position[1];
        c->view_last_position[0] = (GLfloat)mouse_x;
        c->view_last_position[1] = (GLfloat)mouse_y;

        c->view_yaw   += dx * c->sensitivity;
        c->view_pitch -= dy * c->sensitivity;
        c->view_pitch  = glm_clamp(c->view_pitch, -89.0F, 89.0F);
    }
    camera_update_vectors(c);
}

void camera_update(camera *c, const GLfloat dt) {
    camera_input_controller(c, dt);
}

