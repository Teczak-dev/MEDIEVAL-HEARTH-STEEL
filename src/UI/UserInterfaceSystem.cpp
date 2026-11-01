#include "UI/UserInterfaceSystem.hpp"
#include "UI/HUD.hpp"
#include "UI/MainMenu.hpp"
#include "UI/Pause.hpp"
#include "raylib.h"

UserInterfaceSystem::UserInterfaceSystem() {}
UserInterfaceSystem::~UserInterfaceSystem() {}

void UserInterfaceSystem::Update(float deltaTime) {
  switch (currentState) {
  case UI_STATE_MAIN_MENU:
    if (IsKeyPressed(KEY_ENTER)) {
      currentState = UI_STATE_GAMEPLAY;
    }
    if (IsKeyPressed(KEY_Q)) {
      exitRequested = true;
    }
    break;
  case UI_STATE_GAMEPLAY:
    if (IsKeyPressed(KEY_ESCAPE)) {
      currentState = UI_STATE_PAUSE_MENU;
    }
    if (IsKeyPressed(KEY_TAB)) {
      ToggleMinimap();
    }
    break;
  case UI_STATE_PAUSE_MENU:
    if (IsKeyPressed(KEY_ESCAPE)) {
      currentState = UI_STATE_GAMEPLAY;
    }
    if (IsKeyPressed(KEY_Q)) {
      currentState = UI_STATE_MAIN_MENU;
    }
    break;
  case UI_STATE_GAME_OVER:
  case UI_STATE_INVENTORY:
  case UI_STATE_CRAFTING:
  case UI_STATE_DIALOGUE:
  case UI_STATE_SHOP:
  case UI_STATE_SETTINGS:
  default:
    break;
  }
}

void UserInterfaceSystem::Render(const int &screenWidth,
                                 const int &screenHeight, int playerHealth,
                                 Vector2 playerPosition) {
  switch (currentState) {
  case UI_STATE_MAIN_MENU:
    DrawMainMenu(screenWidth, screenHeight);
    break;
  case UI_STATE_GAMEPLAY:
    DrawHUD(screenWidth, screenHeight, playerHealth, playerPosition);
    break;
  case UI_STATE_PAUSE_MENU:
    DrawPauseMenu(screenWidth, screenHeight);
    break;
  case UI_STATE_GAME_OVER:
  case UI_STATE_INVENTORY:
  case UI_STATE_CRAFTING:
  case UI_STATE_DIALOGUE:
  case UI_STATE_SHOP:
  case UI_STATE_SETTINGS:
  default:
    break;
  }
}

UIState UserInterfaceSystem::GetCurrentState() const { return currentState; }

bool UserInterfaceSystem::IsExitRequested() const { return exitRequested; }
