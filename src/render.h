#ifndef RENDER_H
#define RENDER_H

typedef struct Renderer Renderer;
typedef long long GLsizeiptr;

Renderer *renderInit(const float *vertices, GLsizeiptr size,
                     const char *vs_src, const char *fs_src);
void renderDraw(Renderer *r);
void renderDeinit(Renderer *r);

#endif
