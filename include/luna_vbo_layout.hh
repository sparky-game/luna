#pragma once

#include <vector>
#include <cstdint>

namespace luna::objs {
  struct VBOLayoutElement {
    uint32_t type;
    uint32_t count;
    uint8_t normalized;
    static std::size_t size(uint32_t type);
  };

  class VBOLayout {
    std::vector<VBOLayoutElement> m_elements;
    uint32_t m_stride;
  public:
    VBOLayout(void);
    template <typename T>
    void push(uint32_t count);
    const std::vector<VBOLayoutElement> &getElements(void) const { return m_elements; }
    uint32_t getStride(void) const { return m_stride; }
  };
}
