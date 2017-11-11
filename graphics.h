#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "mesh.h"
#include "camera.h"
#include "shader.h"

#include <functional>

#include "glm/vec3.hpp"
#include "glm/gtc/quaternion.hpp" 
#include "glm/gtx/quaternion.hpp" 

using namespace glm;

namespace Graphics {
    void Cube(vec3 position = vec3(1.0), quat rotation = quat(), vec3 scale = vec3(1.0f));

    extern Camera * camera;
    extern Shader * shader;
    extern mat4 world_matrix;
}

#endif