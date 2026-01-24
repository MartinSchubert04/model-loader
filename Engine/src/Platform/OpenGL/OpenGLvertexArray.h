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

  void addVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) override;
  void setIndexBuffer(const Ref<IndexBuffer> &indexBuffer) override;
  Ref<IndexBuffer> &getIndexBuffer() override { return mIndexBuffer; }

private:
  uint32_t mRendererID;
  std::vector<Ref<VertexBuffer>> mVertexBuffers;
  Ref<IndexBuffer> mIndexBuffer;
};

}  // namespace Engine
