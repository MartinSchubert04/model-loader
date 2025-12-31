#pragma once

#include "Shader.h"
#include "Vertex.h"
#include "Buffers/VertexArray.h"
#include "Texture.h"

using namespace render;

class Mesh {
public:
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<std::shared_ptr<Texture>> textures;

  Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
       std::vector<std::shared_ptr<Texture>> textures);
  ~Mesh();

  void draw(Shader &shader);

private:
  VertexBuffer vb;
  IndexBuffer ib;
  VertexArray va;

  unsigned int VAO, VBO, EBO;

  void setupMesh();
};
