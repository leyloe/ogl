#include <stdio.h>
#include "window.h"

void main()
{
    Window window = windowInit(800, 600, "title");
    if (!&window)
        printf("Failed to create window");

    while (!windowShouldClose(&window))
        windowUpdate(&window);

    windowDeinit(&window);
}