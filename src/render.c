#include <glad/glad.h>
#include <GLFW/glfw3.h>

int renderInit()
{
    return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}