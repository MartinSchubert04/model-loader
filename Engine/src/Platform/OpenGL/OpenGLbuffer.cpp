#include "OpenGLbuffer.h"
#include "pch.h"
#include <cstdint>

namespace Engine {

//////////////////////////////////////////////////////////
// Vertex Buffer /////////////////////////////////////////
//////////////////////////////////////////////////////////

OpenGLvertexBuffer::OpenGLvertexBuffer(float *vertices, uint32_t size) {

  glCreateBuffers(1, &mRendererID);
  glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLvertexBuffer::~OpenGLvertexBuffer() {
  glDeleteBuffers(GL_ARRAY_BUFFER, &mRendererID);
}

void OpenGLvertexBuffer::bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
}

void OpenGLvertexBuffer::unbind() const {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//////////////////////////////////////////////////////////
// Index Buffer //////////////////////////////////////////
//////////////////////////////////////////////////////////

OpenGLindexBuffer::OpenGLindexBuffer(uint32_t *indices, uint32_t count) : mCount(count) {

  glGenBuffers(1, &mRendererID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

OpenGLindexBuffer::~OpenGLindexBuffer() {
  glDeleteBuffers(1, &mRendererID);
}

void OpenGLindexBuffer::bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
}

void OpenGLindexBuffer::unbind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

}  // namespace Engine
