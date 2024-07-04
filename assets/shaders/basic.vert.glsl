#version 330 core

layout(location = 0) in vec4 i_position;
layout(location = 1) in vec2 i_texCoord;

out vec2 v_texCoord;

uniform mat4 u_mvp;

void main(void) {
  gl_Position = u_mvp * i_position;
  v_texCoord = i_texCoord;
}
