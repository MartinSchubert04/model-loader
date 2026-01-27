#pragma once
#include <Engine.h>

class ApplicationLayer : public Engine::Layer {

public:
  ApplicationLayer();

  void onUpdate(Engine::DeltaTime dt) override;
  void onEvent(Engine::Event &e) override;

  bool onKeyPressdEvent(Engine::KeyPressedEvent &e);
  void close();

private:
  Engine::Scope<Engine::Shader> mShader;
  Engine::Ref<Engine::VertexArray> vertexArray;
  Engine::Ref<Engine::VertexBuffer> vertexBuffer;
  Engine::Ref<Engine::IndexBuffer> indexBuffer;
  Engine::Scope<Engine::Camera> mCamera;
};
