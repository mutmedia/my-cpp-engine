#include "camera.h"

#include "transform.h"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace glm;

const mat4 Camera::GetViewMatrix() {
  return lookAt(
      transform_.position_,
      transform_.position_ + transform_.rotation_ * vec3(0, 0, 1),
      transform_.rotation_ * vec3(0, 1, 0)
  );
}

