#include "game.h"

#include "camera.h"
#include "graphics.h"
#include "keyboard_input.h"
#include "mouse_input.h"
#include "time.h"
#include "transform.h"
#include "window.h"

#include <SDL.h>

#include <vector>

float mouse_sensitivity = 2.0;

struct Bullet : Transform {
  glm::vec3 velocity;
  bool alive = true;
};

int MAX_BULLETS = 100;
int current_bullet_index = 0;
Bullet *bullets;

// Constants
float bullet_speed = 50.0;
float bullet_size = 0.035;
float linear_speed = 3.0f;
float angular_speed = 1.0f;

glm::vec3 gun_scale = glm::vec3(0.04, 0.08, 0.8);
glm::vec3 gun_pos = glm::vec3(0.0, -0.2, 0.5);

// Initialize events
SDL_KeyMapping keyboard_mapping[9] = {
    KEYBOARD_MAP(w, "up"),         KEYBOARD_MAP(s, "down"),
    KEYBOARD_MAP(a, "left"),       KEYBOARD_MAP(d, "right"),
    KEYBOARD_MAP(RIGHT, "yaw-"),   KEYBOARD_MAP(LEFT, "yaw+"),
    KEYBOARD_MAP(UP, "pitch-"),    KEYBOARD_MAP(DOWN, "pitch+"),
    KEYBOARD_MAP(SPACE, "action"),
};

SDL_MouseKeyMapping mouse_mapping[2] = {
    MOUSE_MAP(LEFT, "fire"),
    MOUSE_MAP(RIGHT, "left"),
};

Camera *my_camera;

glm::vec3 cube_position;
glm::vec3 cube_position2;

void Game::Update() {
  cube_position.y = 5 * sin(Time::GetTotal() / 10);
  cube_position2.x = 4 + 2 * cos(3 * Time::GetTotal() + 2);
  cube_position2.y = 2 * sin(3 * Time::GetTotal() + 2);

  for (int i = 0; i < MAX_BULLETS; i++) {
    if (!bullets[i].alive)
      continue;
    bullets[i].position += Time::GetDelta() * bullets[i].velocity;
  }
}

void LightRepresentation(glm::vec3 position) {
  Graphics::SetMaterial(glm::vec3(1.0));
  Graphics::Cube(position, glm::quat(), glm::vec3(0.1));
}

void DrawBullet(glm::vec3 position, glm::quat rotation) {
  Graphics::SetMaterial(glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0));
  Graphics::Cube(position, glm::quat(), glm::vec3(bullet_size));
}

void Game::Draw() {
  LightRepresentation(glm::vec3(3, 3, 0));
  LightRepresentation(glm::vec3(3, -3, 0));

  Graphics::SetMaterial(glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5));
  Graphics::Cube(glm::vec3(0, -1, 0), glm::quat(), glm::vec3(100, 0.1, 100));

  Graphics::PointLight(glm::vec3(3, 3, 0), glm::vec3(1, 1, 1), 5);

  Graphics::SetMaterial(glm::vec3(0.5, 0.0, 0.7), glm::vec3(1.0, 0.9, 0.9));
  Graphics::Cube(cube_position);

  Graphics::SetMaterial(glm::vec3(0.1, 0.7, 0.2), glm::vec3(0.9, 1.0, 0.7));
  Graphics::Cube(cube_position2);

  Graphics::PointLight(glm::vec3(3, -3, 0), glm::vec3(1, 1, 1), 100);
  Graphics::SetMaterial(glm::vec3(0.0, 0.0, 0.9), glm::vec3(0.9, 1.0, 0.7));
  Graphics::Cube(glm::vec3(8, 0, 0),
                 glm::quat(glm::vec3(Time::GetTotal(), 0, 0)),
                 glm::vec3(0.05, 100, 1.0));

  Graphics::SetMaterial(glm::vec3(0.5, 0.5, 0.3), glm::vec3(0.1, 0.1, 0.1));
  Graphics::Cube(my_camera->transform.position +
                     my_camera->transform.rotation * gun_pos,
                 my_camera->transform.rotation, gun_scale);

  for (int i = 0; i < MAX_BULLETS; i++) {
    if (!bullets[i].alive)
      continue;
    DrawBullet(bullets[i].position, bullets[i].rotation);
  }
}

void Game::Load() {
  KeyboardInput *keyboardInput = new KeyboardInput(keyboard_mapping, 9);
  MouseInput *mouseInput = new MouseInput(mouse_mapping, 2);

  bullets = (Bullet *)malloc(sizeof(Bullet) * MAX_BULLETS);

  // Camera stuff
  my_camera =
      new Camera(45.0f, Window::Instance()->aspect_ratio(), 0.1f, 100.0f);

  my_camera->transform.position = glm::vec3(0, 1, 5);
  my_camera->transform.rotation = glm::quat(glm::vec3(0, glm::pi<float>(), 0));

  Graphics::camera = my_camera;

  keyboardInput->BindAction("up", INPUT_HOLD, [&]() {
    my_camera->transform.position += my_camera->transform.rotation *
                                     glm::vec3(0, 0, +1) * linear_speed *
                                     Time::GetDelta();
  });
  keyboardInput->BindAction("down", INPUT_HOLD, [&]() {
    my_camera->transform.position += my_camera->transform.rotation *
                                     glm::vec3(0, 0, -1) * linear_speed *
                                     Time::GetDelta();
  });
  keyboardInput->BindAction("left", INPUT_HOLD, [&]() {
    my_camera->transform.position += my_camera->transform.rotation *
                                     glm::vec3(+1, 0, 0) * linear_speed *
                                     Time::GetDelta();
  });
  keyboardInput->BindAction("right", INPUT_HOLD, [&]() {
    my_camera->transform.position += my_camera->transform.rotation *
                                     glm::vec3(-1, 0, 0) * linear_speed *
                                     Time::GetDelta();
  });

  keyboardInput->BindAction("right", INPUT_DOWN, [&]() {
    //gun_pos += glm::vec3(0.01, 0, 0);
  });
  keyboardInput->BindAction("left", INPUT_DOWN, [&]() {
    //gun_pos -= glm::vec3(0.01, 0, 0);
  });
  keyboardInput->BindAction("up", INPUT_DOWN, [&]() {
    //gun_pos += glm::vec3(0.0, 0.1, 0);
  });
  keyboardInput->BindAction("down", INPUT_DOWN, [&]() {
    //gun_pos -= glm::vec3(0.0, 0.1, 0);
  });
  keyboardInput->BindAction("pitch+", INPUT_DOWN, [&]() {
    gun_scale *= 1.1;
  });
  keyboardInput->BindAction("pitch-", INPUT_DOWN, [&]() {
    gun_scale /= 1.1;
  });

  mouseInput->BindAction("fire", INPUT_DOWN, [&]() {
    // New bullet
    Bullet b;
    b.position =
        my_camera->transform.position + my_camera->transform.rotation * (gun_pos + glm::vec3(0.0, 0.0, 1.1 * gun_scale.z));
    b.rotation = my_camera->transform.rotation;
    b.velocity =
        my_camera->transform.rotation * glm::vec3(0, 0, 1) * bullet_speed;
    bullets[current_bullet_index] = b;
    current_bullet_index = (current_bullet_index + 1) % MAX_BULLETS;
  });

  mouseInput->BindMovement([&](const MouseMovementData *mouse) {
    my_camera->transform.rotation *=
        glm::quat(glm::vec3(0, -1, 0) * angular_speed * Time::GetDelta() *
                  (mouse->dx / mouse_sensitivity));
  });
}
