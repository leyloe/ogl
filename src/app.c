#include "app.h"
#include "gl/render.h"
#include "window.h"
#include "gl/mesh.h"
#include "shaders.h"
#include "game/camera.h"
#include "game/fame_time.h"
#include <stdio.h>

static GLfloat vertices[] = {
    // front face
    -0.5F, 0.5F, 0.5F, // top left
    0.5F, 0.5F, 0.5F, // top right
    0.5F, -0.5F, 0.5F, // bottom right
    -0.5F, -0.5F, 0.5F, // bottom left
    // right face
    0.5F, 0.5F, 0.5F, // top left
    0.5F, 0.5F, -0.5F, // top right
    0.5F, -0.5F, -0.5F, // bottom right
    0.5F, -0.5F, 0.5F, // bottom left
    // back face
    0.5F, 0.5F, -0.5F, // top left
    -0.5F, 0.5F, -0.5F, // top right
    -0.5F, -0.5F, -0.5F, // bottom right
    0.5F, -0.5F, -0.5F, // bottom left
    // left face
    -0.5F, 0.5F, -0.5F, // top left
    -0.5F, 0.5F, 0.5F, // top right
    -0.5F, -0.5F, 0.5F, // bottom right
    -0.5F, -0.5F, -0.5F, // bottom left
    // top face
    -0.5F, 0.5F, -0.5F, // top left
    0.5F, 0.5F, -0.5F, // top right
    0.5F, 0.5F, 0.5F, // bottom right
    -0.5F, 0.5F, 0.5F, // bottom left
    // bottom face
    -0.5F, -0.5F, 0.5F, // top left
    0.5F, -0.5F, 0.5F, // top right
    0.5F, -0.5F, -0.5F, // bottom right
    -0.5F, -0.5F, -0.5F, // bottom left
};

static GLfloat tex_coords[] = {
    0.0F, 1.0F,
    1.0F, 1.0F,
    1.0F, 0.0F,
    0.0F, 0.0F,

    0.0F, 1.0F,
    1.0F, 1.0F,
    1.0F, 0.0F,
    0.0F, 0.0F,

    0.0F, 1.0F,
    1.0F, 1.0F,
    1.0F, 0.0F,
    0.0F, 0.0F,

    0.0F, 1.0F,
    1.0F, 1.0F,
    1.0F, 0.0F,
    0.0F, 0.0F,

    0.0F, 1.0F,
    1.0F, 1.0F,
    1.0F, 0.0F,
    0.0F, 0.0F,

    0.0F, 1.0F,
    1.0F, 1.0F,
    1.0F, 0.0F,
    0.0F, 0.0F,
};
static const unsigned int indices[] = {
    0,  1,  2,   0,  2,  3,    // front
    4,  5,  6,   4,  6,  7,    // right
    8,  9,  10,  8,  10, 11,   // back
    12, 13, 14,  12, 14, 15,   // left
    16, 17, 18,  16, 18, 19,   // top
    20, 21, 22,  20, 22, 23,   // bottom
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
    shader_set_int(&a->renderer->shader,"texture0", 0);

    texture_init();

    render_enable_depth_test();

    return APP_SUCCESS;
}

int app_run(const app *a) {
    mesh mesh = {0};
    texture texture = {0};

    frame_time frame_time;
    camera cam;

    mesh = mesh_create(vertices, sizeof(vertices), 3, indices, sizeof(indices));
    mesh_add_attribute(&mesh, UV_ATTRIBUTE_LOCATION, tex_coords, sizeof(tex_coords), 2);

    if (load_texture_from_file(&texture, "../textures/dirt.png") != texture_success) {
        return APP_ERROR;
    }

    cam = camera_create(&a->window, 5.0F, 0.1F, 0.0F, 0.0F, 0.0F);
    glfwSetInputMode(a->window.handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    frame_time = frame_time_init();

    while (!window_should_close(&a->window)) {
        mat4 model, view, proj;

        frame_time_get(&frame_time);
        camera_update(&cam, frame_time.dt);
        render_clear();

        glm_mat4_identity(model);
        camera_get_view_matrix(&cam, view);
        camera_get_projection_matrix(&cam, proj);

        shader_set_m4(&a->renderer->shader, "model", model);
        shader_set_m4(&a->renderer->shader, "view", view);
        shader_set_m4(&a->renderer->shader, "proj", proj);

        render_draw(a->renderer, &mesh, &texture);
        window_update(&a->window);
    }

    texture_destroy(&texture);
    mesh_destroy(&mesh);

    return APP_SUCCESS;
}

void app_destroy(app *a) {
    if (a->window.handle != nullptr) {
        if (a->renderer) {
            render_destroy(a->renderer);
            a->renderer = nullptr;
        }
        window_destroy();
    }
}

