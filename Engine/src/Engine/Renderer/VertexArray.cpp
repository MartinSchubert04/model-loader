#include "Core/Base.h"
#include "Renderer/Buffer.h"
#include "pch.h"
#include "Renderer/VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLvertexArray.h"
namespace Engine {

Scope<VertexArray> VertexArray::create() {
  switch (Renderer::getAPI()) {
  case RendererAPI::None: {
    CORE_ASSERT(false, "Renderer API: returning nullptr (NO RENDERER API PROVIDED)");
    return nullptr;
    break;
  }

  case RendererAPI::OpenGL: {
    return createScope<OpenGLvertexArray>();
    break;
  }
  }
}

}  // namespace Engine
