#pragma once
#include "Renderer/||.h"

namespace Engine {

class RendererAPI {

public:
  virtual void drawLines(VertexArray vertexArray, unsigned int vertexCount);

  virtual void drawArray(VertexArray vertexArray, unsigned int arrayIndices);
};

}  // namespace Engine
