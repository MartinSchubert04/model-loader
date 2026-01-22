#include "Application.h"
#include "Assert.h"
#include "Core/Application.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "Renderer/Buffer.h"
#include "imgui.h"
#include "pch.h"
#include "Core/Base.h"
#include "Core/Log.h"
#include "Core/Input.h"
#include "Editor/src/EditorLayer.h"
#include "Core/Shader.h"
#include <cstdint>
namespace Engine {

Application *Application::s_instance = nullptr;

Application::Application() {

  CORE_ASSERT(!s_instance, "Error: Application instance already exists");
  s_instance = this;

  mWindow = Scope<Window>(Window::create());
  mWindow->setEventCallback(BIND_FN(Application ::onEvent));

  mImGuiLayer = new ImGuiLayer;
  pushOverlay(mImGuiLayer);

  glGenVertexArrays(1, &mVAO);
  glBindVertexArray(mVAO);

  // std::vector<float> vertices = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5, 0.0f, 0.0f, 0.5f, 0.0f};
  float vertices[3 * 3] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5, 0.0f, 0.0f, 0.5f, 0.0f};
  unsigned int indices[3] = {0, 1, 2};

  vb = VertexBuffer::create(vertices, sizeof(vertices));
  ib = IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t));

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
}

Application::~Application() {}

void Application::run() {
  CORE_INFO("App running");

  CORE_INFO("OpenGL version: {0}", (const char *)glGetString(GL_VERSION));
  CORE_INFO("Vendor: {0}", (const char *)glGetString(GL_VENDOR));
  CORE_INFO("Renderer: {0}", (const char *)glGetString(GL_RENDERER));
  CORE_INFO("GLSL verson: {0}", (const char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
  CORE_INFO("GLFW version: {0}", glfwGetVersionString());

  Shader shader("Sim/Assets/shaders/triangle.vs", "Sim/Assets/shaders/triangle.fs");

  while (mRunning) {
    glClearColor(.2, .2, .2, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.use();

    glBindVertexArray(mVAO);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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
