#include "graphics.h"
#include "glutils.h"

#include <stdio.h>

#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace {
    void RenderToCamera(std::function<void()> render_func) {
        auto view_projection_matrix = Graphics::camera->GetViewProjectionMatrix();

        auto mvp_matrix = view_projection_matrix * Graphics::world_matrix;

        glUniformMatrix4fv(Graphics::shader->uniform_mvp(),
                        1,
                        GL_FALSE,
                        &mvp_matrix[0][0]);
        GLERRORS("glUniformMatrix4fv");

        render_func();
    }

    struct GraphicsState
    {
        Shader *shader;
        mat4 world_matrix;
        Camera *camera;
    };

    const Vertex cube_vertex_data[] = {
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
    const int cube_vertices_size = 12 * 3;
    Mesh * base_cube_mesh;
}

Camera * Graphics::camera;
Shader * Graphics::shader;
mat4 Graphics::world_matrix = mat4(1.0f);

void Graphics::Cube(vec3 position, quat rotation, vec3 scale) {
    // load cube mesh into GPU and stuff
    if(base_cube_mesh == NULL) {
        base_cube_mesh = new Mesh(cube_vertex_data, cube_vertices_size);
        printf("created new cube mesh\n");
    }

    Graphics::world_matrix = glm::translate(mat4(), position) *
                   glm::toMat4(rotation) *
                   glm::scale(mat4(), scale);
    RenderToCamera([]() { 
        base_cube_mesh->Render(); 
    });
}


