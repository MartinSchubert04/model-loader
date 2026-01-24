#include "Core/Base.h"
#include "Renderer/Buffer.h"
#include "pch.h"
#include "Renderer/VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLvertexArray.h"
namespace Engine {

Ref<VertexArray> VertexArray::create() {
  switch (Renderer::getAPI()) {
  case RendererAPI::API::None: {
    CORE_ASSERT(false, "Renderer API: returning nullptr (NO RENDERER API PROVIDED)");
    return nullptr;
    break;
  }

  case RendererAPI::API::OpenGL: {
    return createRef<OpenGLvertexArray>();
    break;
  }
  }
}

}  // namespace Engine
