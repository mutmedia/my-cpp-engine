#ifndef GLUTILS_H
#define GLUTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengles2.h>

#include "common.h"

void GLERRORS(const char* label);

struct ShaderProgram : nocopy {
  GLuint id;
  ShaderProgram(const char* vert, const char* frag);
  ~ShaderProgram();
};

struct VertexBuffer : nocopy {
  GLuint id;
  VertexBuffer();
  ~VertexBuffer();
};

struct GlContext : nocopy {
  SDL_GLContext id;
  GlContext(SDL_Window* window);
  ~GlContext();
};

#endif
