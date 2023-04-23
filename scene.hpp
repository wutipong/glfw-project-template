#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace Scene {

struct FrameContext {
  const int windowWidth;
  const int windowHeight;
  const double frameTime;
};

void Init();
void CleanUp();
void DoFrame(const FrameContext &ctx);
void DoUI();
} // namespace Scene
