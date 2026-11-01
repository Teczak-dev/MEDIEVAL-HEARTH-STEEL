#include "UI/HUD.hpp"

void DrawHUD(const int &screenWidth, const int &screenHeight, int playerHealth,
             Vector2 playerPosition) {
  // Upper-left corner
  DrawRectangle(10, 10, 280, 80, Fade(BLACK, 0.6f));
  DrawRectangleLines(10, 10, 280, 80, GOLD);
  DrawText("Medieval Hearth & Steel", 20, 20, 18, GOLD);
  DrawFPS(20, 65);

  // Bottom-left corner: player health bar
  DrawRectangle(5, screenHeight - 55, 210, 40, BLACK);
  DrawRectangle(10, screenHeight - 50, playerHealth * 2, 30, RED);

  // Bottom-center status text
  DrawText("Work in progress...", screenWidth / 2 - 100, screenHeight - 20, 16,
           RAYWHITE);
}
