#include "Application.h"
#include "Assert.h"
#include "Core/Application.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "Renderer/Buffer.h"
#include "Renderer/Types.h"
#include "Renderer/VertexArray.h"
#include "pch.h"
#include "Core/Base.h"
#include "Core/Log.h"
#include "Renderer/Renderer.h"

namespace Engine {

Application *Application::s_instance = nullptr;

Application::Application() {

  CORE_ASSERT(!s_instance, "Error: Application instance already exists");
  s_instance = this;

  mWindow = Scope<Window>(Window::create());
  mWindow->setEventCallback(BIND_FN(Application ::onEvent));

  mImGuiLayer = new ImGuiLayer;
  pushOverlay(mImGuiLayer);

  va = VertexArray::create();

  // std::vector<float> vertices = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5, 0.0f, 0.0f, 0.5f, 0.0f};
  float vertices[7 * 3] = {
      -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.5f, -0.5, 0.0f, 1.0f,
      0.0f,  0.0f,  1.0f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
  };
  vb = VertexBuffer::create(vertices, sizeof(vertices));

  // fill layout with buffer elements then gets added to vertex array
  BufferLayout layout = {
      {Types::ShaderDataType::float3, "a_Pos"},
      {Types::ShaderDataType::float4, "a_Color"},
  };

  vb->setLayout(layout);
  va->addVertexBuffer(vb);

  unsigned int indices[3] = {0, 1, 2};
  ib = IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t));

  va->setIndexBuffer(ib);

  mShader = createScope<Shader>("Sim/Assets/shaders/triangle.vs", "Sim/Assets/shaders/triangle.fs");
}

Application::~Application() {}

void Application::run() {
  CORE_INFO("App running");

  CORE_INFO("OpenGL version: {0}", (const char *)glGetString(GL_VERSION));
  CORE_INFO("Vendor: {0}", (const char *)glGetString(GL_VENDOR));
  CORE_INFO("Renderer: {0}", (const char *)glGetString(GL_RENDERER));
  CORE_INFO("GLSL verson: {0}", (const char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
  CORE_INFO("GLFW version: {0}", glfwGetVersionString());

  while (mRunning) {

    RenderCommand::setClearColor({.2, .2, .2, 1});
    RenderCommand::clear();

    Renderer::beginScene();

    mShader->bind();

    Renderer::submit(va);

    Renderer::endScene();

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
