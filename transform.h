#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "glm_extensions.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/vec3.hpp"

class Transform {
public:
  Transform(glm::vec3 position = glm::vec3(0.0),
            glm::quat rotation = glm::quat(), glm::vec3 scale = glm::vec3(1.0))
      : position(position), rotation(rotation), scale(scale) {}

  glm::mat4 ToModelMatrix() {
    // TODO: store matrix?
    return glm::translate(glm::mat4(), position) * glm::toMat4(rotation) *
           glm::scale(glm::mat4(), scale);
  }

  glm::vec3 forward() { return glm::rotate(rotation, -glm::z()); }
  glm::vec3 up() { return glm::rotate(rotation, glm::y()); }
  glm::vec3 right() { return glm::rotate(rotation, glm::x()); }

  glm::vec3 position;
  glm::quat rotation;
  glm::vec3 scale;

private:
};

#endif