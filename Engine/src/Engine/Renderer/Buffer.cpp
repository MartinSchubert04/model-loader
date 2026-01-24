#include "Buffer.h"
#include "Core/Assert.h"
#include "Core/Base.h"
#include "Platform/OpenGL/OpenGLbuffer.h"
#include "Renderer.h"
#include "RendererAPI.h"

namespace Engine {

Ref<VertexBuffer> VertexBuffer::create(float *vertices, uint32_t size) {

  switch (Renderer::getAPI()) {
  case RendererAPI::API::None: {
    CORE_ASSERT(false, "Renderer API: returning nullptr (NO RENDERER API PROVIDED)");
    return nullptr;
    break;
  }

  case RendererAPI::API::OpenGL: {
    return createRef<OpenGLvertexBuffer>(vertices, size);
    break;
  }
  }

  CORE_ASSERT(false, "Renderer API: returning nullptr (NO RENDERER API PROVIDED)");
  return nullptr;
}

Scope<IndexBuffer> IndexBuffer::create(uint32_t *indices, uint32_t size) {

  switch (Renderer::getAPI()) {
  case RendererAPI::API::None: {
    CORE_ASSERT(false, "Renderer API: returning nullptr (NO RENDERER API PROVIDED)");
    return nullptr;
    break;
  }

  case RendererAPI::API::OpenGL: {
    return createScope<OpenGLindexBuffer>(indices, size);
    break;
  }
  }

  CORE_ASSERT(false, "Renderer API: returning nullptr (NO RENDERER API PROVIDED)");
  return nullptr;
}

}  // namespace Engine
