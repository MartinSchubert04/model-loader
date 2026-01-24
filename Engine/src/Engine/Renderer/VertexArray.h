#pragma once

#include "Core/Base.h"
#include "Renderer/Buffer.h"

namespace Engine {

class VertexArray {
public:
  virtual ~VertexArray() {}

  virtual void bind() const = 0;
  virtual void unbind() const = 0;

  virtual void addVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) = 0;
  virtual void setIndexBuffer(const Ref<IndexBuffer> &indexBuffer) = 0;
  virtual Ref<IndexBuffer> &getIndexBuffer() = 0;

  static Ref<VertexArray> create();
};

}  // namespace Engine
