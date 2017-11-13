#ifndef GLUTILS_H
#define GLUTILS_H

#include <SDL.h>
#include <SDL_opengles2.h>

#include "common.h"

void GLERRORS(const char *label);

struct VertexBuffer : nocopy {
  GLuint id;
  VertexBuffer();
  ~VertexBuffer();
};

struct GlContext : nocopy {
  SDL_GLContext id;
  GlContext(SDL_Window *window);
  ~GlContext();
};

#endif
