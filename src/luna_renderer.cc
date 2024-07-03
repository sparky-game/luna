#include <luna_debug.hh>
#include <luna_renderer.hh>

extern "C" {
#include <GL/glew.h>
}

namespace luna {
  void Renderer::clear(void) const {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
  }

  void Renderer::draw(const objs::VAO &vao, const objs::IBO &ibo, const objs::Shader &shader) const {
    shader.bind();
    vao.bind();
    ibo.bind();
    GL_CHECK(glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, nullptr));
  }
}
