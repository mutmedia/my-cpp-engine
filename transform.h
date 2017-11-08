#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "glm/vec3.hpp"
#include "glm/gtc/quaternion.hpp" 
#include "glm/gtx/quaternion.hpp"

using namespace glm;

class Transform {
  public:
    Transform(vec3 position, quat rotation, vec3 scale)
      : position_(position), rotation_(rotation), scale_(scale) {}

    vec3 position_;
    quat rotation_;
    vec3 scale_;
  private:
    
};

#endif

