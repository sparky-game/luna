#version 330 core

layout(location = 0) out vec4 o_color;

uniform vec4 u_color;

void main(void) {
  o_color = u_color;
}
