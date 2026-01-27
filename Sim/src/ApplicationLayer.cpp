#include "ApplicationLayer.h"
#include "Core/Application.h"
#include "Core/DeltaTime.h"
#include "Core/Input.h"
#include "Core/Log.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "Events/KeyCodes.h"
#include "Events/MouseCodes.h"
#include "Events/MouseEVent.h"
#include "Platform/Windows/WindowsInput.h"
#include <vector>

ApplicationLayer::ApplicationLayer() : Layer("App layer") {

  vertexArray = Engine::VertexArray::create();

  // std::vector<float> vertices = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5, 0.0f, 0.0f, 0.5f, 0.0f};
  float vertices[7 * 3] = {
      -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.5f, -0.5, 0.0f, 1.0f,
      0.0f,  0.0f,  1.0f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
  };
  vertexBuffer = Engine::VertexBuffer::create(vertices, sizeof(vertices));

  // fill layout with buffer elements then gets added to vertex array
  Engine::BufferLayout layout = {
      {Engine::Types::ShaderDataType::float3, "a_Pos"},
      {Engine::Types::ShaderDataType::float4, "a_Color"},
  };

  vertexBuffer->setLayout(layout);
  vertexArray->addVertexBuffer(vertexBuffer);

  std::vector<uint32_t> indices = {0, 1, 2};
  indexBuffer = Engine::IndexBuffer::create(indices);

  vertexArray->setIndexBuffer(indexBuffer);

  mShader = Engine::createScope<Engine::Shader>("Sim/Assets/shaders/triangle.vs", "Sim/Assets/shaders/triangle.fs");
  mCamera = Engine::createScope<Engine::Camera>(glm::vec3(0, 0, 1), 45.0f, 1.3f, 0.1f, 1000);
}

void ApplicationLayer::onUpdate(Engine::DeltaTime dt) {

  Engine::RenderCommand::setClearColor({.2, .2, .2, 1});
  Engine::RenderCommand::clear();

  Engine::Renderer::beginScene();

  mShader->bind();

  Engine::Transform transform;
  transform.setModel(mShader);

  mCamera->update(mShader.get());

  Engine::Renderer::submit(vertexArray);

  Engine::Renderer::endScene();
}

void ApplicationLayer::onEvent(Engine::Event &e) {

  Engine::EventDispatcher dispatcher(e);

  dispatcher.dispatch<Engine::KeyPressedEvent>(BIND_FN(ApplicationLayer::onKeyPressedEvent));
  dispatcher.dispatch<Engine::MouseMovedEvent>(BIND_FN(ApplicationLayer::onMouseMoved));
}

bool ApplicationLayer::onKeyPressedEvent(Engine::KeyPressedEvent &event) {
  if (event.getKeyCode() == Engine::Key::Escape) {
    close();
  }

  return false;
}

bool ApplicationLayer::onMouseMoved(Engine::MouseMovedEvent &event) {
  if (Engine::Input::isMouseButtonPressed(Engine::Mouse::ButtonRight)) {
    mCamera->onMouseMove(event.getX(), event.getY(), Engine::Mouse::ButtonRight);
  }

  return false;
}

void ApplicationLayer::close() {
  Engine::WindowCloseEvent e;
  Engine::Application::get().onEvent(e);
}
