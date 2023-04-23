#include "scene.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <glm/glm.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <spdlog/spdlog.h>

constexpr int WindowWidth = 800;
constexpr int WindowHeight = 600;

constexpr int GlMajorVersion = 3;
constexpr int GlMinorVersion = 3;
constexpr char GlslVersion[] = "#version 330";

constexpr char ProjectName[] = "glfw-project-template";

void PrintDeviceInformation();

int main(int argc, char **argv) {
  spdlog::set_level(spdlog::level::debug);

  spdlog::info("{} - starts.", ProjectName);

  if (!glfwInit()) {
    spdlog::error("GLFW initialisation failed!");
    glfwTerminate();
    return 1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GlMajorVersion);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GlMinorVersion);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow *window = glfwCreateWindow(WindowWidth, WindowHeight, ProjectName, NULL, NULL);

  if (!window) {
    spdlog::error("GLFW window creation failed!");
    glfwTerminate();
    return 1;
  }

  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;

  if (glewInit() != GLEW_OK) {
    spdlog::error("GLEW initialisation failed!");
    glfwDestroyWindow(window);
    glfwTerminate();
    return 1;
  }

  PrintDeviceInformation();

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;

  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(GlslVersion);

  Scene::Init();

  auto lastFrame = glfwGetTime();

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    Scene::DoUI();

    ImGui::EndFrame();
    ImGui::Render();

    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);

    auto now = glfwGetTime();
    Scene::DoFrame({
        .windowWidth = display_w,
        .windowHeight = display_h,
        .frameTime = now - lastFrame,
    });

    lastFrame = now;

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(window);
  }

  Scene::CleanUp();

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}

void PrintDeviceInformation() {
  spdlog::info("OpenGL Device Information.");
  spdlog::info("\tOpenGL: {}", reinterpret_cast<const char *>(glGetString(GL_VERSION)));
  spdlog::info("\tGLSL: {}", reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION)));
  spdlog::info("\tDevice: {}", reinterpret_cast<const char *>(glGetString(GL_RENDERER)));
  spdlog::info("\tVendor: {}", reinterpret_cast<const char *>(glGetString(GL_VENDOR)));
  spdlog::info("Supported Extensions:");

  int extCount;
  glGetIntegerv(GL_NUM_EXTENSIONS, &extCount);

  for (int i = 0; i < extCount; i++) {
    spdlog::info("\t{}", reinterpret_cast<const char *>(glGetStringi(GL_EXTENSIONS, i)));
  }
}
