#pragma once

#include "Object.h"
#include "elements/Mesh.h"

class Planet : public Object {
public:
  float radius;
  glm::vec2 segments;
  glm::vec3 position;
  glm::vec4 color;
  float scaleFactor;

  Planet(float radius, glm::vec2 segments, glm::vec3 position);

  void update(Shader *shader) override;
  void draw(Shader *shader) override;
  void scale(float scalar);

  Mesh *getMesh() { return mesh.get(); }
  std::vector<glm::vec3> getVerticesPos();
};
