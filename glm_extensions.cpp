#include "glm_extensions.h"

namespace glm {
quat rotationBetween(vec3 start, vec3 dest) {
  start = normalize(start);
  dest = normalize(dest);

  float cosTheta = dot(start, dest);

  vec3 rotationAxis;

  if (cosTheta < -1 + 0.001f) { // Opposite vectors
    rotationAxis = cross(vec3(0.0, 0.0, 1.0), start);
    rotationAxis = normalize(rotationAxis);
    if (length2(rotationAxis) < 0.01f) { // parallel to (0.0, 0.0, 1.0)
      rotationAxis = cross(vec3(1.0, 0.0, 0.0), start);
      rotationAxis = normalize(rotationAxis);
    }

    return angleAxis(pi<float>(), rotationAxis);
  }

  rotationAxis = cross(start, dest);
  float s = sqrt((1 + cosTheta) * 2);
  float invs = 1 / s;

  return quat(s * 0.5f, rotationAxis * invs);
}

quat quatLookAt(vec3 direction, vec3 up) {
  auto rot1 = rotationBetween(vec3(0.0, 0.0, -1.0), direction);

  vec3 right = cross(direction, up);
  up = cross(right, direction);

  vec3 newUp = rot1 * vec3(0.0, 1.0, 0.0);
  auto rot2 = rotationBetween(newUp, up);

  return rot2 * rot1;
}
} // namespace glm