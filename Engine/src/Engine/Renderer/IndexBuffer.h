#pragma once
#include "Renderer/Buffer.h"

class IndexBuffer : public Buffer {

private:
  GLuint &mIBO = mRendererID;

public:
  IndexBuffer() {}

  void create(const std::vector<unsigned int> &indices);
  void bind() const override;
  void unbind() const override;
  void destroy() override;
};
