#pragma once

#include "Core/Base.h"
#include "Renderer/Buffer.h"

namespace Engine {

class VertexArray {
public:
  virtual ~VertexArray() {}

  virtual void bind() const = 0;
  virtual void unbind() const = 0;

  virtual void addVertexBuffer(const Ref<VertexBuffer> &vb) = 0;
  virtual void setIndexBuffer(const Ref<IndexBuffer> &ib) = 0;
  virtual Ref<IndexBuffer> &getIndexBuffer() = 0;

  static Scope<VertexArray> create();
};

}  // namespace Engine
