#include "Core/Game.hpp"
#include "Gameplay/Damage.hpp"
#include "Systems/InputSystem.hpp"
#include "UI/UserInterfaceSystem.hpp"
#include "raymath.h"

Game::Game() : player({512.0f, 612.0f}, 200.0f), inpSys(), uiSys(), damage() {
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

int Game::GetScreenWidth() const { return SCREEN_WIDTH; }
int Game::GetScreenHeight() const { return SCREEN_HEIGHT; }
bool Game::IsExitRequested() const { return uiSys.IsExitRequested(); }

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
    map.UpdateActiveChunks(player.GetPosition());
    player.Update(deltaTime, inpSys, SCREEN_WIDTH, SCREEN_HEIGHT, damage, map);
    const Vector2 worldSize = map.GetWorldSize();
    const float halfViewWidth = SCREEN_WIDTH / (2.0f * camera.zoom);
    const float halfViewHeight = SCREEN_HEIGHT / (2.0f * camera.zoom);
    camera.target = player.GetPosition();
    camera.target.x = Clamp(camera.target.x + 32.0f, halfViewWidth,
                            worldSize.x - halfViewWidth);
    camera.target.y = Clamp(camera.target.y + 32.0f, halfViewHeight,
                            worldSize.y - halfViewHeight);
    if (IsKeyDown(KEY_X))
      camera.zoom += 0.01f;
    if (IsKeyDown(KEY_Z))
      camera.zoom -= 0.01f;
    if (IsKeyPressed(KEY_C))
      camera.zoom = 1.0f;
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
  uiSys.Render(SCREEN_WIDTH, SCREEN_HEIGHT, player.health.GetCurrentHealth(),
               map, player.GetPosition());

  EndDrawing();
}
