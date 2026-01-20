#include "Application.h"
#include "Assert.h"
#include "Core/Application.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "imgui.h"
#include "pch.h"
#include "Core/Base.h"
#include "Core/Log.h"
#include "Core/Input.h"
#include "Editor/src/EditorLayer.h"
namespace Engine {

Application *Application::s_instance = nullptr;

Application::Application() {

  CORE_ASSERT(!s_instance, "Error: Application instance already exists");
  s_instance = this;

  mWindow = Scope<Window>(Window::create());
  mWindow->setEventCallback(BIND_FN(Application ::onEvent));

  mImGuiLayer = new ImGuiLayer;
  pushOverlay(mImGuiLayer);
}

Application::~Application() {}

void Application::run() {
  CORE_INFO("App running");
  const GLubyte *versionGL = glGetString(GL_VERSION);  // Get the version string
  const GLubyte *vendor = glGetString(GL_VENDOR);
  const GLubyte *renderer = glGetString(GL_RENDERER);
  const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

  CORE_INFO("OpenGL version: {0}, vendor: {1}, renderer: {2}, glslVersion: {3}", (const char *)versionGL,
            (const char *)vendor, (const char *)renderer, (const char *)glslVersion);
  CORE_INFO("GLFW version: {0}", glfwGetVersionString());

  while (mRunning) {
    glClearColor(.2, .2, .2, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    for (Layer *layer : mLayerStack)
      layer->onUpdate();

    mImGuiLayer->begin();
    for (Layer *layer : mLayerStack)
      layer->onImGuiRender();
    mImGuiLayer->end();

    mWindow->onUpdate();
  }
}

void Application::pushLayer(Layer *layer) {
  mLayerStack.pushLayer(layer);
  layer->onAttach();
}

void Application::pushOverlay(Layer *layer) {
  mLayerStack.pushOverlay(layer);
  layer->onAttach();
}

void Application::onEvent(Event &e) {

  EventDispatcher dispatcher(e);

  dispatcher.dispatch<WindowCloseEvent>(BIND_FN(Application::onWindowClose));

  if (e.getEventType() != EventType::MouseMoved)
    CORE_TRACE("{0}", e.toString());

  for (auto it = mLayerStack.end(); it != mLayerStack.begin();) {
    (*--it)->onEvent(e);
    if (e.handled)
      break;
  }
}

bool Application::onWindowClose(WindowCloseEvent &e) {
  mRunning = false;
  return true;
}

bool Application::onWindowResize(WindowResizeEvent &e) {
  glViewport(0, 0, e.getWidth(), e.getHeight());
  return true;
}

}  // namespace Engine
