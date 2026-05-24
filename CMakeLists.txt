cmake_minimum_required(VERSION 3.29)
project(ogl C)

if(NOT CMAKE_C_COMPILER_ID MATCHES "Clang")
    message(FATAL_ERROR "Clang required, got: ${CMAKE_C_COMPILER_ID}")
endif()

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*.c")
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE src src/gl)
target_compile_options(${PROJECT_NAME} PRIVATE -Weverything -Wno-pre-c23-compat -Wno-c++98-compat)
set_source_files_properties(src/gl/glad.c src/gl/stb_image.c PROPERTIES COMPILE_OPTIONS "-w;-fno-sanitize=all")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(SANITIZERS address,undefined,integer,nullability,implicit-conversion,local-bounds)
    target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=${SANITIZERS} -fno-omit-frame-pointer -fno-sanitize-recover=all)
    target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=${SANITIZERS})
endif()

include(FetchContent)
FetchContent_Declare(glfw URL https://github.com/glfw/glfw/archive/refs/tags/3.4.tar.gz)
FetchContent_MakeAvailable(glfw)
set_target_properties(glfw PROPERTIES SYSTEM TRUE)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)
