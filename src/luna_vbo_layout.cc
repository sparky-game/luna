#include <luna_debug.hh>
#include <luna_vbo_layout.hh>

extern "C" {
#include <GL/glew.h>
}

namespace luna::objs {
  size_t VBOLayoutElement::size(uint32_t type) {
    switch (type) {
    case GL_FLOAT:         return sizeof(GLfloat);
    case GL_UNSIGNED_INT:  return sizeof(GLuint);
    case GL_UNSIGNED_BYTE: return sizeof(GLbyte);
    }
    return 0;
  }

  VBOLayout::VBOLayout(void) : m_stride{0} {}

  template <typename T>
  void VBOLayout::push(uint32_t count) {
    static_cast<void>(count);
    static_assert(false);
  }

  template <>
  void VBOLayout::push<float>(uint32_t count) {
    m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
    m_stride += count * VBOLayoutElement::size(GL_FLOAT);
  }

  template <>
  void VBOLayout::push<uint32_t>(uint32_t count) {
    m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
    m_stride += count * VBOLayoutElement::size(GL_UNSIGNED_INT);
  }

  template <>
  void VBOLayout::push<uint8_t>(uint32_t count) {
    m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
    m_stride += count * VBOLayoutElement::size(GL_UNSIGNED_BYTE);
  }
}
