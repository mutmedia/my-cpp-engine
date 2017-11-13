#include "graphics.h"
#include "glutils.h"

#include <stdio.h>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr
#include "glm/gtx/quaternion.hpp"

#define MIN(a, b) (a < b ? a : b)

namespace {
void RenderToCamera(std::function<void()> render_func) {
  auto model_matrix = Graphics::world_matrix;
  auto view_matrix = Graphics::camera->view_matrix();
  auto projection_matrix = Graphics::camera->projection_matrix();

  auto mvp_matrix = projection_matrix * view_matrix * model_matrix;

  glUniformMatrix4fv(Graphics::shader->uniform_mvp(), 1, GL_FALSE,
                     &mvp_matrix[0][0]);
  glUniformMatrix4fv(Graphics::shader->uniform_model(), 1, GL_FALSE,
                     &model_matrix[0][0]);
  glUniformMatrix4fv(Graphics::shader->uniform_view(), 1, GL_FALSE,
                     &view_matrix[0][0]);
  glUniformMatrix4fv(Graphics::shader->uniform_projection(), 1, GL_FALSE,
                     &projection_matrix[0][0]);
  GLERRORS("glUniformMatrix4fv");

  if (Graphics::lightCount) {
    glUniform3fv(Graphics::shader->uniform_lightColor(),
                 MIN(Graphics::lightCount, MAX_LIGHT_COUNT),
                 &Graphics::lightColor[0][0]);
    GLERRORS("uniform light colors");
    glUniform3fv(Graphics::shader->uniform_lightPos_worldspace(),
                 MIN(Graphics::lightCount, MAX_LIGHT_COUNT),
                 &Graphics::lightPosition[0][0]);
    GLERRORS("uniform light positions");
    glUniform1i(Graphics::shader->uniform_lightCount(),
                MIN(Graphics::lightCount, MAX_LIGHT_COUNT));
    GLERRORS("uniform light count");
  }

  render_func();
}

struct GraphicsState {
  Shader *shader;
  glm::mat4 world_matrix;
  Camera *camera;
};

const Vertex cube_vertex_data[] = {
    {{
         -1.0f,
         -1.0f,
         -1.0f,
     },
     {
         -1.0,
         0.0,
         0.0,
     }},
    {{
         -1.0f,
         -1.0f,
         +1.0f,
     },
     {
         -1.0,
         0.0,
         0.0,
     }},
    {{
         -1.0f,
         +1.0f,
         +1.0f,
     },
     {
         -1.0,
         0.0,
         0.0,
     }},

    {{
         +1.0f,
         +1.0f,
         -1.0f,
     },
     {0.0, 0.0, -1.0}},
    {{
         -1.0f,
         -1.0f,
         -1.0f,
     },
     {0.0, 0.0, -1.0}},
    {{
         -1.0f,
         +1.0f,
         -1.0f,
     },
     {0.0, 0.0, -1.0}},

    {{
         +1.0f,
         -1.0f,
         +1.0f,
     },
     {0.0, -1.0, 0.0}},
    {{
         -1.0f,
         -1.0f,
         -1.0f,
     },
     {0.0, -1.0, 0.0}},
    {{
         +1.0f,
         -1.0f,
         -1.0f,
     },
     {0.0, -1.0, 0.0}},

    {{
         +1.0f,
         +1.0f,
         -1.0f,
     },
     {0.0, 0.0, -1.0}},
    {{
         +1.0f,
         -1.0f,
         -1.0f,
     },
     {0.0, 0.0, -1.0}},
    {{
         -1.0f,
         -1.0f,
         -1.0f,
     },
     {0.0, 0.0, -1.0}},

    {{
         -1.0f,
         -1.0f,
         -1.0f,
     },
     {
         -1.0,
         0.0,
         0.0,
     }},
    {{
         -1.0f,
         +1.0f,
         +1.0f,
     },
     {
         -1.0,
         0.0,
         0.0,
     }},
    {{
         -1.0f,
         +1.0f,
         -1.0f,
     },
     {
         -1.0,
         0.0,
         0.0,
     }},

    {{
         +1.0f,
         -1.0f,
         +1.0f,
     },
     {0.0, -1.0, 0.0}},
    {{
         -1.0f,
         -1.0f,
         +1.0f,
     },
     {0.0, -1.0, 0.0}},
    {{
         -1.0f,
         -1.0f,
         -1.0f,
     },
     {0.0, -1.0, 0.0}},

    {{
         -1.0f,
         +1.0f,
         +1.0f,
     },
     {0.0, 0.0, +1.0}},
    {{
         -1.0f,
         -1.0f,
         +1.0f,
     },
     {0.0, 0.0, +1.0}},
    {{
         +1.0f,
         -1.0f,
         +1.0f,
     },
     {0.0, 0.0, +1.0}},

    {{
         +1.0f,
         +1.0f,
         +1.0f,
     },
     {
         +1.0,
         0.0,
         0.0,
     }},
    {{
         +1.0f,
         -1.0f,
         -1.0f,
     },
     {
         +1.0,
         0.0,
         0.0,
     }},
    {{
         +1.0f,
         +1.0f,
         -1.0f,
     },
     {
         +1.0,
         0.0,
         0.0,
     }},

    {{
         +1.0f,
         -1.0f,
         -1.0f,
     },
     {
         +1.0,
         0.0,
         0.0,
     }},
    {{
         +1.0f,
         +1.0f,
         +1.0f,
     },
     {
         +1.0,
         0.0,
         0.0,
     }},
    {{
         +1.0f,
         -1.0f,
         +1.0f,
     },
     {
         +1.0,
         0.0,
         0.0,
     }},

    {{
         +1.0f,
         +1.0f,
         +1.0f,
     },
     {0.0, +1.0, 0.0}},
    {{
         +1.0f,
         +1.0f,
         -1.0f,
     },
     {0.0, +1.0, 0.0}},
    {{
         -1.0f,
         +1.0f,
         -1.0f,
     },
     {0.0, +1.0, 0.0}},

    {{
         +1.0f,
         +1.0f,
         +1.0f,
     },
     {0.0, +1.0, 0.0}},
    {{
         -1.0f,
         +1.0f,
         -1.0f,
     },
     {0.0, +1.0, 0.0}},
    {{
         -1.0f,
         +1.0f,
         +1.0f,
     },
     {0.0, +1.0, 0.0}},

    {{
         +1.0f,
         +1.0f,
         +1.0f,
     },
     {0.0, 0.0, +1.0}},
    {{
         -1.0f,
         +1.0f,
         +1.0f,
     },
     {0.0, 0.0, +1.0}},
    {{
         +1.0f,
         -1.0f,
         +1.0f,
     },
     {0.0, 0.0, +1.0}},
};
const int cube_vertices_size = 12 * 3;
Mesh *base_cube_mesh;
} // namespace

Camera *Graphics::camera;
Shader *Graphics::shader;
glm::mat4 Graphics::world_matrix = glm::mat4(1.0f);
glm::vec3 Graphics::material_diffuse_color;
glm::vec3 Graphics::material_specular_color;
int Graphics::lightCount = 0;
glm::vec3 Graphics::lightColor[MAX_LIGHT_COUNT];
glm::vec3 Graphics::lightPosition[MAX_LIGHT_COUNT];

void Graphics::Cube(Transform transform) {
  Graphics::Cube(transform.position, transform.rotation, transform.scale);
}

void Graphics::Cube(glm::vec3 position, glm::quat rotation, glm::vec3 scale) {
  // load cube mesh into GPU and stuff
  if (base_cube_mesh == NULL) {
    base_cube_mesh = new Mesh(cube_vertex_data, cube_vertices_size);
    printf("created new cube mesh\n");
  }

  Graphics::world_matrix = glm::translate(glm::mat4(), position) *
                           glm::toMat4(rotation) * glm::scale(glm::mat4(), scale);
  RenderToCamera([]() { base_cube_mesh->Render(); });
}

void Graphics::SetMaterial(glm::vec3 diffuse_color, glm::vec3 specular_color) {
  Graphics::material_diffuse_color = diffuse_color;
  Graphics::material_specular_color = specular_color;

  glUniform3fv(Graphics::shader->uniform_material_diffuse_color(), 1,
               &diffuse_color[0]);
  glUniform3fv(Graphics::shader->uniform_material_specular_color(), 1,
               &specular_color[0]);
  GLERRORS("glUniform3fv");
}

void Graphics::SetMaterial(glm::vec3 diffuse_color) {
  Graphics::SetMaterial(diffuse_color, diffuse_color);
}

void Graphics::PointLight(glm::vec3 position, glm::vec3 color, float intensity) {
  Graphics::lightColor[Graphics::lightCount % MAX_LIGHT_COUNT] =
      color * intensity;
  Graphics::lightPosition[Graphics::lightCount % MAX_LIGHT_COUNT] = position;
  Graphics::lightCount++;
}

// Cleans state variables for next iteration
void Graphics::Clear() { lightCount = 0; }