#include "input_manager.h"

#include <algorithm>
#include <string.h>

#include <SDL.h>

namespace {
std::vector<IInputHandler *> handlers;
// TODO: might be a good idea to clear/free things allocated here
} // namespace

void InputManager::RegisterInputHandler(IInputHandler *handler) {
  handlers.push_back(handler);
}

void InputManager::Update() {
  int i = 0;
  std::for_each(handlers.begin(), handlers.end(),
                [&](IInputHandler *inputhandler) { inputhandler->Update(); });
}

void InputManager::ProcessEvent(const SDL_Event *e) {
  std::for_each(
      handlers.begin(), handlers.end(),
      [&](IInputHandler *inputhandler) { inputhandler->ProcessEvent(e); });
}
