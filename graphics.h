#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "camera.h"
#include "mesh.h"
#include "shader.h"
#include "transform.h"

#include <functional>

#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/vec3.hpp"

#define MAX_LIGHT_COUNT 10

using namespace glm;

namespace Graphics {
void Cube(vec3 position, quat rotation = quat(),
          vec3 scale = vec3(1.0f));
void Cube(Transform transform);

void SetMaterial(vec3 diffuse_color, vec3 specular_color);
void SetMaterial(vec3 diffuse_color);

void PointLight(vec3 position, vec3 color, float intensity);

void Clear();

struct GraphicsData {
  Camera *camera;
  Shader *shader;
  mat4 world_matrix;
  vec3 material_diffuse_color;
  vec3 material_specular_color;
};

extern GraphicsData * currentData;

extern Camera *camera;
extern Shader *shader;
extern mat4 world_matrix;
extern vec3 material_diffuse_color;
extern vec3 material_specular_color;
extern int lightCount;
extern vec3 lightColor[];
extern vec3 lightPosition[];

} // namespace Graphics

#endif