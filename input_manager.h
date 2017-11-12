#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "events.h"
#include "i_input_handler.h"

union SDL_Event;

namespace InputManager {
void Update();
void ProcessEvent(const SDL_Event *e);
void RegisterInputHandler(IInputHandler *handler);
} // namespace InputManager

#endif
