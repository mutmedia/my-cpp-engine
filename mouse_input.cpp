#include "mouse_input.h"

#include <algorithm>
#include <string.h>

#include "input_manager.h"

#define MOUSE_MOVEMENT_EVENT 2 << 5

namespace {
int KeyTypeToEvent(const int key, const InputType type) {
  int a = ((int)type << 8) | key;
  return a;
}
} // namespace

MouseInput::MouseInput(SDL_MouseKeyMapping *keymapping, const int mappingsize)
    : key_mapping_(keymapping), mapping_size_(mappingsize) {
  InputManager::RegisterInputHandler(this);
}

void MouseInput::ProcessEvent(const SDL_Event *e) {
  switch (e->type) {
  case SDL_MOUSEBUTTONDOWN: {
    int k = e->button.button;
    input_events_.Fire(KeyTypeToEvent(k, INPUT_DOWN));
    break;
  }
  case SDL_MOUSEBUTTONUP: {
    int k = e->button.button;
    input_events_.Fire(KeyTypeToEvent(k, INPUT_UP));
    break;
  }
  case SDL_MOUSEMOTION: {
    mouse_data_.x = e->motion.x;
    mouse_data_.y = e->motion.y;
    mouse_data_.dx = e->motion.xrel;
    mouse_data_.dy = e->motion.yrel;

    input_events_.Fire(MOUSE_MOVEMENT_EVENT);
    break;
  }
  }
}

void MouseInput::Update() {
  const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
  // TODO: optimize for only keys that are bound to hold
  for (int i = 0; i < mapping_size_; i++) {
    int k = key_mapping_[i].key;
    if (keyboard[SDL_GetScancodeFromKey(k)]) {
      input_events_.Fire(KeyTypeToEvent(k, INPUT_HOLD));
    }
  }
}

void MouseInput::BindAction(const char *name, const InputType type,
                            const std::function<void()> callback) {
  for (int i = 0; i < mapping_size_; i++) {
    if (strcmp(name, key_mapping_[i].name) == 0) {
      input_events_.Add(KeyTypeToEvent(key_mapping_[i].key, type), callback);
    }
  }
}

void MouseInput::BindMovement(
    const std::function<void(const MouseMovementData *d)> callback) {
  auto bound_callback = std::bind(callback, &mouse_data_);
  input_events_.Add(MOUSE_MOVEMENT_EVENT, bound_callback);
}
