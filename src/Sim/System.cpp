#include "System.h"
#include "Object.h"

void System::update(Shader *shader) {
  for (auto &p : planets) {
    p->update(shader);
  }
}

void System::draw(Shader *shader) {
  for (auto &p : planets) {
    p->draw(shader);
  }
}

void System::addEntity(std::unique_ptr<Planet> planet) {
  planets.push_back(std::move(planet));
}
