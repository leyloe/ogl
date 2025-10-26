#ifndef RENDER_H
#define RENDER_H

typedef struct Renderer Renderer;
typedef long long GLsizeiptr;
typedef int GLint;
typedef char GLchar;

Renderer *renderInit();
GLint renderCreate(Renderer *r, const float *vertices, GLsizeiptr size,
                   const char *vs_src, const char *fs_src);
const GLchar *renderShaderInfolog(Renderer *r);
void renderDraw(Renderer *r);
void renderDeinit(Renderer *r);

#endif
