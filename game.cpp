#include "game.h"

#include "time.h"
#include "input.h"
#include "transform.h"
#include "camera.h"
#include "window.h"
#include "meshRenderer.h"

#include <SDL.h>

Mesh * cube;



// Initialize events
SDL_KeyMapping km[9] = {
    {SDLK_w, "up"},
    {SDLK_s, "down"},
    {SDLK_a, "left"},
    {SDLK_d, "right"},
    {SDLK_RIGHT, "yaw-"},
    {SDLK_LEFT, "yaw+"},
    {SDLK_UP, "pitch-"},
    {SDLK_DOWN, "pitch+"},
    {SDLK_SPACE, "action"},
};

Camera * camera;
float linear_speed = 3.0f;
float angular_speed = 1.0f;

void Game::Update() {
  auto pos = main_camera_->transform_.position_;
}

void Game::Load() {
  InputHandler *playerInput = new InputHandler("Player Input", km, 9);
  cube = new Mesh(vertex_data, vertices_size);

  // Camera stuff
  camera = new Camera(
      45.0f,
      Window::Instance()->aspect_ratio,
      0.1f,
      100.0f);

  camera->transform_.position_ = glm::vec3(0, 0, 3);
  camera->transform_.rotation_ = glm::quat(glm::vec3(0, glm::pi<float>(), 0));

  main_camera_ = camera;

  playerInput->BindAction("action", INPUT_HOLD, [&]() {
    auto rend = new MeshRenderer(cube);
    rend->transform_.position_ = camera->transform_.position_;
  });

  playerInput->BindAction("up", INPUT_HOLD, [&]() {
    camera->transform_.position_ += camera->transform_.rotation_ * glm::vec3(0, 0, +1) * linear_speed * Time::DeltaTime();
  });
  playerInput->BindAction("down", INPUT_HOLD, [&]() {
    camera->transform_.position_ += camera->transform_.rotation_ * glm::vec3(0, 0, -1) * linear_speed * Time::DeltaTime();
  });
  playerInput->BindAction("left", INPUT_HOLD, [&]() {
    camera->transform_.position_ += camera->transform_.rotation_ * glm::vec3(+1, 0, 0) * linear_speed * Time::DeltaTime();
  });
  playerInput->BindAction("right", INPUT_HOLD, [&]() {
    camera->transform_.position_ += camera->transform_.rotation_ * glm::vec3(-1, 0, 0) * linear_speed * Time::DeltaTime();
  });
  playerInput->BindAction("yaw+", INPUT_HOLD, [&]() {
    camera->transform_.rotation_ *= glm::quat(glm::vec3(0, +1, 0) * angular_speed * Time::DeltaTime());
  });
  playerInput->BindAction("yaw-", INPUT_HOLD, [&]() {
    camera->transform_.rotation_ *= glm::quat(glm::vec3(0, -1, 0) * angular_speed * Time::DeltaTime());
  });
  playerInput->BindAction("pitch-", INPUT_HOLD, [&]() {
    camera->transform_.rotation_ *= glm::quat(glm::vec3(-1, 0, 0) * angular_speed * Time::DeltaTime());
  });
  playerInput->BindAction("pitch+", INPUT_HOLD, [&]() {
    camera->transform_.rotation_ *= glm::quat(glm::vec3(+1, 0, 0) * angular_speed * Time::DeltaTime());
  });


}
