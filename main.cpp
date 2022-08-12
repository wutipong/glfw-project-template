#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <glm/glm.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

constexpr int WindowWidth = 800;
constexpr int WindowHeight = 600;

constexpr int GlMajorVersion = 3;
constexpr int GlMinorVersion = 3;
constexpr char GlslVersion[] = "#version 330";

constexpr glm::vec4 ClearColor = {0.33f, 0.67f, 1.0f, 1.0f};

int main(int argc, char **argv) {
  if (!glfwInit()) {
    std::printf("GLFW initialisation failed!");
    glfwTerminate();
    return 1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GlMajorVersion);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GlMinorVersion);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow *window = glfwCreateWindow(WindowWidth, WindowHeight,
                                        "glfw-project-template", NULL, NULL);

  if (!window) {
    std::printf("GLFW window creation failed!");
    glfwTerminate();
    return 1;
  }

  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;

  if (glewInit() != GLEW_OK) {
    printf("GLEW initialisation failed!");
    glfwDestroyWindow(window);
    glfwTerminate();
    return 1;
  }

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;

  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(GlslVersion);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Begin UI
    ImGui::Begin("Greetings");
    ImGui::Button("Hello World");
    ImGui::End();
    // End UI

    ImGui::EndFrame();
    ImGui::Render();

    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);

    glClearColor(ClearColor.r, ClearColor.g, ClearColor.b, ClearColor.a);
    glClear(GL_COLOR_BUFFER_BIT);

    // Begin Draw
    /*
     *
     *
     *
     *
     */
    // End Draw

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(window);
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
