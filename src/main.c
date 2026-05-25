#include "app.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

int main(void) {
    app a;
    int exit_code = 0;

    if (app_create(&a, WINDOW_WIDTH, WINDOW_HEIGHT, "APP") != APP_SUCCESS) {
        exit_code = -1;
    } else {
        app_run(&a);
    }

    app_destroy(&a);

    return exit_code;
}
