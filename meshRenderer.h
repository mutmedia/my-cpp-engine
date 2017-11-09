#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include <vector>

#include "glm/mat4x4.hpp"

#include "mesh.h"
#include "transform.h"

class MeshRenderer {
    public:
        MeshRenderer() : MeshRenderer(NULL) {}
        MeshRenderer(Mesh * mesh);
        ~MeshRenderer();

        void Render();

        // TODO: Will move up to more generic component
        glm::mat4 GetModelMatrix();
        Transform transform_;
    private:
        Mesh * mesh_;
};

#endif