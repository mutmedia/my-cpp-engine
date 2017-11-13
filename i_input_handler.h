#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL.h>

class IInputHandler {
public:
  virtual void Update() = 0;
  virtual void ProcessEvent(const SDL_Event *e) = 0;
  virtual ~IInputHandler() {}
};

#endif