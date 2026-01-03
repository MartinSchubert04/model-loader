#pragma once

#include "common.h"
#include "elements/Vertex.h"
#include "elements/Mesh.h"

class Object {

protected:
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;

public:
  std::unique_ptr<Mesh> mesh;

  virtual void update(Shader *shader) = 0;
  virtual void draw(Shader *shader) = 0;
};
