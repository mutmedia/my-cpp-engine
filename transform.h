#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/vec3.hpp"

class Transform {
public:
  Transform(glm::vec3 position = glm::vec3(0.0),
            glm::quat rotation = glm::quat(), glm::vec3 scale = glm::vec3(1.0))
      : position(position), rotation(rotation), scale(scale) {}

  inline glm::mat4 ToModelMatrix() {
    return glm::translate(glm::mat4(), position) * glm::toMat4(rotation) *
           glm::scale(glm::mat4(), scale);
  }

  glm::vec3 position;
  glm::quat rotation;
  glm::vec3 scale;

private:
};

#endif