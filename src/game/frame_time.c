#include "fame_time.h"
#include "GLFW/glfw3.h"

frame_time frame_time_init() {
    const frame_time frame = {0};
    return frame;
}

void frame_time_get(frame_time *f) {
    f->now = glfwGetTime();
    f->dt = (float)(f->now - f->last);
    f->last = f->now;
}
