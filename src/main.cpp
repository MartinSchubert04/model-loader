#include "Application.h"
#include <memory>

int main() {
  auto app = std::make_unique<Application>("Model loader");

  app->start();

  return 0;
}
