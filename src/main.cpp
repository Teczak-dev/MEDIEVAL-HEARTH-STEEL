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
  game.LoadAssets();

  SetTargetFPS(60);
  SetExitKey(KEY_NULL);

  while (!WindowShouldClose() && !game.IsExitRequested()) {
    float deltaTime = GetFrameTime();
    game.Update(deltaTime);
    game.Draw();
  }

  game.Shutdown();
  CloseWindow();
  return 0;
}
