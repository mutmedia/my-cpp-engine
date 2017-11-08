#ifndef INPUT_H
#define INPUT_H

#include <vector>

#include "events.h"
union SDL_Event;

struct SDL_KeyMapping {
  int key;
  const char * name;
};

enum InputType {
  INPUT_NONE = 0,
  INPUT_DOWN = 1,
  INPUT_UP = 2,
  INPUT_HOLD = 3,
};

class InputHandler {
  public:
    InputHandler(const char * name, SDL_KeyMapping *keymapping, const int mappingsize);
    void BindAction(const char * name, const InputType type, const std::function<void()> callback);
    const void ProcessEvent(const SDL_Event* e);
    const void Update();
    // TODO: allow key remapping
  private: 
    const int KeyTypeToEvent(const int key, const InputType type);  
    EventSystem input_events_;
    SDL_KeyMapping * key_mapping_;
    int mapping_size_;
    const char * name_;
};

namespace Input {
  static void RegisterInputHandler(InputHandler * handler);
  void Update();
  void ProcessEvent(const SDL_Event * e);

  static std::vector<InputHandler *> handlers;
  // TODO: might be a good idea to clear/free things allocated here
}

#endif
