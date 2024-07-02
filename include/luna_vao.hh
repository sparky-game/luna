#pragma once

#include "luna_vbo.hh"
#include "luna_vbo_layout.hh"

namespace luna::objs {
  class VAO {
    uint32_t m_id;
  public:
    VAO(void);
    ~VAO(void);
    void bind(void) const;
    void unbind(void) const;
    void add_vbo(const VBO &vbo, const VBOLayout &layout);
  };
}
