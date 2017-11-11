#include "game.h"

#include "camera.h"
#include "graphics.h"
#include "input.h"
#include "time.h"
#include "transform.h"
#include "window.h"

#include <SDL.h>

// Initialize events
SDL_KeyMapping km[9] = {
    {SDLK_w, "up"},      {SDLK_s, "down"},      {SDLK_a, "left"},
    {SDLK_d, "right"},   {SDLK_RIGHT, "yaw-"},  {SDLK_LEFT, "yaw+"},
    {SDLK_UP, "pitch-"}, {SDLK_DOWN, "pitch+"}, {SDLK_SPACE, "action"},
};

Camera *my_camera;
float linear_speed = 3.0f;
float angular_speed = 1.0f;

glm::vec3 cube_position;
glm::vec3 cube_position2;

void Game::Update() {
  cube_position.y = 5 * sin(Time::GetTotal() / 10);
  cube_position2.x = 4 + 2 * cos(3 * Time::GetTotal() + 2);
  cube_position2.y = 2 * sin(3 * Time::GetTotal() + 2);
}

void LightRepresentation (vec3 position) {
  Graphics::SetMaterial(glm::vec3(1.0));
  Graphics::Cube(position, quat(), glm::vec3(0.1));
}

void Game::Draw() {
  LightRepresentation(glm::vec3(3, 3, 0));
  LightRepresentation(glm::vec3(3, -3, 0));

  Graphics::PointLight(glm::vec3(3, 3, 0), glm::vec3(1, 1, 1), 5);

  Graphics::SetMaterial(glm::vec3(0.5, 0.0, 0.7), glm::vec3(1.0, 0.9, 0.9));
  Graphics::Cube(cube_position);

  Graphics::SetMaterial(glm::vec3(0.1, 0.7, 0.2), glm::vec3(0.9, 1.0, 0.7));
  Graphics::Cube(cube_position2);

  Graphics::PointLight(glm::vec3(3, -3, 0), glm::vec3(1, 1, 1), 100);
  Graphics::SetMaterial(glm::vec3(0.0, 0.0, 0.9), glm::vec3(0.9, 1.0, 0.7));
  Graphics::Cube(glm::vec3(8, 0, 0), quat(glm::vec3(Time::GetTotal(), 0, 0)),
                 glm::vec3(0.05, 100, 1.0));
}

void Game::Load() {
  InputHandler *playerInput = new InputHandler("Player Input", km, 9);

  // Camera stuff
  my_camera =
      new Camera(45.0f, Window::Instance()->aspect_ratio(), 0.1f, 100.0f);

  my_camera->transform.position = glm::vec3(0, 0, 5);
  my_camera->transform.rotation = glm::quat(glm::vec3(0, glm::pi<float>(), 0));

  Graphics::camera = my_camera;

  playerInput->BindAction("up", INPUT_HOLD, [&]() {
    my_camera->transform.position += my_camera->transform.rotation *
                                     glm::vec3(0, 0, +1) * linear_speed *
                                     Time::GetDelta();
  });
  playerInput->BindAction("down", INPUT_HOLD, [&]() {
    my_camera->transform.position += my_camera->transform.rotation *
                                     glm::vec3(0, 0, -1) * linear_speed *
                                     Time::GetDelta();
  });
  playerInput->BindAction("left", INPUT_HOLD, [&]() {
    my_camera->transform.position += my_camera->transform.rotation *
                                     glm::vec3(+1, 0, 0) * linear_speed *
                                     Time::GetDelta();
  });
  playerInput->BindAction("right", INPUT_HOLD, [&]() {
    my_camera->transform.position += my_camera->transform.rotation *
                                     glm::vec3(-1, 0, 0) * linear_speed *
                                     Time::GetDelta();
  });
  playerInput->BindAction("yaw+", INPUT_HOLD, [&]() {
    my_camera->transform.rotation *=
        glm::quat(glm::vec3(0, +1, 0) * angular_speed * Time::GetDelta());
  });
  playerInput->BindAction("yaw-", INPUT_HOLD, [&]() {
    my_camera->transform.rotation *=
        glm::quat(glm::vec3(0, -1, 0) * angular_speed * Time::GetDelta());
  });
  playerInput->BindAction("pitch-", INPUT_HOLD, [&]() {
    my_camera->transform.rotation *=
        glm::quat(glm::vec3(-1, 0, 0) * angular_speed * Time::GetDelta());
  });
  playerInput->BindAction("pitch+", INPUT_HOLD, [&]() {
    my_camera->transform.rotation *=
        glm::quat(glm::vec3(+1, 0, 0) * angular_speed * Time::GetDelta());
  });
}
