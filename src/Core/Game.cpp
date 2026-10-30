#include "Core/Game.hpp"
#include "Gameplay/Damage.hpp"
#include "Systems/InputSystem.hpp"
#include "UI/UserInterfaceSystem.hpp"

Game::Game() : player({512.0f, 612.0f}, 200.0f), inpSys(), uiSys(), damage() {
  camera.target = player.GetPosition();
  camera.offset = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 200.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;
}

Game::~Game() {}

int Game::GetScreenWidth() const { return SCREEN_WIDTH; }
int Game::GetScreenHeight() const { return SCREEN_HEIGHT; }

void Game::Update(float deltaTime) {
  uiSys.Update(deltaTime);

  const UIState currentUIState = uiSys.GetCurrentState();
  if (lastUIState != currentUIState) {
    lastUIState = currentUIState;
    if (currentUIState == UI_STATE_GAMEPLAY) {
      camera.offset = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
    } else if (currentUIState == UI_STATE_MAIN_MENU) {
      camera.offset = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 200.0f};
    }
  }

  if (currentUIState == UI_STATE_GAMEPLAY) {
    player.Update(deltaTime, inpSys, SCREEN_WIDTH, SCREEN_HEIGHT, damage);
    camera.target = player.GetPosition();
  }
}

void Game::Draw() {
  BeginDrawing();
  ClearBackground(BLACK);

  // RYSOWANIE W WSPÓŁRZĘDNYCH Świata (world coordinates)
  BeginMode2D(camera);
  // world rendering
  map.Draw();

  // player rendering
  player.Draw();
  EndMode2D();

  // interface
  uiSys.Render(SCREEN_WIDTH, SCREEN_HEIGHT, player.health.GetCurrentHealth());

  EndDrawing();
}
