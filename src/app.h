#ifndef APP_H
#define APP_H

#include "mesh.h"
#include "window.h"
#include "render.h"
#include "texture.h"

#define APP_SUCCESS 0
#define APP_ERROR   (-1)

typedef struct {
    window window;
    renderer *renderer;
} app;

int app_create(app *a, int width, int height, const char *title);
int app_run(const app *a);
void app_destroy(app *a);

#endif
