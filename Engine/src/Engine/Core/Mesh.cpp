#include "Mesh.h"
#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"
#include "pch.h"
#include <vector>

namespace Engine {

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
           std::vector<std::shared_ptr<Texture>> textures) :
    va() {
  this->vertices = vertices;
  this->indices = indices;
  this->textures = textures;

  setupMesh();
}

void Mesh::setupMesh() {

  std::vector<glm::vec3> positions;
  for (auto &v : vertices) {
    positions.push_back(v.position);
  }

  vb = VertexBuffer::create(vertices, vertices.size());
  ib = IndexBuffer::create(indices);

  va->bind();
  ib->bind();

  Engine::BufferLayout layout = {
      {Engine::Types::ShaderDataType::float3, "a_Pos"},
      {Engine::Types::ShaderDataType::float3, "a_Normal"},
      {Engine::Types::ShaderDataType::float2, "a_TextCoords"},
      {Engine::Types::ShaderDataType::float4, "a_Color"},
  };

  va.addBuffer(vb, layout);

  va.unbind();
}

void Mesh::draw(Shader &shader, DrawType type) {
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

  switch (type) {

  case DrawType::TRIANGLES:
    GLcall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));
    break;
  case DrawType::LINES:
    GLcall(glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0));
    break;
  case DrawType::LINE_STRIP:
    GLcall(glDrawArrays(GL_LINE_STRIP, 0, vertices.size()));
    break;
  default:
    GLcall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));
  }

  va.unbind();
}

}  // namespace Engine
