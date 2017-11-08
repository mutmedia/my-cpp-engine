#ifndef CAMERA_H
#define CAMERA_H

#include "transform.h"
#include "glm/mat4x4.hpp" // glm::mat4
using namespace glm;

// TODO: make inherit/composition with a transform
class Camera {
  public:
    Camera(const float fov, const float aspect_ratio, const float near, const float far) 
      : fov_(fov), aspect_ratio_(aspect_ratio), near_(near), far_(far) {}
    const mat4 GetViewProjectionMatrix();

    Transform transform_;
    float aspect_ratio_;
    float fov_; // Degrees
    float near_;
    float far_;
  private:
    
};

#endif
