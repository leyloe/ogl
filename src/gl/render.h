#ifndef RENDER_H
#define RENDER_H

#define SHADER_VERTEX_COMPILATION_ERROR 0
#define SHADER_FRAGMENT_COMPILATION_ERROR -1
#define SHADER_PROGRAM_LINKING_ERROR -2

typedef struct Renderer Renderer;
typedef long long GLsizeiptr;
typedef int GLint;
typedef char GLchar;

Renderer *renderInit();
int renderCreate(Renderer *r, const float *vertices, GLsizeiptr size,
                 const char *vs_src, const char *fs_src);
const GLchar *renderShaderInfolog(Renderer *r);
void renderDraw(Renderer *r);
void renderDeinit(Renderer *r);

#endif
