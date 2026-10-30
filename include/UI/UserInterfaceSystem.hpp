
#pragma once

enum UIState {
  UI_STATE_MAIN_MENU,
  UI_STATE_GAMEPLAY,
  UI_STATE_PAUSE_MENU,
  UI_STATE_GAME_OVER
};

class UserInterfaceSystem {
public:
  UserInterfaceSystem();
  ~UserInterfaceSystem();

  void Update(float deltaTime);
  void Render(const int &screenWidth, const int &screenHeight,
              int playerHealth);
  void RenderMainMenu(const int &screenWidth, const int &screenHeight);
  void RenderPauseMenu(const int &screenWidth, const int &screenHeight);
  UIState GetCurrentState() const;

private:
  UIState currentState = UI_STATE_MAIN_MENU;
};
