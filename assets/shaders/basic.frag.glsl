#version 330 core

in vec2 v_texCoord;

layout(location = 0) out vec4 o_color;

uniform sampler2D u_texture;

void main(void) {
  o_color = texture(u_texture, v_texCoord);
}
