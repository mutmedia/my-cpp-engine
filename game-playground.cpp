#include "game.h"

#include "camera.h"
#include "graphics.h"
#include "keyboard_input.h"
#include "mouse_input.h"
#include "time.h"
#include "transform.h"
#include "window.h"

// lib
#include "glm_extensions.h"
#include "scheduler.h"

#include <SDL.h>

#include <vector>

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

// Constants
Camera *my_camera;
Scheduler *scheduler;
glm::vec3 arm_direction = glm::vec3(0, 1, -1);
float arm_length = 30;

void Game::Update() {
  scheduler->Update(Time::GetDelta());

  my_camera->transform.position =
      player.position + glm::normalize(arm_direction) * arm_length;
  if (cam_control) return;
  my_camera->transform.rotation = 
      glm::quatLookAt(-arm_direction, glm::vec3(0.0, 1.0, 0.0));
}

void Game::Draw() {
  Graphics::SetAmbientLight(glm::vec3(0.1));
  Graphics::SetClearColor(glm::vec3(0.3, 0.5, 0.7));
  // Graphics::PointLight(glm::vec3(0.0, 3.0, 2.0), glm::vec3(1.0), 10.0);
  Graphics::Cube(glm::vec3(2.0, 1.0, 0.0));
  for (int i = -10; i <= 10; i += 5) {
    for (int j = -10; j <= 10; j += 5) {
      for (int k = -10; k <= 10; k += 5) {
        Graphics::SetMaterial(glm::vec3((float)(i + 10) / 100.0,
                                        (float)(j + 10) / 100.0,
                                        (float)(k + 10) / 100.0));
        Graphics::Cube(glm::vec3(i, j, k), glm::quat(), glm::vec3(0.1));
      }
    }
  }
}

void Game::Load() {
  scheduler = new Scheduler();
  KeyboardInput *keyboardInput = new KeyboardInput(keyboard_mapping, 9);
  MouseInput *mouseInput = new MouseInput(mouse_mapping, 2);

  // Camera stuff
  my_camera =
      new Camera(45.0f, Window::Instance()->aspect_ratio(), 0.1f, 100.0f);

  my_camera->transform.rotation =
      glm::quat(glm::vec3(0.0, glm::pi<float>(), 0.0));

  Graphics::camera = my_camera;

  keyboardInput->BindAction("up", INPUT_HOLD, [&]() {
        glm::quat(Time::GetDelta() * glm::vec3(1.0, 0.0, 0.0));
  });
  keyboardInput->BindAction("down", INPUT_HOLD, [&]() {
    my_camera->transform.rotation *=
        glm::quat(Time::GetDelta() * glm::vec3(-1.0, 0.0, 0.0));
  });
  keyboardInput->BindAction("left", INPUT_HOLD, [&]() {
    arm_direction += glm::vec3(0.0, 0.1, 0.0);
  });
  keyboardInput->BindAction("right", INPUT_HOLD, [&]() {
    arm_direction -= glm::vec3(0.0, 0.1, 0.0);
  });
  keyboardInput->BindAction("cam-cw", INPUT_HOLD, [&]() {
    my_camera->transform.rotation *=
        glm::quat(Time::GetDelta() * glm::vec3(0.0, 1.0, 0.0));
  });
  keyboardInput->BindAction("cam-ccw", INPUT_HOLD, [&]() {
    my_camera->transform.rotation *=
        glm::quat(Time::GetDelta() * glm::vec3(0.0, -1.0, 0.0));
  });

  mouseInput->BindMovement([&](const MouseMovementData *mouse) {});
}
