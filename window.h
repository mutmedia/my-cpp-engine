#ifndef WINDOW_H
#define WINDOW_H

#include <memory>
#include <functional>

struct SDL_Window;
union SDL_Event;
struct WindowImpl;

class Window {
  public:
    Window(const char* name, int w, int h);
    ~Window();
    void Render(std::function<void()> renderFunc);
    void HandleResize();
    //void AddLayer();
    void ProcessEvent(SDL_Event* event);

    static int FRAME;
    bool visible;
    int width, height;
  private:
    std::unique_ptr<WindowImpl> self;
};


#endif
