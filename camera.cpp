#include "camera.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/mat4x4.hpp"
#include "transform.h"

using namespace glm;

mat4 Camera::projection_matrix() const {
  // TODO: ortho camera?
  return perspective(radians(fov), aspect_ratio, near, far);
}

mat4 Camera::view_matrix() const {

  // TODO: store results and only recalculate on change?
  return lookAt(transform.position,
                transform.position + transform.rotation * vec3(0, 0, 1),
                transform.rotation * vec3(0, 1, 0));
}
