#pragma once
#include "imgui_impl_glfw.h"
#include <string>
namespace window {

class GLwindow {

public:
  bool init(int width, int height, std::string title);
  bool isRunning();
  void render();

  void setNativeWindow(void *window) { mWindow = (GLFWwindow *)window; }

  void onRezise();

  void onClose();

  int height;
  int width;
  std::string title;

private:
  GLFWwindow *mWindow;
  bool mIsRunning;
};

}  // namespace window
