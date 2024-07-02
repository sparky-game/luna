#pragma once

#include <cstdint>

namespace luna::objs {
  class IBO {
    uint32_t m_id;
    uint32_t m_count;
  public:
    IBO(const uint32_t *data, uint32_t count);
    ~IBO(void);
    void bind(void) const;
    void unbind(void) const;
  };
}
