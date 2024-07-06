#pragma once

#include <imgui.h>
#include "luna_vao.hh"
#include "luna_ibo.hh"
#include "luna_shader.hh"

typedef struct GLFWwindow GLFWwindow;

namespace luna {
  class Renderer {
    std::string m_name;
    uint32_t m_width;
    uint32_t m_height;
    bool m_debug;
    GLFWwindow *m_window;
  public:
    Renderer(const std::string &name, uint32_t width, uint32_t height, bool debug = false);
    ~Renderer(void);
    bool is_running(void) const;
    void prepare(void) const;
    void clear(void) const;
    void draw(const objs::VAO &vao, const objs::IBO &ibo, objs::Shader &shader) const;
    void present(void) const;
  };
}
