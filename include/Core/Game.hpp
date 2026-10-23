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

class Game {
public:
  Game();
  ~Game();

  void LoadScene(const std::string &sceneName);

  void Update(float deltaTime);
  void Draw();

private:
  std::vector<std::string> scenes;
  Player player;
  InputSystem inpSys;
  UserInterfaceSystem uiSys;
  Damage damage;
};
