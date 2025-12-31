#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
           std::vector<std::shared_ptr<Texture>> textures)
    : va() {
  this->vertices = vertices;
  this->indices = indices;
  this->textures = textures;

  setupMesh();
}

Mesh::~Mesh() {
  vb.destroy();
  ib.destroy();
  va.destroy();
}

void Mesh::setupMesh() {

  VertexBufferLayout layout;

  vb.create(vertices);
  ib.create(indices);

  va.bind();
  ib.bind();

  layout.push<float>(3);  // position
  layout.push<float>(3);  // normal
  layout.push<float>(2);  // texCoords

  va.addBuffer(vb, layout);

  va.unbind();
}

void Mesh::draw(Shader &shader) {
  unsigned int diffuseNr = 1;
  unsigned int specularNr = 1;
  for (unsigned int i = 0; i < textures.size(); i++) {

    std::string number;
    std::string name = textures[i]->getType();
    if (name == "texture_diffuse")
      number = std::to_string(diffuseNr++);
    else if (name == "texture_specular")
      number = std::to_string(specularNr++);

    shader.setInt(("material." + name + number).c_str(), i);
    textures[i]->bind(i);
  }

  // GLcall(glActiveTexture(GL_TEXTURE0));

  va.bind();
  GLcall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));
  va.unbind();
}
