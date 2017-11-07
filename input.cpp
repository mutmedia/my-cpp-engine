#include "input.h"

#include <string.h>

#include "SDL2/SDL.h"

const void InputHandler::ProcessEvent(const SDL_Event* e) {
  switch(e->type) {
    case SDL_KEYDOWN: 
      {
        int k = e->key.keysym.sym;
        input_events_.Fire(KeyTypeToEvent(k, INPUT_DOWN));
        break;
      }
    case SDL_KEYUP:
      {
        int k = e->key.keysym.sym;
        input_events_.Fire(KeyTypeToEvent(k, INPUT_UP));
        break;
      }
  }
}

const void InputHandler::Update() {
  const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
  // TODO: optimize for only keys that are bound to hold
  for (int i = 0; i < mapping_size_; i++) {
    int k = key_mapping_[i].key;
    if(keyboard[SDL_GetScancodeFromKey(k)]) {
        input_events_.Fire(KeyTypeToEvent(k, INPUT_HOLD));
    }
  }
}

void InputHandler::BindAction(const char * name, const InputType type, const std::function<void()> callback) {
  for (int i = 0; i < mapping_size_; i++) {
    if(strcmp(name, key_mapping_[i].name) == 0) {
      input_events_.Add(KeyTypeToEvent(key_mapping_[i].key, type), callback);
    }
  }
}

const int InputHandler::KeyTypeToEvent(const int key, const InputType type) {
  int a =  ((int)type << 8) | key;
  return a;
}
