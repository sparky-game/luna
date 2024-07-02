#pragma once

#include <string>
#include <cstdint>

namespace luna::objs {
  class Shader {
    uint32_t m_id;
    std::string m_name;
    std::string read(const std::string &name);
    uint32_t compile(uint32_t type, const std::string &src);
    uint32_t build(const std::string &vs_src, const std::string &fs_src);
    uint32_t getUniformLoc(const std::string &name);
  public:
    Shader(const std::string &name);
    ~Shader(void);
    void bind(void) const;
    void unbind(void) const;
    void setUniform4f(const std::string &name, float f0, float f1, float f2, float f3);
  };
}
