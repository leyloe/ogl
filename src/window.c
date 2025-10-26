#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.h"

void windowHint(int major, int minor, int profile)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, profile);
}

void windowDestroy(Window *w)
{
    glfwTerminate();
}

Window windowInit(int width, int height, const char *title) { return (Window){width, height, title, NULL}; }

int windowCreate(Window *w)
{
    if (!glfwInit())
        return GLFW_INITIALIZATION_ERROR;

    windowHint(4, 6, GLFW_OPENGL_CORE_PROFILE);

    w->handle = glfwCreateWindow(w->width, w->height, w->title, NULL, NULL);
    if (!w->handle)
    {
        glfwTerminate();
        return GLFW_WINDOW_CREATION_ERROR;
    }

    glfwMakeContextCurrent(w->handle);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return GLAD_INITIALIZATION_ERROR;
    }

    return 1;
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