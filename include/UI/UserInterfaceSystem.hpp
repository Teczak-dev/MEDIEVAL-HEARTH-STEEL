
#pragma once

// Controls interface states, menus, HUD rendering, and UI-related requests.
#include "raylib.h"

enum UIState {
  UI_STATE_MAIN_MENU,
  UI_STATE_GAMEPLAY,
  UI_STATE_PAUSE_MENU,
  UI_STATE_INVENTORY,
  UI_STATE_CRAFTING,
  UI_STATE_DIALOGUE,
  UI_STATE_SHOP,
  UI_STATE_SETTINGS,
  UI_STATE_GAME_OVER
};

class UserInterfaceSystem {
public:
  UserInterfaceSystem();
  ~UserInterfaceSystem();

  void Update(float deltaTime);
  void Render(const int &screenWidth, const int &screenHeight, int playerHealth,
              Vector2 playerPosition);
  UIState GetCurrentState() const;
  bool IsExitRequested() const;

  bool IsMinimapVisible() const { return showMinimap; }
  void ToggleMinimap() { showMinimap = !showMinimap; }

private:
  UIState currentState = UI_STATE_MAIN_MENU;
  bool showMinimap = true;
  bool exitRequested = false;

  // windows and other UI classes
};
