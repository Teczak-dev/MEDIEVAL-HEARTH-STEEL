
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
  void Render(int screenWidth, int screenHeight, int playerHealth);

private:
  UIState currentState = UI_STATE_GAMEPLAY;
};
