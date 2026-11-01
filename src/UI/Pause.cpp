#include "UI/Pause.hpp"
#include "raylib.h"

void DrawPauseMenu(const int &screenWidth, const int &screenHeight) {
  DrawText("PAUSED", screenWidth / 2 - 100, screenHeight / 2 - 100, 48, GOLD);
  DrawText("Press ESC to resume the game", screenWidth / 2 - 200,
           screenHeight / 2, 24, RAYWHITE);
  DrawText("Press Q to return to the main menu", screenWidth / 2 - 200,
           screenHeight / 2 + 40, 24, RAYWHITE);
}
