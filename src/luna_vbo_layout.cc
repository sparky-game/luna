#include <luna_debug.hh>
#include <luna_vbo_layout.hh>

extern "C" {
#include <GL/glew.h>
}

namespace luna::objs {
  template <>
  consteval uint32_t VBOLayoutElement::gl_type<float>(void) { return GL_FLOAT; }

  template <>
  consteval uint32_t VBOLayoutElement::gl_type<uint32_t>(void) { return GL_UNSIGNED_INT; }

  template <>
  consteval uint32_t VBOLayoutElement::gl_type<uint8_t>(void) { return GL_UNSIGNED_BYTE; }

  template <typename T>
  consteval uint8_t VBOLayoutElement::is_normalized(void) { return GL_FALSE; }

  template <>
  consteval uint8_t VBOLayoutElement::is_normalized<uint8_t>(void) { return GL_TRUE; }

  size_t VBOLayoutElement::gl_size(uint32_t type) {
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
    m_elements.push_back({ VBOLayoutElement::gl_type<T>(), count, VBOLayoutElement::is_normalized<T>() });
    m_stride += count * VBOLayoutElement::gl_size(VBOLayoutElement::gl_type<T>());
  }

  template void VBOLayout::push<float>(uint32_t count);
  template void VBOLayout::push<uint32_t>(uint32_t count);
  template void VBOLayout::push<uint8_t>(uint32_t count);
}
