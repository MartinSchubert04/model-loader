#version 460 core
layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec4 a_Color;

out vec3 Position;
out vec4 Color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  Position = a_Pos;
  Color = a_Color;

  gl_Position = projection * view * model * vec4(a_Pos, 1.0);
}
