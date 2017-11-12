#ifndef KEYBOARD_INPUT_H
#define KEYBOARD_INPUT_H

// TODO: allow key remapping
#include "events.h"
#include "i_input_handler.h"
#include "input_type.h"

#include "SDL.h"

struct SDL_KeyMapping {
  int key;
  const char *name;
};

class KeyboardInput : public IInputHandler {
public:
  KeyboardInput(SDL_KeyMapping *keymapping, const int mappingsize);
  void BindAction(const char *name, const InputType type,
                  const std::function<void()> callback);

  virtual void ProcessEvent(const SDL_Event *e);
  virtual void Update();

private:
  EventSystem input_events_;
  SDL_KeyMapping *key_mapping_;
  int mapping_size_;
};

#endif