#include "Renderer/Buffer.h"
#include <cstdint>

namespace Engine {

class OpenGLvertexBuffer : public VertexBuffer {
public:
  OpenGLvertexBuffer(float *vertices, uint32_t size);
  ~OpenGLvertexBuffer();

  void bind() const override;
  void unbind() const override;

private:
  unsigned int mRendererID;
};

class OpenGLindexBuffer : public IndexBuffer {
public:
  OpenGLindexBuffer(uint32_t *indices, uint32_t size);
  ~OpenGLindexBuffer();

  void bind() const override;
  void unbind() const override;

  uint32_t getCount() override { return mCount; };

private:
  unsigned int mRendererID;
  uint32_t mCount;
};

}  // namespace Engine
