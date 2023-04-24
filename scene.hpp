#pragma once

namespace Scene {
constexpr bool HasUI = false;

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
