#include "Core/Game.hpp"
#include "raylib.h"

int main() {
  Game game;
  InitWindow(game.GetScreenWidth(), game.GetScreenHeight(),
             "MEDIEVAL HEARTH & STEEL - Prototype");
  if (!IsWindowReady()) {
    TraceLog(LOG_ERROR, "Could not create the application window");
    return 1;
  }

  SetTargetFPS(60);

  // turn off the default exit key (ESC) to avoid closing the window when
  // pressing ESC
  SetExitKey(KEY_NULL);

  while (!WindowShouldClose()) {
    float deltaTime = GetFrameTime();
    game.Update(deltaTime);
    game.Draw();
  }

  CloseWindow();
  return 0;
}
