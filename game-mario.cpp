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
float arm_length = 20;

struct Character {
  Transform transform;

  glm::vec3 direction;
  const float speed = 5.0;

  bool isJumping;
  bool isGrounded;
};

Character player;

void DrawCharacter(const Character &c) {
  auto translation = glm::vec3(0.0, 1.0, 0.0);
  // Corpo
  Graphics::SetMaterial(glm::vec3(218, 41, 28) * 1.0f / 255.0f);
  Graphics::Cube(c.transform.position + translation, c.transform.rotation,
                 c.transform.scale);

  // Cabeca
  translation += glm::vec3(0.0, 1.0, 0.0);
  Graphics::SetMaterial(glm::vec3(245, 215, 165) * 1.0f / 255.0f);
  Graphics::Cube(c.transform.position + translation, c.transform.rotation,
                 c.transform.scale * glm::vec3(0.95, 1.0, 0.95));

  // Chapeu
  Graphics::SetMaterial(glm::vec3(218, 41, 28) * 1.0f / 255.0f);
  translation += glm::vec3(0.0, 1.0, 0.3);
  Graphics::Cube(c.transform.position + translation, c.transform.rotation,
                 c.transform.scale * glm::vec3(1.1, 0.1, 1.5));
  translation += glm::vec3(0.0, 0.2, 0.1);
  Graphics::Cube(c.transform.position + translation, c.transform.rotation,
                 c.transform.scale * glm::vec3(0.7, 0.2, 0.7));
}

void Game::Update() {
  scheduler->Update(Time::GetDelta());

  my_camera->transform.position =
      player.transform.position + glm::normalize(arm_direction) * arm_length;
  my_camera->transform.rotation =
      glm::quatLookAt(-arm_direction, glm::vec3(0.0, 1.0, 0.0));
}

void Game::Draw() {
  Graphics::SetAmbientLight(glm::vec3(0.7));
  Graphics::SetClearColor(glm::vec3(0.3, 0.5, 0.7));
  // Graphics::PointLight(glm::vec3(0.0, 3.0, 2.0), glm::vec3(1.0), 10.0);
  DrawCharacter(player);

  Graphics::SetMaterial(glm::vec3(0.0, 0.0, 0.5));
  for (int x = -10; x <= 10; x++) {
    for (int z = -10; z <= 10; z++) {
      Graphics::SetMaterial(glm::vec3((x + z) % 2 == 0 ? 0.0 : 1.0));
      Graphics::Cube(glm::vec3(2*x, -1, 2*z));
    }
  }
}

void Game::Load() {
  glm::vec3 v1 = glm::vec3(0.0, 0.0, 1.0);
  glm::vec3 v2 = glm::vec3(0.0, -1.0, -1.0);
  auto rot = glm::rotationBetween(v1, v2);
  printf("x: %f, y: %f, z: %f, w: %f\n", rot.x, rot.y, rot.z, rot.w);

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
    player.transform.position += player.transform.forward() * Time::GetDelta() * player.speed;
  });
  keyboardInput->BindAction("down", INPUT_HOLD, [&]() {
    player.transform.position -= player.transform.forward() * Time::GetDelta() * player.speed;
  });
  keyboardInput->BindAction("left", INPUT_HOLD, [&]() {
    player.transform.position -= player.transform.right() * Time::GetDelta() * player.speed;
  });
  keyboardInput->BindAction("right", INPUT_HOLD, [&]() {
    player.transform.position += player.transform.right() * Time::GetDelta() * player.speed;
  });

  keyboardInput->BindAction("cam-cw", INPUT_HOLD, [&]() {
    arm_direction =
        glm::rotate(glm::angleAxis(+Time::GetDelta(), glm::y()), arm_direction);
  });
  keyboardInput->BindAction("cam-ccw", INPUT_HOLD, [&]() {
    arm_direction =
        glm::rotate(glm::angleAxis(-Time::GetDelta(), glm::y()), arm_direction);
  });

  mouseInput->BindMovement([&](const MouseMovementData *mouse) {});
}
