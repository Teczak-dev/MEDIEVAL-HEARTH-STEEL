#pragma once

// This class represents the game scene manager, which is responsible for
// managing the different scenes in the game, such as the main menu, gameplay,
// and pause menu. It handles scene transitions, updates, and rendering.
// or at least it will in the future, for now it just a placeholder for the main
// game loop and scene management.
#include "Characters/Player.hpp"
#include "Gameplay/Damage.hpp"
#include "Systems/InputSystem.hpp"
#include "UI/UserInterfaceSystem.hpp"
#include "Worlds/Map.hpp"
#include "raylib.h"

class Game {
public:
  Game();
  ~Game();

  void LoadAssets();
  void Shutdown();
  void Update(float deltaTime);
  void Draw();
  int GetScreenWidth() const;
  int GetScreenHeight() const;
  bool IsExitRequested() const;

private:
  const int SCREEN_WIDTH = 1024;
  const int SCREEN_HEIGHT = 768;
  Player player;
  InputSystem inpSys;
  UserInterfaceSystem uiSys;
  Damage damage;
  Camera2D camera = {0};
  UIState lastUIState = UI_STATE_MAIN_MENU;
  bool isShutdown = false;

  Map map;
};
