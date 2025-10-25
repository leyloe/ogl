#include <stdio.h>

#include "render.h"
#include "window.h"

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\n\0";

const float vertices[] = {
    -0.5f, -0.5f, 0.0f, // left
    0.5f, -0.5f, 0.0f,  // right
    0.0f, 0.5f, 0.0f    // top
};

void main()
{
    Window window = windowInit(800, 600, "title");

    if (windowCreate(&window) != 0)
    {
        printf("Failed to create window\n");
        return;
    }

    Renderer *renderer = renderInit(vertices, sizeof(vertices),
                                    vertexShaderSource, fragmentShaderSource);
    if (!renderer)
    {
        printf("Failed to initialize renderer\n");
        windowDeinit(&window);
        return;
    }

    while (!windowShouldClose(&window))
    {
        renderDraw(renderer);
        windowUpdate(&window);
    }

    renderDeinit(renderer);
    windowDeinit(&window);
}