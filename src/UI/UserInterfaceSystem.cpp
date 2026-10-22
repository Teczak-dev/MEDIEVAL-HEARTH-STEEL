#include "UI/UserInterfaceSystem.hpp"
#include "raylib.h"

UserInterfaceSystem::UserInterfaceSystem() {}
UserInterfaceSystem::~UserInterfaceSystem() {}

void UserInterfaceSystem::Update(float deltaTime) {
  // LOGIC
}

void UserInterfaceSystem::Render(int screenWidth, int screenHeight,
                                 int playerHealth) {
  // UPPER LEFT CORNER
  DrawRectangle(10, 10, 280, 80, Fade(BLACK, 0.6f));
  DrawRectangleLines(10, 10, 280, 80, GOLD);
  DrawText("Medieval Hearth & Steel", 20, 20, 18, GOLD);
  DrawFPS(20, 65);

  // BOTTOM LEFT CORNER ( PLAYER HEALTH BAR )
  DrawRectangle(5, screenHeight - 55, 210, 40, BLACK);
  DrawRectangle(10, screenHeight - 50, playerHealth * 2, 30, RED);

  // BOTTOM CENTER
  DrawText("Work in progress...", screenWidth / 2 - 100, screenHeight - 20, 16,
           RAYWHITE);
}
