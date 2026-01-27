#pragma once
#include <Engine.h>

class ApplicationLayer : public Engine::Layer {

public:
  ApplicationLayer();

  void onUpdate(Engine::DeltaTime dt) override;
  void onEvent(Engine::Event &e) override;

  bool onKeyPressedEvent(Engine::KeyPressedEvent &e);
  bool onMouseMoved(Engine::MouseMovedEvent &event);

private:
  void close();

private:
  Engine::Ref<Engine::Shader> mShader;
  Engine::Ref<Engine::VertexArray> vertexArray;
  Engine::Ref<Engine::VertexBuffer> vertexBuffer;
  Engine::Ref<Engine::IndexBuffer> indexBuffer;
  Engine::Scope<Engine::Camera> mCamera;
};
