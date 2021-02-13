#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <cstdio>

#include "imgui_impl/imgui_impl_opengl3.h"
#include "imgui_impl/imgui_impl_glfw.h"

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

int main(int argc, char **argv)
{
  //init GLFW
  if (!glfwInit())
  {
    std::printf("GLFW initialisation failed!");
    glfwTerminate();
    return 1;
  }

  const char *glsl_version = "#version 330";
  //Setup GLFW window properties
  //OpenGL version (using 3.3)
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  //Core Profile = No Backwards Compatibility
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  //Allow forward compatibility
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);

  if (!window)
  {
    std::printf("GLFW window creation failed!");
    glfwTerminate();
    return 1;
  }

  //Set context for GLEW to use
  glfwMakeContextCurrent(window);

  //Allow modern extension features
  glewExperimental = GL_TRUE;

  if (glewInit() != GLEW_OK)
  {
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
  ImGui_ImplOpenGL3_Init(glsl_version);

  while (!glfwWindowShouldClose(window))
  {
    //Get + Handle user input events
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Begin UI
    /* ImGui::Begin("Hello World");
     * ImGui::Button("Push Me If You Can");
     * ImGui::End();
     */ 
    // End UI

    ImGui::EndFrame();
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);

    //Clear window
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //draw here
    /* 
    * 
    *
    *
    * 
    */
    //end draw
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
