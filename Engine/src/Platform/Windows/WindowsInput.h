#pragma once
#include "Core/Input.h"
#include "Events/MouseCodes.h"

namespace Engine {
class WindowsInput : public Input {

protected:
  bool isKeyPressedImpl(KeyCode keycode) override;
  bool isMouseButtonPressedImpl(MouseCode keycode) override;
  glm::vec2 getMousePosImpl() override;
  float getMouseXImpl() override;
  float getMouseYImpl() override;
};
}  // namespace Engine
