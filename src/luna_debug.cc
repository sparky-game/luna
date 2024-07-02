#include <luna_debug.hh>

#ifdef DEBUG

extern "C" {
#include <GL/glew.h>
}

namespace luna::debug {
  void glClearError(void) {
    while (glGetError() != GL_NO_ERROR);
  }

  bool glLogCall(const char *func, const char *file, int32_t line) {
    while (GLenum err = glGetError()) {
      std::cerr << "ERROR: `glCheckError` (" << file << ":" << line << "::" << func << ") -> " << err << std::endl;
      return false;
    }
    return true;
  }
}

#endif
