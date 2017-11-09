#include "game.h"

#include "time.h"
#include "input.h"
#include "transform.h"
#include "camera.h"
#include "window.h"
#include "meshRenderer.h"

#include <SDL2/SDL.h>

static const Vertex vertex_data[] = {
  {{-1.0f, -1.0f, -1.0f,},	 {0.583f, 0.771f, 0.014f,}},
  {{-1.0f, -1.0f, +1.0f,},	 {0.609f, 0.115f, 0.436f,}},
  {{-1.0f, +1.0f, +1.0f,},	 {0.327f, 0.483f, 0.844f,}},
  {{+1.0f, +1.0f, -1.0f,},	 {0.822f, 0.569f, 0.201f,}},
  {{-1.0f, -1.0f, -1.0f,},	 {0.435f, 0.602f, 0.223f,}},
  {{-1.0f, +1.0f, -1.0f,},	 {0.310f, 0.747f, 0.185f,}},
  {{+1.0f, -1.0f, +1.0f,},	 {0.597f, 0.770f, 0.761f,}},
  {{-1.0f, -1.0f, -1.0f,},	 {0.559f, 0.436f, 0.730f,}},
  {{+1.0f, -1.0f, -1.0f,},	 {0.359f, 0.583f, 0.152f,}},
  {{+1.0f, +1.0f, -1.0f,},	 {0.483f, 0.596f, 0.789f,}},
  {{+1.0f, -1.0f, -1.0f,},	 {0.559f, 0.861f, 0.639f,}},
  {{-1.0f, -1.0f, -1.0f,},	 {0.195f, 0.548f, 0.859f,}},
  {{-1.0f, -1.0f, -1.0f,},	 {0.014f, 0.184f, 0.576f,}},
  {{-1.0f, +1.0f, +1.0f,},	 {0.771f, 0.328f, 0.970f,}},
  {{-1.0f, +1.0f, -1.0f,},	 {0.406f, 0.615f, 0.116f,}},
  {{+1.0f, -1.0f, +1.0f,},	 {0.676f, 0.977f, 0.133f,}},
  {{-1.0f, -1.0f, +1.0f,},	 {0.971f, 0.572f, 0.833f,}},
  {{-1.0f, -1.0f, -1.0f,},	 {0.140f, 0.616f, 0.489f,}},
  {{-1.0f, +1.0f, +1.0f,},	 {0.997f, 0.513f, 0.064f,}},
  {{-1.0f, -1.0f, +1.0f,},	 {0.945f, 0.719f, 0.592f,}},
  {{+1.0f, -1.0f, +1.0f,},	 {0.543f, 0.021f, 0.978f,}},
  {{+1.0f, +1.0f, +1.0f,},	 {0.279f, 0.317f, 0.505f,}},
  {{+1.0f, -1.0f, -1.0f,},	 {0.167f, 0.620f, 0.077f,}},
  {{+1.0f, +1.0f, -1.0f,},	 {0.347f, 0.857f, 0.137f,}},
  {{+1.0f, -1.0f, -1.0f,},	 {0.055f, 0.953f, 0.042f,}},
  {{+1.0f, +1.0f, +1.0f,},	 {0.714f, 0.505f, 0.345f,}},
  {{+1.0f, -1.0f, +1.0f,},	 {0.783f, 0.290f, 0.734f,}},
  {{+1.0f, +1.0f, +1.0f,},	 {0.722f, 0.645f, 0.174f,}},
  {{+1.0f, +1.0f, -1.0f,},	 {0.302f, 0.455f, 0.848f,}},
  {{-1.0f, +1.0f, -1.0f,},	 {0.225f, 0.587f, 0.040f,}},
  {{+1.0f, +1.0f, +1.0f,},	 {0.517f, 0.713f, 0.338f,}},
  {{-1.0f, +1.0f, -1.0f,},	 {0.053f, 0.959f, 0.120f,}},
  {{-1.0f, +1.0f, +1.0f,},	 {0.393f, 0.621f, 0.362f,}},
  {{+1.0f, +1.0f, +1.0f,},	 {0.673f, 0.211f, 0.457f,}},
  {{-1.0f, +1.0f, +1.0f,},	 {0.820f, 0.883f, 0.371f,}},
  {{+1.0f, -1.0f, +1.0f,},	 {0.982f, 0.099f, 0.879f}}
};
int vertices_size = 12 * 3;
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

void Game::Initialize() {
  // Camera stuff
  float aspectratio = (float)Window::Instance()->width / (float)Window::Instance()->height;
  printf("Aspect ratio: %f\n", aspectratio);
  camera = new Camera(
      45.0f,
      aspectratio,
      0.1f,
      100.0f);

  camera->transform_.position_ = glm::vec3(0, 0, 3);
  camera->transform_.rotation_ = glm::quat(glm::vec3(0, glm::pi<float>(), 0));

  main_camera_ = camera;
      
    InputHandler *playerInput = new InputHandler("Player Input", km, 9);

  cube = new Mesh(vertex_data, vertices_size);

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
