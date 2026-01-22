#pragma once
#include "pch.h"
#include <cstdint>

namespace Engine {

class Buffer {

public:
  virtual ~Buffer() = default;

  virtual void bind() const = 0;
  virtual void unbind() const = 0;
};

class VertexBuffer : public Buffer {
public:
  virtual ~VertexBuffer() {};

  virtual void bind() const override;
  virtual void unbind() const override;

  static Scope<VertexBuffer> create(float *vertices, uint32_t size);
};

class IndexBuffer : public Buffer {
public:
  virtual ~IndexBuffer() {};

  virtual void bind() const override;
  virtual void unbind() const override;

  virtual uint32_t getCount();

  static Scope<IndexBuffer> create(uint32_t *indices, uint32_t size);
};

}  // namespace Engine
