#version 460 core

in vec3 Position;

out vec4 FragColor;

void main() {
  FragColor = vec4(Position * 0.5 + 0.5, 1.0);
}
