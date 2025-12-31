#pragma once

#include "Shader.h"
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <memory>
#include "Texture.h"

using namespace std;

class Model {
public:
  Model(string path);

  void draw(Shader &shader);

private:
  vector<unique_ptr<Mesh>> meshes;
  string directory;
  vector<shared_ptr<Texture>> texturesLoaded;

  void loadModel(string path);
  void processNode(aiNode *node, const aiScene *scene);
  unique_ptr<Mesh> processMesh(aiMesh *mesh, const aiScene *scene);

  vector<shared_ptr<Texture>>
  loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};
