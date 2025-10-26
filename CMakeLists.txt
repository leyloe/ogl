cmake_minimum_required(VERSION 3.30)

project(ogl)

set(SRC
    src/main.c
    src/window.c
    src/gl/render.c
    src/gl/shader.c
    src/gl/vertexArray.c
    src/gl/vertexBuffer.c
    src/gl/glad.c
)

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gl
)


target_link_libraries(${PROJECT_NAME} glfw)

## Fetch ##
include(FetchContent)

FetchContent_Declare(
        glfw
        URL https://github.com/glfw/glfw/archive/refs/tags/3.4.tar.gz
)

FetchContent_MakeAvailable(glfw)