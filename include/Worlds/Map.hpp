#pragma once

#include "Worlds/World.hpp"
#include "raylib.h"
#include <memory>
#include <string>

class Map {
public:
  explicit Map(const std::string &mapPath);
  void LoadAssets();
  void UnloadAssets();
  bool IsInteriorActive() const;
  bool HasEntrance(Vector2 playerPosition, Vector2 playerSize) const;
  bool IsAtInteriorExit(Vector2 playerPosition, Vector2 playerSize) const;
  bool EnterInterior(Vector2 playerPosition, Vector2 playerSize,
                     Vector2 &interiorSpawn);
  bool LeaveInterior(Vector2 &outdoorPosition);

  void UpdateActiveChunks(Vector2 playerPosition);
  void Draw();
  bool Collides(Vector2 position, Vector2 size) const;
  Vector2 ClampPosition(Vector2 position, Vector2 size) const;
  Vector2 GetWorldSize() const;
  void DrawMinimap(Rectangle bounds, Vector2 playerPosition) const;

private:
  World world;
  std::unique_ptr<World> interiorWorld;
  Texture2D outdoorTileset = {0};
  Texture2D interiorTileset = {0};
  Vector2 outdoorReturnPosition = {0};
};
