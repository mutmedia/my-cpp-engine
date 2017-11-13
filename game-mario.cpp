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
glm::vec3 arm_direction = glm::vec3(0, 1, 2);
float arm_length = 10;

struct Character {
  glm::vec3 position;
  glm::vec3 direction;
  glm::vec3 scale = glm::vec3(1.0);
  glm::quat rotation;
  const float speed = 1.0;

  bool isJumping;
  bool isGrounded;
};

Character player;

void DrawCharacter(const Character &c) {
  auto translation = glm::vec3(0.0, 1.0, 0.0);
  // Corpo
  Graphics::SetMaterial(glm::vec3(218, 41, 28) * 1.0f / 255.0f);
  Graphics::Cube(c.position + translation, c.rotation, c.scale);

  // Cabeca
  translation += glm::vec3(0.0, 1.0, 0.0);
  Graphics::SetMaterial(glm::vec3(245, 215, 165) * 1.0f / 255.0f);
  Graphics::Cube(c.position + translation, c.rotation, c.scale);

  // Chapeu
  Graphics::SetMaterial(glm::vec3(218, 41, 28) * 1.0f / 255.0f);
  translation += glm::vec3(0.0, 1.0, 0.3);
  Graphics::Cube(c.position + translation, c.rotation,
                 c.scale * glm::vec3(1.1, 0.1, 1.5));
}

void Game::Update() {
  scheduler->Update(Time::GetDelta());

  my_camera->transform.position =
      player.position + glm::normalize(arm_direction) * arm_length;
  auto look_dir = player.position - my_camera->transform.position;
  my_camera->transform.rotation =
      glm::quatLookAt(look_dir, glm::vec3(0.0, 1.0, 0.0));
}

void Game::Draw() {
  Graphics::SetAmbientLight(glm::vec3(0.1));
  Graphics::SetClearColor(glm::vec3(0.3, 0.5, 0.7));
  Graphics::PointLight(glm::vec3(0.0, 3.0, 2.0), glm::vec3(1.0), 10.0);
  DrawCharacter(player);

  Graphics::SetAmbientLight(glm::vec3(1.0));
  for (int i = -50; i <= 50; i+=10) {
    for (int j = -50; j <= 50; j+=10) {
      for (int k = -50; k <= 50; k+=10) {
      Graphics::SetMaterial(glm::vec3((float)(i+50)/100.0, (float)(j+50)/100.0, (float)(k+50)/100.0));
      Graphics::Cube(glm::vec3(i, j, k), glm::quat(), glm::vec3(0.1));
      }
    }
  }
}

int count = 0;

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
    my_camera->transform.rotation *=
        glm::quat(Time::GetDelta() * glm::vec3(1.0, 0.0, 0.0));
        player.position += glm::vec3(0, 0, +1) * Time::GetDelta() * player.speed;
  });
  keyboardInput->BindAction("down", INPUT_HOLD, [&]() {
    my_camera->transform.rotation *=
        glm::quat(Time::GetDelta() * glm::vec3(-1.0, 0.0, 0.0));
        player.position += glm::vec3(0, 0, -1) * Time::GetDelta() * player.speed;
  });
  keyboardInput->BindAction("left", INPUT_HOLD, [&]() {
    my_camera->transform.rotation *=
        glm::quat(Time::GetDelta() * glm::vec3(0.0, 0.0, 1.0));
        player.position += glm::vec3(+1, 0, 1) * Time::GetDelta() * player.speed;
  });
  keyboardInput->BindAction("right", INPUT_HOLD, [&]() {
    my_camera->transform.rotation *=
        glm::quat(Time::GetDelta() * glm::vec3(0.0, 0.0, -1.0));
        player.position += glm::vec3(-1, 0, 0) * Time::GetDelta() * player.speed;
  });
  keyboardInput->BindAction("cam-cw", INPUT_HOLD, [&]() {
    my_camera->transform.rotation *=
        glm::quat(Time::GetDelta() * glm::vec3(0.0, 1.0, 0.0));
  });
  keyboardInput->BindAction("cam-ccw", INPUT_HOLD, [&]() {
    my_camera->transform.rotation *=
        glm::quat(Time::GetDelta() * glm::vec3(0.0, -1.0, 0.0));
  });

  mouseInput->BindAction("fire", INPUT_DOWN, [&]() {
    printf("%d Scheduled\n", count);
    scheduler->Add(2,
                   [&]() { printf("%d Scheduled event was fired!\n", count); });
    count++;
  });

  mouseInput->BindMovement([&](const MouseMovementData *mouse) {});
}
