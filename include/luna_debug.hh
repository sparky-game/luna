#pragma once

#ifdef DEBUG
#define GL_ASSERT(x) (if (!(x)) __builtin_trap())
#define GL_CHECK(x) (do { glClearError(); (x); GL_ASSERT(glLogCall(#x, __FILE__, __LINE__)) } while (0))

namespace luna::debug {
  void glClearError(void);

  bool glLogCall(const char *func, const char *file, int32_t line);
}

#else
#define GL_CHECK(x) (x)
#endif
