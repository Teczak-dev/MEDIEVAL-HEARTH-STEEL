#pragma once

#include "Worlds/World.hpp"
#include "raylib.h"
#include <string>

class Map {
public:
  explicit Map(const std::string &mapPath);
  void LoadAssets();
  void UnloadAssets();

  void UpdateActiveChunks(Vector2 playerPosition);
  void Draw();
  bool Collides(Vector2 position, Vector2 size) const;
  Vector2 ClampPosition(Vector2 position, Vector2 size) const;
  Vector2 GetWorldSize() const;
  void DrawMinimap(Rectangle bounds, Vector2 playerPosition) const;

private:
  World world;
  Texture2D tileset = {0};
};
