#ifndef MESH_H
#define MESH_H

#include <SDL2/SDL_opengles2.h>

#include "vertex.h"

class Mesh {
  public:
    Mesh(const Vertex * vertexdata, int verticessize);
    ~Mesh();

    void Render();
  private:
    const Vertex * vertex_data_;
    int vertices_size_;
    GLuint vertex_buffer_;
};

#endif

