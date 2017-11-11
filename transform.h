#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/vec3.hpp"

using namespace glm;

class Transform {
public:
  Transform(vec3 position = vec3(0.0), quat rotation = quat(),
            vec3 scale = vec3(1.0))
      : position(position), rotation(rotation), scale(scale) {}

  inline mat4 ToModelMatrix() {
    return glm::translate(mat4(), position) * glm::toMat4(rotation) *
           glm::scale(mat4(), scale);
  }

  vec3 position;
  quat rotation;
  vec3 scale;

private:
};

#endif