#pragma once

#include "common.h"
#include "renderer/openGLrender.h"
#include "renderer/Interface.h"

// #include "renderer/ui_context.h"
// #include "renderer/opengl_context.h"
// #include "renderer/opengl_buffer_manager.h"

using namespace render;

namespace window {

class GLwindow : public Iwindow {

public:
  GLwindow() : mIsRunning(true), mWindow(nullptr) {
    mInterface = std::make_unique<Interface>();
    mRender = std::make_unique<OpenGLrenderer>();
  }

  ~GLwindow();

  bool init(int width, int height, std::string title);
  bool isRunning();
  void render();

  void setNativeWindow(void *window) override {
    mWindow = (GLFWwindow *)window;
  }

  void *getNativeWindow() override { return mWindow; }

  void onScroll(double delta) override;

  void onKey(int key, int scancode, int action, int mods) override;

  void onResize(int width, int height) override;

  void onClose() override;

  bool inRunning() { return mIsRunning; }

  void handleInput();

private:
  GLFWwindow *mWindow;
  bool mIsRunning;

  std::unique_ptr<OpenGLrenderer> mRender;

  std::unique_ptr<Interface> mInterface;

  // std::unique_ptr<Interface> mSceneView;
};

}  // namespace window
