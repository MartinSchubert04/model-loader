#pragma once
#include "Core/Base.h"
#include "Renderer/RenderCommand.h"
#include "RendererAPI.h"
#include "VertexArray.h"
namespace Engine {

class Renderer {
public:
  static void beginScene();
  static void endScene();

  static void submit(const Ref<VertexArray> &vertexArray);

  inline static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }
};

}  // namespace Engine
