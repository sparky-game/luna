#include <luna_vao.hh>
#include <luna_debug.hh>

extern "C" {
#include <GL/glew.h>
}

namespace luna::objs {
  VAO::VAO(void) {
    GL_CHECK(glGenVertexArrays(1, &m_id));
  }

  VAO::~VAO(void) {
    GL_CHECK(glDeleteVertexArrays(1, &m_id));
  }

  void VAO::bind(void) const {
    GL_CHECK(glBindVertexArray(m_id));
  }

  void VAO::unbind(void) const {
    GL_CHECK(glBindVertexArray(0));
  }

  void VAO::add_vbo(const VBO &vbo, const VBOLayout &layout) {
    bind();
    vbo.bind();
    const auto &elements { layout.getElements() };
    uint32_t offset {0};
    for (size_t i = 0; i < elements.size(); ++i) {
      const auto &element { elements[i] };
      GL_CHECK(glEnableVertexAttribArray(i));
      GL_CHECK(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void *) (uintptr_t) offset));
      offset += element.count * VBOLayoutElement::gl_size(element.type);
    }
  }
}
