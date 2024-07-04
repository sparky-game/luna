#pragma once

#include "luna_vao.hh"
#include "luna_ibo.hh"
#include "luna_shader.hh"

typedef struct GLFWwindow GLFWwindow;

namespace luna {
  class Renderer {
    std::string m_name;
    uint32_t m_width;
    uint32_t m_height;
    GLFWwindow *m_window;
  public:
    Renderer(const std::string &name, uint32_t width, uint32_t height);
    ~Renderer(void);
    bool is_running(void) const;
    void poll_events(void) const;
    void clear(void) const;
    void draw(const objs::VAO &vao, const objs::IBO &ibo, const objs::Shader &shader) const;
    void present(void) const;
  };
}
