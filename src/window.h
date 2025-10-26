#ifndef WINDOW_H
#define WINDOW_H

typedef struct GLFWwindow GLFWwindow;

#define GLFW_INITIALIZATION_ERROR 0
#define GLFW_WINDOW_CREATION_ERROR -1
#define GLAD_INITIALIZATION_ERROR -2

typedef struct Window
{
    int width;
    int height;
    const char *title;
    GLFWwindow *handle;
} Window;

Window windowInit(int width, int height, const char *title);
void windowDestroy(Window *window);
int windowShouldClose(Window *window);
void windowUpdate(Window *window);

#endif
