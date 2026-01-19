#pragma once
#include "Core/Layer.h"
#include "Engine/ImGui/ImGuiLayer.h"

namespace Engine {

class EditorLayer : public Layer {

public:
  EditorLayer();
  virtual ~EditorLayer() = default;

  void onAttach() override;
  void onDetach() override;
  void onUpdate() override;
  void onImGuiRender() override;
  void onEvent(Event &event) override;

private:
};
}  // namespace Engine
