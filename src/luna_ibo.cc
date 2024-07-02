#include <luna_ibo.hh>
#include <luna_debug.hh>

extern "C" {
#include <GL/glew.h>
}

namespace luna::objs {
  IBO::IBO(const uint32_t *data, uint32_t count) : m_count{count} {
    GL_CHECK(glGenBuffers(1, &m_id));
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(uint32_t), data, GL_STATIC_DRAW));
  }

  IBO::~IBO(void) {
    GL_CHECK(glDeleteBuffers(1, &m_id));
  }

  void IBO::bind(void) const {
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
  }

  void IBO::unbind(void) const {
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
  }
}
