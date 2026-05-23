#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

typedef enum {
    window_success = 0,
    window_glfw_error_init,
    window_glfw_error_create,
    window_glad_error_init
} window_result;

typedef struct window {
    int width;
    int height;
    const char *title;
    GLFWwindow *handle;
} window;

window window_create(int width, int height, const char *title);
void window_hint(int major, int minor, int profile);
window_result window_open(window *w);
void window_destroy(const window *w);
int window_should_close(const window *w);
void window_update(const window *w);

#endif
