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
  glBegin(GL_TRIANGLES);
  glColor3f(1.0f, 0.0f, 0.0f);  // Rojo
  glVertex2f(-0.5f, -0.5f);

  glColor3f(0.0f, 1.0f, 0.0f);  // Verde
  glVertex2f(0.5f, -0.5f);

  glColor3f(0.0f, 0.0f, 1.0f);  // Azul
  glVertex2f(0.0f, 0.5f);
  glEnd();

  glfwSwapBuffers(mWindowHandle);
}

}  // namespace Engine
