#ifndef GLM_EXTENSIONS_H
#define GLM_EXTENSIONS_H

#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/vec3.hpp"

namespace glm {
quat rotationBetween(vec3 start, vec3 dest);
quat quatLookAt(vec3 direction, vec3 up);
} // namespace glm

#endif
