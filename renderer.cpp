#include "renderer.h"
#include "glutils.h"

#include "glm/mat4x4.hpp"

#include <algorithm>

void Renderer::AddRenderable(MeshRenderer * renderable) {
    renderables.push_back(renderable);
}

void Renderer::RenderAll(glm::mat4 view_projection, GLint uniform_mvp) {
    std::for_each(renderables.begin(), renderables.end(), [&](Renderable * r) {
        glm::mat4 MVP = view_projection * r->GetModelMatrix();
        glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, &MVP[0][0]);
        GLERRORS("glUniformMatrix4fv");
        r->Render();
    });
}