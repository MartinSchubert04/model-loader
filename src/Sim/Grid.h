
#include "common.h"
#include "elements/Shader.h"
#include "Object.h"

class Grid : Object {

public:
  glm::vec2 size;
  glm::vec3 position;
  glm::vec3 squareSize;
  glm::vec4 color = glm::vec4(.8f, .8f, .8f, .1f);

  Grid(glm::vec2 size, glm::vec3 position = {0, 0, 0}, float squareSize = 2);

  void draw(Shader *shader) override;
  void update(glm::vec3 force, float delta) override;
};
