#pragma once
#include "Core/Assert.h"
#include <pch.h>

namespace Engine {
namespace Types {

enum class ShaderDataType : uint8_t {

  None = 0,
  float1,
  float2,
  float3,
  float4,
  int1,
  int2,
  int3,
  int4,
  boolean,
  mat3,
  mat4

};

static uint32_t ShaderDataTypeSize(ShaderDataType type) {

  switch (type) {
  case ShaderDataType::float1:
    return 4;
  case ShaderDataType::float2:
    return 4 * 2;
  case ShaderDataType::float3:
    return 4 * 3;
  case ShaderDataType::float4:
    return 4 * 4;
  case ShaderDataType::int1:
    return 4;
  case ShaderDataType::int2:
    return 4 * 2;
  case ShaderDataType::int3:
    return 4 * 3;
  case ShaderDataType::int4:
    return 4 * 4;
  case ShaderDataType::boolean:
    return 1;
  case ShaderDataType::mat3:
    return 4 * 3 * 3;
  case ShaderDataType::mat4:
    return 4 * 4 * 4;
  }

  CORE_ASSERT(false, "Unkown shader data type");
  return 0;
}

}  // namespace Types
}  // namespace Engine
