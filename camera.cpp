#include "camera.h"

#include "transform.h"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace glm;

const mat4 Camera::GetViewProjectionMatrix() {
  // TODO: ortho camera?
  // TODO: store results and only recalculate on change?
  mat4 projection = perspective(
    radians(fov_),
    aspect_ratio_,
    near_,
    far_);

  mat4 view = lookAt(
      transform_.position_,
      transform_.position_ + transform_.rotation_ * vec3(0, 0, 1),
      transform_.rotation_ * vec3(0, 1, 0)
  );

  return projection * view;
}

