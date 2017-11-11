#include "mesh.h"
#include "vertex.h"
#include "glutils.h"

Mesh::Mesh(const Vertex * vertexdata, int verticessize) :
  vertex_data_(vertexdata), vertices_size_(verticessize) {
    glGenBuffers(1, &vertex_buffer_);
}

Mesh::~Mesh() {
  glDeleteBuffers(1, &vertex_buffer_);
}

// TODO: check if using AoS or SoA
void Mesh::Render() const {
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
  glBufferData(GL_ARRAY_BUFFER,
      sizeof(Vertex) * vertices_size_,
      vertex_data_,
      GL_STATIC_DRAW);
  GLERRORS("mesh buffer data");

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0,
      3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
      (GLvoid *)offsetof(Vertex, position));

      /*
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1,
      3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
      (GLvoid *)offsetof(Vertex, color));
  */

  GLERRORS("mesh attrib array");

  glDrawArrays(GL_TRIANGLES, 0, vertices_size_);
  GLERRORS("mesh draw");
  glDisableVertexAttribArray(0);
  //glDisableVertexAttribArray(1);
}
