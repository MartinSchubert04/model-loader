#include "Renderer.h"

namespace Engine {

void Renderer::beginScene() {}

void Renderer::endScene() {}

void Renderer::submit(const Ref<VertexArray> &vertexArray) {
  vertexArray->bind();
  RenderCommand::drawIndexed(vertexArray);
}

}  // namespace Engine
