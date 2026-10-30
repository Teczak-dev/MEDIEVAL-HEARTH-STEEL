#include "UI/UserInterfaceSystem.hpp"
#include "raylib.h"

UserInterfaceSystem::UserInterfaceSystem() {}
UserInterfaceSystem::~UserInterfaceSystem() {}

void UserInterfaceSystem::Update(float deltaTime) {
  // LOGIC
  if (currentState == UI_STATE_MAIN_MENU) {
    if (IsKeyPressed(KEY_ENTER)) {
      currentState = UI_STATE_GAMEPLAY;
    }
    SetExitKey(KEY_Q);
  } else if (currentState == UI_STATE_GAMEPLAY) {
    if (IsKeyPressed(KEY_ESCAPE)) {
      currentState = UI_STATE_PAUSE_MENU;
    }
  } else if (currentState == UI_STATE_PAUSE_MENU) {
    if (IsKeyPressed(KEY_ESCAPE)) {
      currentState = UI_STATE_GAMEPLAY;
    }
    if (IsKeyPressed(KEY_Q)) {
      currentState = UI_STATE_MAIN_MENU;
    }
  }
  SetExitKey(KEY_NULL);
}

void UserInterfaceSystem::Render(const int &screenWidth,
                                 const int &screenHeight, int playerHealth) {

  if (currentState == UI_STATE_MAIN_MENU)
    RenderMainMenu(screenWidth, screenHeight);
  else if (currentState == UI_STATE_GAMEPLAY) {
    // UPPER LEFT CORNER
    DrawRectangle(10, 10, 280, 80, Fade(BLACK, 0.6f));
    DrawRectangleLines(10, 10, 280, 80, GOLD);
    DrawText("Medieval Hearth & Steel", 20, 20, 18, GOLD);
    DrawFPS(20, 65);

    // BOTTOM LEFT CORNER ( PLAYER HEALTH BAR )
    DrawRectangle(5, screenHeight - 55, 210, 40, BLACK);
    DrawRectangle(10, screenHeight - 50, playerHealth * 2, 30, RED);

    // BOTTOM CENTER
    DrawText("Work in progress...", screenWidth / 2 - 100, screenHeight - 20,
             16, RAYWHITE);
  } else if (currentState == UI_STATE_PAUSE_MENU)
    RenderPauseMenu(screenWidth, screenHeight);
  else if (currentState == UI_STATE_GAME_OVER)
    RenderPauseMenu(screenWidth, screenHeight);
}

void UserInterfaceSystem::RenderMainMenu(const int &screenWidth,
                                         const int &screenHeight) {
  DrawText("Medieval Hearth & Steel", screenWidth / 2 - 200,
           screenHeight / 2 - 100, 48, GOLD);
  DrawText("Press ENTER to start the game", screenWidth / 2 - 200,
           screenHeight / 2, 24, RAYWHITE);
}

void UserInterfaceSystem::RenderPauseMenu(const int &screenWidth,
                                          const int &screenHeight) {
  DrawText("PAUSED", screenWidth / 2 - 100, screenHeight / 2 - 100, 48, GOLD);
  DrawText("Press ESC to resume the game", screenWidth / 2 - 200,
           screenHeight / 2, 24, RAYWHITE);
  DrawText("Press Q to return to the main menu", screenWidth / 2 - 200,
           screenHeight / 2 + 40, 24, RAYWHITE);
}

UIState UserInterfaceSystem::GetCurrentState() const { return currentState; }
