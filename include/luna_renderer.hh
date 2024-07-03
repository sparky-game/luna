#pragma once

#include "luna_vao.hh"
#include "luna_ibo.hh"
#include "luna_shader.hh"

namespace luna {
  class Renderer {
  public:
    void clear(void) const;
    void draw(const objs::VAO &vao, const objs::IBO &ibo, const objs::Shader &shader) const;
  };
}
