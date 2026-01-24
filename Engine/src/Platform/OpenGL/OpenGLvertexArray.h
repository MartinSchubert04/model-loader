#include "Core/Base.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include <cstdint>
#include <vector>

namespace Engine {

class OpenGLvertexArray : public VertexArray {
public:
  OpenGLvertexArray();
  ~OpenGLvertexArray();

  void bind() const override;
  void unbind() const override;

  void addVertexBuffer(const Ref<VertexBuffer> &vb) override;
  void setIndexBuffer(const Ref<IndexBuffer> &ib) override;
  Ref<IndexBuffer> &getIndexBuffer() override { return mIndexBuffer; }

private:
  uint32_t mRendererID;
  std::vector<Ref<VertexBuffer>> mVertexBuffers;
  Ref<IndexBuffer> mIndexBuffer;
};

}  // namespace Engine
