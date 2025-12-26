#pragma once

#include "window/Window.h"
#include "elements/Vertex.h"

namespace render {

class RenderContext {

public:
  RenderContext() : mWindow(nullptr) {}

  virtual bool init(window::Iwindow *window) {
    mWindow = window;
    return true;
  }

  virtual void preRender() = 0;
  virtual void postRender() = 0;
  virtual void end() = 0;

protected:
  window::Iwindow *mWindow;
};

class VertexIndexBuffer {

private:
  unsigned int mRedererID;
  unsigned int mVAO, mVBO, mEBO;

public:
  VertexIndexBuffer(const std::vector<Vertex> &vertices,
                    const std::vector<unsigned int> &indices);
  ~VertexIndexBuffer();

  virtual void bind() const = 0;
  virtual void unbind() const = 0;
};

class FrameBuffer {};

}  // namespace render
