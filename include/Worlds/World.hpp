#pragma once

#include "Worlds/Chunk.hpp"
#include "raylib.h"
#include <string>
#include <vector>

class World {
public:
  explicit World(const std::string &mapPath);

  void UpdateActiveChunks(Vector2 playerPosition);
  void Draw(Texture2D tileset) const;
  bool Collides(Vector2 position, Vector2 size) const;
  Vector2 ClampPosition(Vector2 position, Vector2 size) const;
  Vector2 GetWorldSize() const;
  void DrawMinimap(Rectangle bounds, Vector2 playerPosition) const;

private:
  int tileSize = 64;
  int chunkWidth = 128;
  int chunkHeight = 128;
  std::vector<std::vector<Chunk>> chunks;

  void SetChunkActivity(int playerChunkX, int playerChunkY);
};