#include "app.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

int main(void) {
    app a;
    int exit_code = 0;

    if (app_create(&a, WINDOW_WIDTH, WINDOW_HEIGHT, "APP") != APP_SUCCESS) {
        exit_code = -1;
    }

    if (app_run(&a) != APP_SUCCESS) {
        exit_code = -1;
    }

    app_destroy(&a);

    return exit_code;
}
