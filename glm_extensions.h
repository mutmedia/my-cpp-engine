#ifndef GLM_EXTENSIONS_H
#define GLM_EXTENSIONS_H

#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/vec3.hpp"

namespace glm {
quat rotationBetween(vec3 start, vec3 dest);
quat quatLookAt(vec3 direction, vec3 up);
inline vec3 x() { return glm::vec3(1.0, 0.0, 0.0); }
inline vec3 y() { return glm::vec3(0.0, 1.0, 0.0); }
inline vec3 z() { return glm::vec3(0.0, 0.0, 1.0); }
} // namespace glm

#endif
