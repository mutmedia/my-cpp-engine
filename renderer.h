#ifndef RENDERER_H
#define RENDERER_H

#include "meshRenderer.h"

#include <SDL_opengles2.h>

namespace Renderer {
    typedef MeshRenderer Renderable;
    static std::vector<Renderable *> renderables;
    void AddRenderable(Renderable * renderable);
    void RenderAll(glm::mat4 view_projection, GLint uniform_mvp);
}

#endif