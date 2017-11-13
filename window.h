#ifndef WINDOW_H
#define WINDOW_H

#include <functional>
#include <memory>

struct SDL_Window;
union SDL_Event;
struct WindowImpl;

class Window {
public:
  ~Window();

  static Window *Instance();
  static void Initialize(const char *name, int w, int h);

  void Render(std::function<void()> renderFunc);
  void HandleResize();
  // void AddLayer();
  void ProcessEvent(SDL_Event *event);

  float aspect_ratio() const;

  static int FRAME;
  bool visible;
  int width, height;

private:
  std::unique_ptr<WindowImpl> self;
  Window(const char *name, int w, int h);
};

#endif
