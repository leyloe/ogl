#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.h"

void window_hint(const int major, const int minor, const int profile)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, profile);
}

void window_destroy(void)
{
    glfwTerminate();
}

window window_create(const int width, const int height, const char *title)
{
    return (window){width, height, title, nullptr};
}

window_result window_open(window *w)
{
    if (!glfwInit())
        return window_glfw_error_init;

    window_hint(3, 3, GLFW_OPENGL_CORE_PROFILE);

    w->handle = glfwCreateWindow(w->width, w->height, w->title, nullptr, nullptr);
    if (!w->handle)
    {
        glfwTerminate();
        return window_glfw_error_create;
    }

    glfwMakeContextCurrent(w->handle);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcast-function-type-strict"
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        w->handle = nullptr;
        return window_glad_error_init;
    }
#pragma clang diagnostic pop

    return window_success;
}

int window_should_close(const window *w)
{
    return glfwWindowShouldClose(w->handle) != 0;
}

void window_update(const window *w)
{
    glfwSwapBuffers(w->handle);
    glfwPollEvents();
}
