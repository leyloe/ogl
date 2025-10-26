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

void printe(const char *message) { fprintf(stderr, "%s\n", message); }

void printShaderError(Renderer *renderer, const char *message) { fprintf(stderr, "%s: %s\n", message, renderShaderInfolog(renderer)); }

void main()
{
    Window window = windowInit(800, 600, "title");

    switch (windowCreate(&window))
    {
    case GLFW_INITIALIZATION_ERROR:
        printe("Failed to initialize GLFW");
        return;

    case GLFW_WINDOW_CREATION_ERROR:
        printe("Failed to create GLFW window");
        return;

    case GLAD_INITIALIZATION_ERROR:
        printe("Failed to initialize GLAD");
        return;

    default:
        break;
    }

    Renderer *renderer = renderInit();
    if (!renderer)
    {
        printe("Failed to initialize renderer");
        windowDestroy(&window);
        return;
    }

    switch (renderCreateScene(renderer, vertices, sizeof(vertices), vertexShaderSource, fragmentShaderSource))
    {
    case SHADER_VERTEX_COMPILATION_ERROR:
        printShaderError(renderer, "Vertex shader compilation failed");
        cleanup(renderer, &window);
        return;

    case SHADER_FRAGMENT_COMPILATION_ERROR:
        printShaderError(renderer, "Fragment shader compilation failed");
        cleanup(renderer, &window);
        return;

    case SHADER_PROGRAM_LINKING_ERROR:
        printShaderError(renderer, "Shader program linking failed");
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