#pragma once

#include <cstdint>

namespace luna::objs {
  class VBO {
    uint32_t m_id;
  public:
    VBO(const void *data, std::size_t size);
    ~VBO(void);
    void bind(void) const;
    void unbind(void) const;
  };
}
