#ifndef SHADERS_H
#define SHADERS_H

#define UV_ATTRIBUTE_LOCATION 1

static const char *vertex_shader_source = "#version 330 core\n"
                                          "layout (location = 0) in vec3 aPos;\n"
                                          "layout (location = 1) in vec2 aTexCoord;\n"
                                          "out vec2 textCoord;\n"
                                          "uniform mat4 model;\n"
                                          "uniform mat4 view;\n"
                                          "uniform mat4 proj;\n"
                                          "void main()\n"
                                          "{\n"
                                          "   gl_Position = proj * view * model * vec4(aPos, 1.0);\n"
                                          "   textCoord = aTexCoord;\n"
                                          "}";
static const char *fragment_shader_source = "#version 330 core\n"
                                            "in vec2 textCoord;\n"
                                            "uniform sampler2D texture0;\n"
                                            "out vec4 FragColor;\n"
                                            "void main()\n"
                                            "{\n"
                                            "   FragColor = texture(texture0, textCoord);\n"
                                            "}";

#endif
