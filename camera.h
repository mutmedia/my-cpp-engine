#ifndef CAMERA_H
#define CAMERA_H

#include "transform.h"
#include "glm/mat4x4.hpp" // glm::mat4
using namespace glm;

// TODO: make inherit/composition with a transform
class Camera {
  public:
    Camera(const Transform transform) : transform_(transform) {}
    const mat4 GetViewMatrix();

    Transform transform_;
  private:
    
};

#endif
