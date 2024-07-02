#include <sstream>
#include <fstream>
#include <iostream>
#include <luna_debug.hh>
#include <luna_shader.hh>

extern "C" {
#include <GL/glew.h>
}

namespace luna::objs {
  std::string Shader::read(const std::string &name) {
    std::ifstream ifs { "assets/shaders/" + name + ".glsl" };
    if (!ifs) throw std::runtime_error{ "ERROR: `read_shader_from_file` failed (`" + name + ".glsl`)" };
    std::stringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
  }

  uint32_t Shader::compile(uint32_t type, const std::string &src) {
    uint32_t id = glCreateShader(type);
    const char *src_buf = src.c_str();
    GL_CHECK(glShaderSource(id, 1, &src_buf, nullptr));
    GL_CHECK(glCompileShader(id));
    int32_t result;
    GL_CHECK(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
      int32_t len;
      GL_CHECK(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len));
      char *msg = (char *) alloca(len * sizeof(char));
      GL_CHECK(glGetShaderInfoLog(id, len, &len, msg));
      std::cerr << "ERROR: `compile_shader` [" << (type == GL_VERTEX_SHADER ? "vertex" : "frag") << "] failed" << std::endl;
      std::cerr << msg << std::endl;
      GL_CHECK(glDeleteShader(id));
      return 0;
    }
    return id;
  }

  uint32_t Shader::build(const std::string &vs_src, const std::string &fs_src) {
    uint32_t program = glCreateProgram();
    uint32_t vs = compile(GL_VERTEX_SHADER, vs_src);
    uint32_t fs = compile(GL_FRAGMENT_SHADER, fs_src);
    GL_CHECK(glAttachShader(program, vs));
    GL_CHECK(glAttachShader(program, fs));
    GL_CHECK(glLinkProgram(program));
    GL_CHECK(glValidateProgram(program));
    GL_CHECK(glDeleteShader(vs));
    GL_CHECK(glDeleteShader(fs));
    return program;
  }

  uint32_t Shader::getUniformLoc(const std::string &name) {
    if (m_uniformCache.find(name) != m_uniformCache.end()) return m_uniformCache.at(name);
    int32_t location = glGetUniformLocation(m_id, name.c_str());
    if (location == -1) std::cout << "WARNING: uniform `" << name << "` does not exist" << std::endl;
    m_uniformCache[name] = location;
    return location;
  }

  Shader::Shader(const std::string &name) : m_id{0}, m_name{name} {
    std::string vs_src = read(m_name + ".vert");
    std::string fs_src = read(m_name + ".frag");
    m_id = build(vs_src, fs_src);
  }

  Shader::~Shader(void) {
    GL_CHECK(glDeleteProgram(m_id));
  }

  void Shader::bind(void) const {
    GL_CHECK(glUseProgram(m_id));
  }

  void Shader::unbind(void) const {
    GL_CHECK(glUseProgram(0));
  }

  void Shader::setUniform4f(const std::string &name, float f0, float f1, float f2, float f3) {
    GL_CHECK(glUniform4f(getUniformLoc(name), f0, f1, f2, f3));
  }
}
