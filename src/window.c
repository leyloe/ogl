#include <GLFW/glfw3.h>

#include "window.h"

void windowHint(int major, int minor, int profile)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, profile);
}

void windowDeinit(Window *w)
{
    glfwTerminate();
}

Window windowInit(int width, int height, const char *title)
{
    Window w = {width, height, title, NULL};

    if (!glfwInit())
    {
        return (Window){0};
    }

    windowHint(4, 6, GLFW_OPENGL_CORE_PROFILE);

    w.handle = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!w.handle)
    {
        windowDeinit(&w);
        return (Window){0};
    }

    glfwMakeContextCurrent(w.handle);

    return w;
}

int windowShouldClose(Window *w)
{
    return glfwWindowShouldClose(w->handle);
}

void windowUpdate(Window *w)
{
    glfwSwapBuffers(w->handle);
    glfwPollEvents();
}