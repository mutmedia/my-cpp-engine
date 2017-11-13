#ifndef CAMERA_H
#define CAMERA_H

#include "glm/mat4x4.hpp" // glm::mat4
#include "transform.h"

// TODO: make inherit/composition with a transform
class Camera {
public:
  Camera(const float fov, const float aspect_ratio, const float near,
         const float far)
      : fov(fov), aspect_ratio(aspect_ratio), near(near), far(far) {}

  glm::mat4 view_matrix() const;
  glm::mat4 projection_matrix() const;

  Transform transform;
  float aspect_ratio;
  float fov; // Degrees
  float near;
  float far;

private:
};

#endif
