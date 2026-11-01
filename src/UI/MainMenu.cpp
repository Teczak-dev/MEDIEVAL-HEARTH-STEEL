#include "UI/MainMenu.hpp"
#include "raylib.h"

void DrawMainMenu(const int &screenWidth, const int &screenHeight) {
  DrawText("Medieval Hearth & Steel", screenWidth / 2 - 200,
           screenHeight / 2 - 100, 48, GOLD);
  DrawText("Press ENTER to start the game", screenWidth / 2 - 200,
           screenHeight / 2, 24, RAYWHITE);
  DrawText("Press Q to exit", screenWidth / 2 - 100, screenHeight / 2 + 50, 24,
           RAYWHITE);
}
