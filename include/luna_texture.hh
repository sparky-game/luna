#pragma once

#include <string>
#include <cstdint>

namespace luna::objs {
  class Texture {
    uint32_t m_id;
    std::string m_name;
    uint8_t *m_buffer;
    uint32_t m_width;
    uint32_t m_height;
    uint32_t m_bpp;
  public:
    Texture(const std::string &name);
    ~Texture(void);
    void bind(uint32_t slot = 0) const;
    void unbind(void) const;
    inline uint32_t getWidth(void) const { return m_width; }
    inline uint32_t getHeight(void) const { return m_height; }
  };
}
