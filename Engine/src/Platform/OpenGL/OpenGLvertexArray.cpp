#include "Core/Application.h"
#include "Core/Assert.h"
#include "Core/Base.h"
#include "OpenGLvertexArray.h"
#include "Renderer/Buffer.h"
#include "pch.h"

namespace Engine {

OpenGLvertexArray::OpenGLvertexArray() {
  glCreateVertexArrays(1, &mRendererID);
}

OpenGLvertexArray::~OpenGLvertexArray() {
  glDeleteVertexArrays(1, &mRendererID);
}

void OpenGLvertexArray::bind() const {
  glBindVertexArray(mRendererID);
}
void OpenGLvertexArray::unbind() const {
  glBindVertexArray(0);
}
void OpenGLvertexArray::addVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) {
  CORE_ASSERT(vertexBuffer->getLayout().getElements().size(), "Vertex Buffer has no layout!")

  glBindVertexArray(mRendererID);
  vertexBuffer->bind();

  auto &layout = vertexBuffer->getLayout();
  auto &elements = layout.getElements();
  for (unsigned int i{0}; i < elements.size(); i++) {
    auto &e = elements[i];
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, e.getElementCount(), e.getElementType(), e.normalized ? GL_TRUE : GL_FALSE,
                          layout.getStride(), (const void *)e.offset);
  }

  mVertexBuffers.push_back(vertexBuffer);
}
void OpenGLvertexArray::setIndexBuffer(const Ref<IndexBuffer> &ib) {
  glBindVertexArray(mRendererID);
  ib->bind();
  mIndexBuffer = ib;
}

}  // namespace Engine
