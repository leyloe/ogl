#include "app.h"
#include "render.h"
#include "window.h"
#include "mesh.h"
#include <stdio.h>

// static const char *vertex_shader_source = "#version 330 core\n"
//                                           "layout (location = 0) in vec3 aPos;\n"
//                                           "layout (location =1) in vec2 aTexCoord;\n"
//                                           "out vec2 textCoord;\n"
//                                           "void main()\n"
//                                           "{\n"
//                                           "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//                                           "   textCoord = aTexCoord;\n"
//                                           "}\0";
// static const char *fragment_shader_source = "#version 330 core\n"
//                                             "in vec2 textCoord;\n"
//                                             "uniform sampler2D texture0;\n"
//                                             "out vec4 FragColor;\n"
//                                             "void main()\n"
//                                             "{\n"
//                                             "   FragColor = texture(texture0, textCoord);\n"
//                                             "}\0";

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
    -0.5F, 0.5F, 0.0F, // top left
    0.5F, 0.5F, 0.0F, // top right
    0.5F,  -0.5F, 0.0F, // bottom right
    -0.5F,  -0.5F,  0.0F  // bottom left
};

static const unsigned int indices[] = {
    // top triangle
    0, 1, 2,
    // bottom triangle
    0, 2, 3
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

static int load_shader_or_report_error(renderer *r) {
    const render_result result = render_load_shader(r, vertex_shader_source, fragment_shader_source);

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
    a->mesh = (mesh){0};

    if (create_window_or_report_error(&a->window) != APP_SUCCESS) {
        return APP_ERROR;
    }

    a->renderer = render_create();
    if (!a->renderer) {
        output_error("Failed to initialize renderer");
        return APP_ERROR;
    }

    if (load_shader_or_report_error(a->renderer) != APP_SUCCESS) {
        return APP_ERROR;
    }

    a->mesh = mesh_create(vertices, indices, sizeof(vertices), sizeof(indices), 3);

    return APP_SUCCESS;
}

void app_run(const app *a) {
    while (!window_should_close(&a->window)) {
        render_draw(a->renderer, &a->mesh);
        window_update(&a->window);
    }
}

void app_destroy(app *a) {
    mesh_destroy(&a->mesh);
    if (a->renderer) {
        render_destroy(a->renderer);
        a->renderer = nullptr;
    }
    window_destroy(&a->window);
}
