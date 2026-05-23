#include "app.h"
#include "render.h"
#include "window.h"
#include <stdio.h>

static const char *vertex_shader_source = "#version 330 core\n"
                                          "layout (location = 0) in vec3 aPos;\n"
                                          "void main()\n"
                                          "{\n"
                                          "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                          "}\0";
static const char *fragment_shader_source = "#version 330 core\n"
                                            "out vec4 FragColor;\n"
                                            "void main()\n"
                                            "{\n"
                                            "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                            "}\n\0";

static float vertices[] = {
    -0.5F, -0.5F, 0.0F, // left
    0.5F,  -0.5F, 0.0F, // right
    0.0F,  0.5F,  0.0F  // top
};

static void output_error(const char *message) {
    (void)fprintf(stderr, "%s\n", message);
}

static void print_shader_error(const renderer *r, const char *message) {
    (void)fprintf(stderr, "%s: %s\n", message, render_get_shader_info_log(r));
}

static int create_window_or_report_error(window *w) {
    const window_result result = window_open(w);

    if (result == window_glfw_error_init) {
        output_error("Failed to initialize GLFW");
        return APP_ERROR;
    }
    if (result == window_glfw_error_create) {
        output_error("Failed to create GLFW window");
        return APP_ERROR;
    }
    if (result == window_glad_error_init) {
        output_error("Failed to initialize GLAD");
        return APP_ERROR;
    }
    return APP_SUCCESS;
}

static int create_scene_or_report_error(renderer *r) {
    const render_result result =
        render_create_scene(r, vertices, sizeof(vertices), vertex_shader_source, fragment_shader_source);

    if (result == render_shader_error_vertex) {
        print_shader_error(r, "Vertex shader compilation failed");
        return APP_ERROR;
    }
    if (result == render_shader_error_fragment) {
        print_shader_error(r, "Fragment shader compilation failed");
        return APP_ERROR;
    }
    if (result == render_shader_error_linking) {
        print_shader_error(r, "Shader program linking failed");
        return APP_ERROR;
    }
    return APP_SUCCESS;
}

int app_create(app *a, const int width, const int height, const char *title) {
    a->window = window_create(width, height, title);
    a->renderer = nullptr;

    if (create_window_or_report_error(&a->window) != APP_SUCCESS) {
        return APP_ERROR;
    }

    a->renderer = render_create();
    if (!a->renderer) {
        output_error("Failed to initialize renderer");
        return APP_ERROR;
    }

    return create_scene_or_report_error(a->renderer);
}

void app_run(const app *a) {
    while (!window_should_close(&a->window)) {
        render_draw(a->renderer);
        window_update(&a->window);
    }
}

void app_destroy(app *a) {
    if (a->renderer) {
        render_destroy(a->renderer);
        a->renderer = nullptr;
    }
    window_destroy(&a->window);
}
