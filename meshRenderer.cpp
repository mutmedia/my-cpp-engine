#include "meshRenderer.h"
#include "renderer.h"

#include <stdio.h>

MeshRenderer::MeshRenderer(Mesh * mesh) : mesh_(mesh) {
    Renderer::AddRenderable(this);
}

MeshRenderer::~MeshRenderer() {
    free(mesh_);
    // SUPER-TODO: remove from global rendering list
}

void MeshRenderer::Render() {
    if (mesh_ == NULL) {
        printf("WARNING: Trying to render MeshRenderer without mesh.\n");
    } else {
        mesh_->Render();
    }
}

glm::mat4 MeshRenderer::GetModelMatrix() {
    return transform_.ToModelMatrix();
}