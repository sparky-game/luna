#include <luna_vbo.hh>
#include <luna_debug.hh>

extern "C" {
#include <GL/glew.h>
}

namespace luna::objs {
  VBO::VBO(const void *data, std::size_t size) {
    GL_CHECK(glGenBuffers(1, &m_id));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_id));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
  }

  VBO::~VBO(void) {
    GL_CHECK(glDeleteBuffers(1, &m_id));
  }

  void VBO::bind(void) const {
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_id));
  }

  void VBO::unbind(void) const {
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
  }
}
