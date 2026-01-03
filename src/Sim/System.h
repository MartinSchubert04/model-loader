#pragma once

#include "common.h"
#include "Planet.h"

class System {

public:
  std::vector<std::unique_ptr<Planet>> planets;

  void addEntity(std::unique_ptr<Planet> planet);
  void draw(Shader *shader);
  void update(Shader *shader);
};
