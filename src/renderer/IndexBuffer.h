#pragma once

#include "Render.h"

namespace render {

class IndexBuffer : Buffer {

private:
  GLuint &mIBO = mRendererID;

public:
  IndexBuffer(const std::vector<unsigned int> &indices);
  ~IndexBuffer();

  void bind() const override;
  void unbind() const override;
  void destroy() override;
};

};  // namespace render
