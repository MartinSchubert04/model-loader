#pragma once

#include <string>
#include "window/window.h"

class Application {

public:
  Window mWindow;
  void start();
  Application(const std::string &name);
};
