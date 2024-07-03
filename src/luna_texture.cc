#include <luna_debug.hh>
#include <luna_texture.hh>

extern "C" {
#include <GL/glew.h>
#include <stb_image.h>
}

namespace luna::objs {
  Texture::Texture(const std::string &name) : m_id{0}, m_name{name}, m_buffer{nullptr}, m_width{0}, m_height{0}, m_bpp{0} {
    stbi_set_flip_vertically_on_load(1);
    m_buffer = stbi_load(("assets/textures/" + name + ".png").c_str(), (int32_t *) &m_width, (int32_t *) &m_height, (int32_t *) &m_bpp, 4);
    GL_CHECK(glGenTextures(1, &m_id));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_id));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_buffer));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
    if (m_buffer) stbi_image_free(m_buffer);
  }

  Texture::~Texture(void) {
    GL_CHECK(glDeleteTextures(1, &m_id));
  }

  void Texture::bind(uint32_t slot) const {
    GL_CHECK(glActiveTexture(GL_TEXTURE0 + slot));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_id));
  }

  void Texture::unbind(void) const {
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
  }
}
