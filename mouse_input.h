#ifndef MOUSE_INPUT_H
#define MOUSE_INPUT_H

#include "events.h"
#include "i_input_handler.h"
#include "input_type.h"

#include "SDL.h"

struct SDL_MouseKeyMapping {
  int key;
  const char *name;
};

struct MouseMovementData {
  int x;
  int y;
  int dx;
  int dy;
};

class MouseInput : public IInputHandler {
public:
  MouseInput(SDL_MouseKeyMapping *keymapping, const int mappingsize);

  void BindAction(const char *name, const InputType type,
                  const std::function<void()> callback);

  void BindMovement(const std::function<void(const MouseMovementData * d)> callback);

  virtual void ProcessEvent(const SDL_Event *e);
  virtual void Update();

private:
  EventSystem input_events_;
  SDL_MouseKeyMapping *key_mapping_;
  MouseMovementData mouse_data_;
  int mapping_size_;
};

#endif
