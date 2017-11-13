#include "game.h"

#include "camera.h"
#include "graphics.h"
#include "keyboard_input.h"
#include "mouse_input.h"
#include "time.h"
#include "transform.h"
#include "window.h"

// lib
#include "scheduler.h"

#include <SDL.h>

#include <vector>

float mouse_sensitivity = 2.0;

float linear_speed = 3.0f;

// Initialize events
SDL_KeyMapping keyboard_mapping[9] = {
    KEYBOARD_MAP(w, "up"),         KEYBOARD_MAP(s, "down"),
    KEYBOARD_MAP(a, "left"),       KEYBOARD_MAP(d, "right"),
    KEYBOARD_MAP(q, "cam-cw"),     KEYBOARD_MAP(e, "cam-ccw"),
    KEYBOARD_MAP(SPACE, "action"),
};

SDL_MouseKeyMapping mouse_mapping[2] = {
    MOUSE_MAP(LEFT, "fire"),
    MOUSE_MAP(RIGHT, "left"),
};

Camera *my_camera;
Scheduler *scheduler;

void Game::Update() { scheduler->Update(Time::GetDelta()); }

void Game::Draw() {
  Graphics::SetClearColor(glm::vec3(0.3, 0.5, 0.7));
}

int count = 0;
void Game::Load() {
  scheduler = new Scheduler();
  KeyboardInput *keyboardInput = new KeyboardInput(keyboard_mapping, 9);
  MouseInput *mouseInput = new MouseInput(mouse_mapping, 2);

  // Camera stuff
  my_camera =
      new Camera(45.0f, Window::Instance()->aspect_ratio(), 0.1f, 100.0f);

  my_camera->transform.position = glm::vec3(0, 1, 5);
  my_camera->transform.rotation = glm::quat(glm::vec3(0, glm::pi<float>(), 0));

  Graphics::camera = my_camera;

  keyboardInput->BindAction("up", INPUT_HOLD, [&]() {});
  keyboardInput->BindAction("down", INPUT_HOLD, [&]() {});
  keyboardInput->BindAction("left", INPUT_HOLD, [&]() {});
  keyboardInput->BindAction("right", INPUT_HOLD, [&]() {});

  mouseInput->BindAction("fire", INPUT_DOWN, [&]() {
    printf("%d Scheduled\n", count);
    scheduler->Add(2,
                   [&]() { printf("%d Scheduled event was fired!\n", count); });
    count++;
  });

  mouseInput->BindMovement([&](const MouseMovementData *mouse) {});
}
