#pragma once

#include "Object.h"
#include "elements/Mesh.h"

class Planet : public Object {

private:
public:
  float radius;
  glm::vec2 segments;
  glm::vec3 position;
  glm::vec4 color;

  Planet(float radius, glm::vec2 segments, glm::vec3 position);

  void update(Shader *shader) override;
  void draw(Shader *shader) override;
  Mesh *getMesh() { return mesh.get(); }
};
