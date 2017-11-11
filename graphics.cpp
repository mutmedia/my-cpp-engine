#include "graphics.h"
#include "glutils.h"

void Graphics::RenderToCamera() {
    auto view_projection_matrix = Graphics::camera->GetViewProjectionMatrix();
    
    auto mvp_matrix = view_projection_matrix * Graphics::world_matrix;

    glUniformMatrix4fv(Graphics::shader->uniform_mvp(),
     1,
     GL_FALSE,
     &mvp_matrix[0][0]);
    GLERRORS("glUniformMatrix4fv");


}

void Graphics::Cube(vec3 position = vec3(1.0), quat rotation = quat(), vec3 scale = vec3(1.0f)) {
    base_cube_mesh->Render();
}