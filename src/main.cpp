#include "Characters/Player.hpp"
#include "Systems/InputSystem.hpp"
#include "Systems/UserInterfaceSystem.hpp"
#include "Worlds/TestMap.hpp"
#include "raylib.h"

int main() {
  const int screenWidth = 1024;
  const int screenHeight = 768;

  InitWindow(screenWidth, screenHeight, "MEDIEVAL HEARTH & STEEL - Prototype");
  if (!IsWindowReady()) {
    TraceLog(LOG_ERROR, "Could not create the application window");
    return 1;
  }

  SetTargetFPS(60);

  Player player({screenWidth / 2.0f, screenHeight / 2.0f}, 200.0f);

  TestMap map(30, 40, 64, 64);

  InputSystem inpSys;
  UserInterfaceSystem uiSys;

  Camera2D camera = {0};
  camera.target = player.GetPosition();
  camera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  SetExitKey(KEY_NULL);

  while (!WindowShouldClose()) {
    float deltaTime = GetFrameTime();
    // 1. Update (Logika gry)
    player.Update(deltaTime, inpSys, screenWidth, screenHeight);
    camera.target = player.GetPosition();
    // 2. Draw (Renderowanie)
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
    uiSys.Render(screenWidth, screenHeight, player.GetHealth());

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
