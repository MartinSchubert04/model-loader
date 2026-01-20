#include "WindowsInput.h"
#include "Core/Application.h"
#include "GLFW/glfw3.h"

namespace Engine {

Scope<Input> Input::s_Instance = createScope<WindowsInput>();

bool WindowsInput::isKeyPressedImpl(KeyCode keycode) {
  // static cast is needed because window class return a void *
  auto window = static_cast<GLFWwindow *>(Application::get().getWindow().getNativeWindow());

  auto state = glfwGetKey(window, keycode);

  return state == GLFW_PRESS || state == GLFW_REPEAT;  // check if key is hold down in any way
}

bool WindowsInput::isMouseButtonPressedImpl(MouseCode keycode) {
  // static cast is needed because window class return a void *
  auto window = static_cast<GLFWwindow *>(Application::get().getWindow().getNativeWindow());

  auto state = glfwGetMouseButton(window, keycode);

  return state == GLFW_PRESS;
}

glm::vec2 WindowsInput::getMousePosImpl() {
  auto window = static_cast<GLFWwindow *>(Application::get().getWindow().getNativeWindow());

  double xpos, ypos;

  glfwGetCursorPos(window, &xpos, &ypos);

  return {xpos, ypos};
}

float WindowsInput::getMouseXImpl() {
  return getMousePosImpl().x;
}
float WindowsInput::getMouseYImpl() {
  return getMousePosImpl().y;
}

}  // namespace Engine
