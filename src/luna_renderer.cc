#include <iostream>
#include <luna_debug.hh>
#include <luna_renderer.hh>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

extern "C" {
#include <GL/glew.h>
#include <GLFW/glfw3.h>
}

static constexpr auto luna_version { "v0.1-alpha" };
static constexpr auto glsl_version { "#version 330" };

namespace luna {
  Renderer::Renderer(const std::string &name, uint32_t width, uint32_t height, bool debug)
    : m_name{name}, m_width{width}, m_height{height}, m_debug{debug}, m_window{nullptr}
  {
    if (not glfwInit()) throw std::runtime_error { "ERROR: `glfwInit` failed" };
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_window = glfwCreateWindow(m_width, m_height, m_name.c_str(), nullptr, nullptr);
    if (not m_window) {
      glfwTerminate();
      throw std::runtime_error { "ERROR: `glfwCreateWindow` failed" };
    }
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);
    if (glewInit() != GLEW_OK) {
      glfwDestroyWindow(m_window);
      glfwTerminate();
      throw std::runtime_error { "ERROR: `glewInit` failed" };
    }
    GL_CHECK(glEnable(GL_BLEND));
    GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    if (m_debug) ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    std::cout << "*** BSD Luna (" << luna_version << ") ***" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "ImGui version:   " << IMGUI_VERSION << " (" << IMGUI_VERSION_NUM << ")" << std::endl;
    std::cout << "GLFW version:    " << glfwGetVersionString() << std::endl;
    std::cout << "GLEW version:    " << glewGetString(GLEW_VERSION) << std::endl;
    std::cout << "OpenGL vendor:   " << GL_CHECK(glGetString(GL_VENDOR)) << std::endl;
    std::cout << "OpenGL renderer: " << GL_CHECK(glGetString(GL_RENDERER)) << std::endl;
    std::cout << "OpenGL version:  " << GL_CHECK(glGetString(GL_VERSION)) << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "Running config:  " << (m_debug ? "DEBUG (Editor mode)" : "RELEASE (Runtime mode)") << std::endl;
    std::cout << "---------------------------------------" << std::endl;
  }

  Renderer::~Renderer(void) {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(m_window);
    glfwTerminate();
  }

  bool Renderer::is_running(void) const {
    return not glfwWindowShouldClose(m_window);
  }

  void Renderer::prepare(void) const {
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    if (m_debug) {
      ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
      if (glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS             &&
          (glfwGetKey(m_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS ||
           glfwGetKey(m_window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)) glfwSetWindowShouldClose(m_window, true);
      if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
          if (ImGui::MenuItem("Exit (Ctrl+Q)")) glfwSetWindowShouldClose(m_window, true);
          ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
      }
    }
  }

  void Renderer::clear(void) const {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
  }

  void Renderer::draw(const objs::VAO &vao, const objs::IBO &ibo, objs::Shader &shader) const {
    shader.bind();
    vao.bind();
    ibo.bind();
    GL_CHECK(glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, nullptr));
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

  void Renderer::present(void) const {
    glfwSwapBuffers(m_window);
  }
}
