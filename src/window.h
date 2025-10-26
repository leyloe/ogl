#ifndef WINDOW_H
#define WINDOW_H

typedef struct GLFWwindow GLFWwindow;

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
