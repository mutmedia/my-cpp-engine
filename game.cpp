#include "game.h"

#include "time.h"
#include "input.h"
#include "transform.h"
#include "camera.h"
#include "window.h"
#include "graphics.h"

#include <SDL.h>

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

Camera * my_camera;
float linear_speed = 3.0f;
float angular_speed = 1.0f;

glm::vec3 cube_position;
glm::vec3 cube_position_2;

void Game::Update() {
  cube_position.y = 5 * sin(Time::GetTotal() / 10);
  cube_position_2.x = 3;
  cube_position_2.y = 10 * sin(Time::GetTotal() + 2);
}


void Game::Draw() {
  Graphics::Cube(cube_position);
  Graphics::Cube(cube_position_2);
}

void Game::Load() {
  InputHandler *playerInput = new InputHandler("Player Input", km, 9);

  // Camera stuff
  my_camera = new Camera(
      45.0f,
      Window::Instance()->aspect_ratio(),
      0.1f,
      100.0f);

  my_camera->transform_.position_ = glm::vec3(0, 0, 5);
  my_camera->transform_.rotation_ = glm::quat(glm::vec3(0, glm::pi<float>(), 0));

  Graphics::camera = my_camera;

  playerInput->BindAction("up", INPUT_HOLD, [&]() {
    my_camera->transform_.position_ += my_camera->transform_.rotation_ * glm::vec3(0, 0, +1) * linear_speed * Time::GetDelta();
  });
  playerInput->BindAction("down", INPUT_HOLD, [&]() {
    my_camera->transform_.position_ += my_camera->transform_.rotation_ * glm::vec3(0, 0, -1) * linear_speed * Time::GetDelta();
  });
  playerInput->BindAction("left", INPUT_HOLD, [&]() {
    my_camera->transform_.position_ += my_camera->transform_.rotation_ * glm::vec3(+1, 0, 0) * linear_speed * Time::GetDelta();
  });
  playerInput->BindAction("right", INPUT_HOLD, [&]() {
    my_camera->transform_.position_ += my_camera->transform_.rotation_ * glm::vec3(-1, 0, 0) * linear_speed * Time::GetDelta();
  });
  playerInput->BindAction("yaw+", INPUT_HOLD, [&]() {
    my_camera->transform_.rotation_ *= glm::quat(glm::vec3(0, +1, 0) * angular_speed * Time::GetDelta());
  });
  playerInput->BindAction("yaw-", INPUT_HOLD, [&]() {
    my_camera->transform_.rotation_ *= glm::quat(glm::vec3(0, -1, 0) * angular_speed * Time::GetDelta());
  });
  playerInput->BindAction("pitch-", INPUT_HOLD, [&]() {
    my_camera->transform_.rotation_ *= glm::quat(glm::vec3(-1, 0, 0) * angular_speed * Time::GetDelta());
  });
  playerInput->BindAction("pitch+", INPUT_HOLD, [&]() {
    my_camera->transform_.rotation_ *= glm::quat(glm::vec3(+1, 0, 0) * angular_speed * Time::GetDelta());
  });


}
