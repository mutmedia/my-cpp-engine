#include "window.h"

#include <SDL2/SDL.h>
#include "glutils.h"

#include <vector>

struct WindowImpl {
  SDL_Window* window;
  bool context_initialized;
  GlContext context;

  WindowImpl(SDL_Window* window_);
  ~WindowImpl();
};

WindowImpl::WindowImpl(SDL_Window* window_)
  :window(window_), context_initialized(false), context(window)
{
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  glClearColor(0.0, 0.0, 0.0, 1.0);
}

WindowImpl::~WindowImpl() {
  SDL_DestroyWindow(window);
}

int Window::FRAME = 0;

Window::Window(const char* name, int w, int h) 
  :visible(true), width(w), height(h),
  self(new WindowImpl(SDL_CreateWindow(name,
          SDL_WINDOWPOS_CENTERED,
          SDL_WINDOWPOS_CENTERED,
          width, height,
          SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
          )))
{
  HandleResize();
}

Window::~Window() {
  free(window_instance);
}

void Window::HandleResize() {
  self->context_initialized = false;
  SDL_GL_GetDrawableSize(self->window, &width, &height);
  glViewport(0, 0, width, height);
}

void Window::Initialize(const char* name, int w, int h) {
  window_instance = new Window(name, w, h);
}


Window * Window::Instance() {
  if(window_instance == NULL) {
    printf("ERROR: window not initialized");
  }
  return window_instance;
}

void Window::Render(std::function<void()> renderFunc) {
  if(visible) {
    glClear(GL_COLOR_BUFFER_BIT); //TODO: add depth buffer
    renderFunc();
    self->context_initialized = true;
    SDL_GL_SwapWindow(self->window);
    FRAME++;
  }
}

void Window::ProcessEvent(SDL_Event* event) {
  if(event->type == SDL_WINDOWEVENT)
  {
    switch (event->window.event)
    {
      case SDL_WINDOWEVENT_SHOWN: 
        {
          visible = true;
          break;
        }
      case SDL_WINDOWEVENT_HIDDEN:
        {
          visible = false;
          break;
        }
      case SDL_WINDOWEVENT_SIZE_CHANGED: 
        {
          HandleResize();
          break;
        }
    }
  }
}

