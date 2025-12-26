#pragma once
#include "Shader.h"
#include "Vertex.h"
#include <glm/glm.hpp>
#include <string>

using namespace std;

struct Texture {
  unsigned int id;
  string type;
  string path;
};

class Mesh {
public:
  vector<Vertex> vertices;
  vector<unsigned int> indices;
  vector<Texture> textures;

  Mesh(vector<Vertex> vertices, vector<unsigned int> indices,
       vector<Texture> textures);

  void draw(Shader &shader);

private:
  unsigned int VAO, VBO, EBO;

  void setupMesh();
};
