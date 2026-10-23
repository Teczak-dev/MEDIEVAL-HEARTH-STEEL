#include "Characters/Player.hpp"
#include "Worlds/TestMap.hpp"
#include "raylib.h"

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

int main() {

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT,
             "MEDIEVAL HEARTH & STEEL - Prototype");
  if (!IsWindowReady()) {
    TraceLog(LOG_ERROR, "Could not create the application window");
    return 1;
  }

  SetTargetFPS(60);
  Damage damage;

  Player player({SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f}, 200.0f);

  TestMap map(30, 40, 64, 64);

  InputSystem inpSys;
  UserInterfaceSystem uiSys;

  Camera2D camera = {0};
  camera.target = player.GetPosition();
  camera.offset = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  // turn off the default exit key (ESC) to avoid closing the window when
  // pressing ESC
  // SetExitKey(KEY_NULL);

  while (!WindowShouldClose()) {
    float deltaTime = GetFrameTime();
    // 1. Update (Logika gry)
    player.Update(deltaTime, inpSys, SCREEN_WIDTH, SCREEN_HEIGHT, damage);
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
    uiSys.Render(SCREEN_WIDTH, SCREEN_HEIGHT, player.health.GetCurrentHealth());

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
