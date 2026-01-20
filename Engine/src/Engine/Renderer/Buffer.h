#pragma once
#include "pch.h"

namespace Engine {

class Buffer {

public:
  virtual void bind() const = 0;
  virtual void unbind() const = 0;
  virtual void destroy() = 0;

protected:
  GLuint mRendererID;
};
}  // namespace Engine
