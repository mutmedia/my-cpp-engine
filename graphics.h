#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "camera.h"
#include "mesh.h"
#include "shader.h"
#include "transform.h"

#include <functional>

#include "glm/vec3.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

#define MAX_LIGHT_COUNT 10

namespace Graphics {
void Cube(glm::vec3 position, glm::quat rotation = glm::quat(),
          glm::vec3 scale = glm::vec3(1.0f));
void Cube(Transform transform);

void SetMaterial(glm::vec3 diffuse_color, glm::vec3 specular_color);
void SetMaterial(glm::vec3 diffuse_color);

void PointLight(glm::vec3 position, glm::vec3 color, float intensity);

void SetAmbientLight(glm::vec3 color);
void SetClearColor(glm::vec3 color);

void Clear();

struct GraphicsData {
  Camera *camera;
  Shader *shader;
  glm::mat4 world_matrix;
  glm::vec3 material_diffuse_color;
  glm::vec3 material_specular_color;
};

extern GraphicsData *currentData;

extern Camera *camera;
extern Shader *shader;
extern glm::mat4 world_matrix;
extern glm::vec3 material_diffuse_color;
extern glm::vec3 material_specular_color;
extern int lightCount;
extern glm::vec3 lightColor[];
extern glm::vec3 lightPosition[];
extern glm::vec3 ambient_light;

} // namespace Graphics

#endif