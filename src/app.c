#include "app.h"
#include "render.h"
#include "window.h"
#include "mesh.h"
#include "shaders.h"
#include <stdio.h>

static GLfloat vertices[] = {
    -0.5F, 0.5F, 0.0F, // top left
    0.5F, 0.5F, 0.0F, // top right
    0.5F,  -0.5F, 0.0F, // bottom right
    -0.5F,  -0.5F,  0.0F  // bottom left
};

static GLfloat tex_coords[] = {
    0.0F, 1.0F,
    1.0F, 1.0F,
    1.0F, 0.0F,
    0.0F, 0.0F,
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
    a->texture = (texture){0};

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

    a->mesh = mesh_create(vertices, sizeof(vertices), 3, indices, sizeof(indices));
    mesh_add_attribute(&a->mesh, UV_ATTRIBUTE_LOCATION, tex_coords, sizeof(tex_coords), 2);

    texture_init();
    a->texture = texture_create();
    if (load_texture_from_file("../textures/dirt.png", &a->texture) != texture_success) {
        return APP_ERROR;
    }

    return APP_SUCCESS;
}

void app_run(const app *a) {
    GLfloat y_rot = 0.0F;

    while (!window_should_close(&a->window)) {
        mat4 model, view, proj;
        y_rot += 0.1F;

        render_clear();

        glm_mat4_identity(model);
        glm_mat4_identity(view);
        glm_perspective(glm_rad(60.0F), (GLfloat)a->window.width / (GLfloat)a->window.height, 0.1F, 100.0F, proj);

        glm_translate_make(model, (vec3){0.0F, 0.0F, -3.0F});
        glm_rotate(model, glm_rad(y_rot), (vec3){0.0F, 1.0F, 0.0F});


        shader_set_m4(&a->renderer->shader, "model", model);
        shader_set_m4(&a->renderer->shader, "view", view);
        shader_set_m4(&a->renderer->shader, "proj", proj);

        render_draw(a->renderer, &a->mesh, &a->texture);
        window_update(&a->window);
    }
}

void app_destroy(app *a) {
    if (a->window.handle != nullptr) {
        texture_destroy(&a->texture);
        mesh_destroy(&a->mesh);
        if (a->renderer) {
            render_destroy(a->renderer);
            a->renderer = nullptr;
        }
        window_destroy();
    }
}

