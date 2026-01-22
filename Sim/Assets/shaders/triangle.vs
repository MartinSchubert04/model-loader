#version 460 core
layout(location = 0) in vec3 a_Pos;

out vec3 Position;

void main() {
  Position = a_Pos;
  gl_Position = vec4(a_Pos, 1.0);
}
