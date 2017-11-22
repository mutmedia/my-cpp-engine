#include "camera.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/mat4x4.hpp"
#include "transform.h"

glm::mat4 Camera::projection_matrix() const {
  // TODO: ortho camera?
  return glm::perspective(glm::radians(fov), aspect_ratio, near, far);
}

glm::mat4 Camera::view_matrix() const {

  // TODO: store results and only recalculate on change?
  return glm::inverse(glm::translate(glm::mat4(), transform.position) *
                      glm::mat4_cast(transform.rotation));
}
