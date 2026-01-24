#include "OpenGLcontext.h"
#include "GLFW/glfw3.h"
#include "pch.h"

namespace Engine {

OpenGLcontext::OpenGLcontext(GLFWwindow *windowHandle) : mWindowHandle(windowHandle) {
  CORE_ASSERT(windowHandle, "Window handle is nullptr");
}

void OpenGLcontext::init() {
  glfwMakeContextCurrent(mWindowHandle);
  int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  CORE_ASSERT(success, "Failed to load GLAD context");
}

void OpenGLcontext::swapBuffers() {
  glfwSwapBuffers(mWindowHandle);
}

}  // namespace Engine
