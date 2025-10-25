#include <stdio.h>
#include "window.h"

void main()
{
    Window window = windowInit(800, 600, "title");

    if (windowCreate(&window) != 0)
    {
        printf("Failed to create window\n");
        return;
    }

    while (!windowShouldClose(&window))
        windowUpdate(&window);

    windowDeinit(&window);
}