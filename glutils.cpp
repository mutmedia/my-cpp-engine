#include "glutils.h"
#include "common.h"

#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif

void GLERRORS(const char *label) {
  //#ifndef __EMSCRIPTEN__
  while (true) {
    GLenum err = glGetError();
    if (err == GL_NO_ERROR) {
      break;
    }
    fprintf(stderr, "%s glGetError returned %d \n", label, err);
  }
  //#endif
}

void FAIL(const char *label) {
  GLERRORS(label);
  fprintf(stderr, "%s failed : %s \n", label, SDL_GetError());
  exit(EXIT_FAILURE);
}

VertexBuffer::VertexBuffer() { glGenBuffers(1, &id); }

VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &id); }

GlContext::GlContext(SDL_Window *window) {
  id = SDL_GL_CreateContext(window);
  if (id == nullptr) {
    FAIL("SDL_GL_CreateContext");
  }
}

GlContext::~GlContext() { SDL_GL_DeleteContext(id); }
