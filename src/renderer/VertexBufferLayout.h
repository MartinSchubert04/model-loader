#pragma once

#include "common.h"
#include "Render.h"

struct VertexBufferElement {
  unsigned int type;
  unsigned int count;
  const char normalized;

  static unsigned int getSizeOf(unsigned int type) {
    switch (type) {
    case GL_FLOAT:
      return 4;
    case GL_UNSIGNED_INT:
      return 4;
    case GL_UNSIGNED_BYTE:
      return 1;
    }

    ASSERT(false);
    return 0;
  }
};

class VertexBufferLayout {
private:
  std::vector<VertexBufferElement> mElements;
  unsigned int mStride;

public:
  VertexBufferLayout();

  template <typename T>
  void push(unsigned int count) {
    static_assert(false);
  }

  template <>
  void push<float>(unsigned int count) {
    mElements.push_back({GL_FLOAT, count, GL_FALSE});
    mStride += count * VertexBufferElement::getSizeOf(GL_FLOAT);
  }

  template <>
  void push<unsigned int>(unsigned int count) {
    mElements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    mStride += count * VertexBufferElement::getSizeOf(GL_UNSIGNED_INT);
  }

  template <>
  void push<unsigned char>(unsigned int count) {
    mElements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
    mStride += count * VertexBufferElement::getSizeOf(GL_UNSIGNED_BYTE);
  }

  inline const std::vector<VertexBufferElement> getElements() const & {
    return mElements;
  };
  inline const unsigned int getStride() const { return mStride; }
};
