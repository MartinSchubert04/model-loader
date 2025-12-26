
#include "common.h"
#include "VertexBuffer.h"

namespace render {

VertexBuffer::VertexBuffer(const std::vector<Vertex> &vertices) {

  GLcall(glGenBuffers(1, &mVBO));
  GLcall(glBindBuffer(GL_ARRAY_BUFFER, mVBO));
  GLcall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
                      vertices.data(), GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
  VertexBuffer::destroy();
}

void VertexBuffer::bind() const {
  GLcall(glBindVertexArray(mVBO));
}

void VertexBuffer::unbind() const {
  GLcall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::destroy() {
  GLcall(glDeleteBuffers(1, &mVBO));
}
}  // namespace render
