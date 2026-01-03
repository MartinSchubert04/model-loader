#include "Planet.h"

Planet::Planet(float radius, glm::vec2 segments, glm::vec3 pos)
    : radius(radius), segments(segments), position(pos) {

  float PI = 3.14;
  this->color = glm::vec4(.8, .8, .8, .8);

  for (int y{0}; y <= segments.y; y++) {
    for (int x{0}; x <= segments.x; x++) {
      Vertex vertex;

      float xSeg = float(x) / segments.x;
      float ySeg = float(y) / segments.y;

      float xPos = std::cos(xSeg * 2.0f * PI) * std::sin(ySeg * PI);
      float yPos = std::cos(ySeg * PI);
      float zPos = std::sin(xSeg * 2.0f * PI) * std::sin(ySeg * PI);

      vertex.position = glm::vec3(xPos, yPos, zPos);

      // calculate normal
      vertex.normal = glm::vec3(xPos, yPos, zPos) - position;
      vertex.texCoords = glm::vec2(0.0f, 0.0f);
      vertex.color = color;

      vertices.push_back(vertex);
    }
  }

  for (int y = 0; y < segments.y; y++) {
    for (int x = 0; x < segments.x; x++) {
      unsigned int curRow = y * (segments.x + 1);
      unsigned int nextRow = (y + 1) * (segments.x + 1);

      // Triángulo 1
      indices.push_back(curRow + x);
      indices.push_back(nextRow + x);
      indices.push_back(curRow + x + 1);

      // Triángulo 2
      indices.push_back(nextRow + x);
      indices.push_back(nextRow + x + 1);
      indices.push_back(curRow + x + 1);
    }
  }

  mesh = std::make_unique<Mesh>(vertices, indices,
                                std::vector<std::shared_ptr<Texture>>{});
}

void Planet::draw(Shader *shader) {
  mesh->draw(*shader);
}

void Planet::update(Shader *shader) {
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, position);
  model = glm::scale(model, glm::vec3(radius));
  shader->setMat4("model", model);
  shader->setVec4("modelColor", color);
}
