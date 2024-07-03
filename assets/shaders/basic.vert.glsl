#version 330 core

layout(location = 0) in vec4 i_position;
layout(location = 1) in vec2 i_texCoord;

out vec2 v_texCoord;

void main(void) {
  gl_Position = i_position;
  v_texCoord = i_texCoord;
}
