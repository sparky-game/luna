#pragma once

#include <vector>
#include <cstdint>

namespace luna::objs {
  struct VBOLayoutElement {
    uint32_t type;
    uint32_t count;
    uint8_t normalized;
    template <typename T>
    static consteval uint32_t gl_type(void);
    template <typename T>
    static consteval uint8_t is_normalized(void);
    static std::size_t gl_size(uint32_t type);
  };

  class VBOLayout {
    std::vector<VBOLayoutElement> m_elements;
    uint32_t m_stride;
  public:
    VBOLayout(void);
    template <typename T>
    void push(uint32_t count);
    inline const std::vector<VBOLayoutElement> &getElements(void) const { return m_elements; }
    inline uint32_t getStride(void) const { return m_stride; }
  };
}
