#ifndef INPUT_H
#define INPUT_H

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
    InputHandler(SDL_KeyMapping *keymapping, const int mappingsize) : key_mapping_(keymapping), mapping_size_(mappingsize) { };
    const void ProcessEvent(const SDL_Event* e);
    const void Update();
    void BindAction(const char * name, const InputType type, const std::function<void()> callback);
    // TODO: allow key remapping
  private: 
    const int KeyTypeToEvent(const int key, const InputType type);  
    EventSystem input_events_;
    SDL_KeyMapping * key_mapping_;
    int mapping_size_;
};

#endif
