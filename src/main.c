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

void cleanup(Renderer *renderer, Window *window)
{
    renderDeinit(renderer);
    windowDestroy(window);
}

void main()
{
    Window window = windowInit(800, 600, "title");

    if (!windowCreate(&window))
    {
        printf("Failed to create window\n");
        return;
    }

    Renderer *renderer = renderInit();
    if (!renderer)
    {
        printf("Failed to initialize renderer\n");
        windowDestroy(&window);
        return;
    }

    switch (renderCreateScene(renderer, vertices, sizeof(vertices), vertexShaderSource, fragmentShaderSource))
    {
    case SHADER_VERTEX_COMPILATION_ERROR:
        printf("Vertex shader compilation failed: %s\n", renderShaderInfolog(renderer));
        cleanup(renderer, &window);
        return;

    case SHADER_FRAGMENT_COMPILATION_ERROR:
        printf("Fragment shader compilation failed: %s\n", renderShaderInfolog(renderer));
        cleanup(renderer, &window);
        return;

    case SHADER_PROGRAM_LINKING_ERROR:
        printf("Shader program linking failed: %s\n", renderShaderInfolog(renderer));
        cleanup(renderer, &window);
        return;

    default:
        break;
    }

    while (!windowShouldClose(&window))
    {
        renderDraw(renderer);
        windowUpdate(&window);
    }

    cleanup(renderer, &window);
}