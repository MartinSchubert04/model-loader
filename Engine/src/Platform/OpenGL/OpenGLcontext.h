#pragma once
#include "Renderer/GraphicsContext.h"
#include "pch.h"
namespace Engine {

class OpenGLcontext : public GraphicsContext {

public:
  OpenGLcontext(GLFWwindow *windowHandle);

  void init() override;
  void swapBuffers() override;

private:
  GLFWwindow *mWindowHandle;
};

}  // namespace Engine
