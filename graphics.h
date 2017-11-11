#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "mesh.h"
#include "camera.h"
#include "shader.h"

#include "glm/vec3.hpp"
#include "glm/gtc/quaternion.hpp" 
#include "glm/gtx/quaternion.hpp" 

using namespace glm;

namespace Graphics {
    void Initialize();

    void Cube(vec3 position = vec3(1.0), quat rotation = quat(), vec3 scale = vec3(1.0f));

    static Camera * camera = new Camera(45, 1, 0.1f, 100.0f);

    static Shader * shader;

    static mat4 world_matrix;

    static void RenderToCamera();

    struct GraphicsState {
      Shader * shader;
      mat4 world_matrix;
      Camera * camera;
    };


}


static const Vertex cube_vertex_data[] = {
  {-1.0f, -1.0f, -1.0f,},
  {-1.0f, -1.0f, +1.0f,},
  {-1.0f, +1.0f, +1.0f,},
  {+1.0f, +1.0f, -1.0f,},
  {-1.0f, -1.0f, -1.0f,},
  {-1.0f, +1.0f, -1.0f,},
  {+1.0f, -1.0f, +1.0f,},
  {-1.0f, -1.0f, -1.0f,},
  {+1.0f, -1.0f, -1.0f,},
  {+1.0f, +1.0f, -1.0f,},
  {+1.0f, -1.0f, -1.0f,},
  {-1.0f, -1.0f, -1.0f,},
  {-1.0f, -1.0f, -1.0f,},
  {-1.0f, +1.0f, +1.0f,},
  {-1.0f, +1.0f, -1.0f,},
  {+1.0f, -1.0f, +1.0f,},
  {-1.0f, -1.0f, +1.0f,},
  {-1.0f, -1.0f, -1.0f,},
  {-1.0f, +1.0f, +1.0f,},
  {-1.0f, -1.0f, +1.0f,},
  {+1.0f, -1.0f, +1.0f,},
  {+1.0f, +1.0f, +1.0f,},
  {+1.0f, -1.0f, -1.0f,},
  {+1.0f, +1.0f, -1.0f,},
  {+1.0f, -1.0f, -1.0f,},
  {+1.0f, +1.0f, +1.0f,},
  {+1.0f, -1.0f, +1.0f,},
  {+1.0f, +1.0f, +1.0f,},
  {+1.0f, +1.0f, -1.0f,},
  {-1.0f, +1.0f, -1.0f,},
  {+1.0f, +1.0f, +1.0f,},
  {-1.0f, +1.0f, -1.0f,},
  {-1.0f, +1.0f, +1.0f,},
  {+1.0f, +1.0f, +1.0f,},
  {-1.0f, +1.0f, +1.0f,},
  {+1.0f, -1.0f, +1.0f,},
};
static const int cube_vertices_size = 12 * 3;
static const Mesh * base_cube_mesh = new Mesh(cube_vertex_data, cube_vertices_size);

#endif