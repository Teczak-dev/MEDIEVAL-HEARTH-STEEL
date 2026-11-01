#include "Core/Game.hpp"
#include "Gameplay/Damage.hpp"
#include "Systems/InputSystem.hpp"
#include "UI/UserInterfaceSystem.hpp"
#include "raymath.h"

Game::Game()
    : player({64.0f, 64.0f}, 200.0f), inpSys(), uiSys(), damage(),
      map(3, 3, 4, 3, 64, 64) {
  camera.target = player.GetPosition();
  camera.offset = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 200.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;
}

Game::~Game() { Shutdown(); }

void Game::LoadAssets() { map.LoadAssets(); }

void Game::Shutdown() {
  if (isShutdown) {
    return;
  }
  map.UnloadAssets();
  isShutdown = true;
}

void Game::HandleStateTransition(UIState oldState, UIState newState) {
  if (newState == UI_STATE_GAMEPLAY) {
    camera.offset = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
  } else if (newState == UI_STATE_MAIN_MENU) {
    camera.offset = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 200.0f};
  }
}

void Game::UpdateCamera() {
  camera.target = player.GetPosition();

  if (IsKeyDown(KEY_X))
    camera.zoom = Clamp(camera.zoom + 0.01f, 0.001f, 3.0f);
  if (IsKeyDown(KEY_Z))
    camera.zoom = Clamp(camera.zoom - 0.01f, 0.001f, 3.0f);
  if (IsKeyPressed(KEY_C))
    camera.zoom = 1.0f;
}

int Game::GetScreenWidth() const { return SCREEN_WIDTH; }
int Game::GetScreenHeight() const { return SCREEN_HEIGHT; }
bool Game::IsExitRequested() const { return uiSys.IsExitRequested(); }

void Game::Update(float deltaTime) {
  uiSys.Update(deltaTime);

  const UIState currentUIState = uiSys.GetCurrentState();
  if (lastUIState != currentUIState) {
    HandleStateTransition(lastUIState, currentUIState);
    lastUIState = currentUIState;
  }
  switch (currentUIState) {
  case UI_STATE_MAIN_MENU:
    // Handle main menu logic here if needed in the future
    break;
  case UI_STATE_GAMEPLAY:
    map.Update(player.GetPosition());
    player.Update(deltaTime, inpSys, SCREEN_WIDTH, SCREEN_HEIGHT, damage);
    UpdateCamera();
    break;
  case UI_STATE_PAUSE_MENU:
    UpdateCamera();
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
  camera.target = player.GetPosition();
  if (IsKeyDown(KEY_X))
    camera.zoom = Clamp(camera.zoom + 0.01f, 0.0001f, 10.0f);
  if (IsKeyDown(KEY_Z))
    camera.zoom = Clamp(camera.zoom - 0.01f, 0.0001f, 10.0f);
  if (IsKeyPressed(KEY_C))
    camera.zoom = 1.0f;

  if (currentUIState == UI_STATE_PAUSE_MENU) {
    camera.target = player.GetPosition();
  }
}

void Game::Draw() {
  BeginDrawing();
  ClearBackground(BLACK);

  // Draw the world using world coordinates.
  BeginMode2D(camera);
  map.Draw();
  // Player rendering
  player.Draw();
  EndMode2D();

  // User interface
  uiSys.Render(SCREEN_WIDTH, SCREEN_HEIGHT, player.health.GetCurrentHealth(),
               player.GetPosition());

  EndDrawing();
}
