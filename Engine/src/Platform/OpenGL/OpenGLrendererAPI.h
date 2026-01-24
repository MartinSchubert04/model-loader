#pragma once

#include "Engine/Renderer/RendererAPI.h"

namespace Engine {
class OpenGLrendererAPI : public RendererAPI {

  void setClearColor(const glm::vec4 &color) override;
  void clear() override;

  void drawIndexed(const Ref<VertexArray> &vertexArray) override;
};

}  // namespace Engine
