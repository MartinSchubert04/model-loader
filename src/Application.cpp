#include "Application.h"

Application::Application(const std::string &app_name) {
  mWindow = std::make_unique<window::GLwindow>();
  mWindow->init(1024, 720, app_name);
}

void Application::start() {
  while (mWindow->isunning()) {
    mWindowm->render();
  }
}
