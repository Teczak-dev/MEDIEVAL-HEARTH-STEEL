#pragma once

#include "Worlds/Chunk.hpp"
#include "raylib.h"
#include <optional>
#include <string>
#include <vector>

struct WorldEntrance {
  std::string id;
  int chunkX = 0;
  int chunkY = 0;
  Rectangle bounds = {0};
  std::string worldPath;
  std::string tilesetPath;
  Vector2 interiorSpawn = {0};
  Vector2 outdoorReturn = {0};
};

class World {
public:
  explicit World(const std::string &mapPath);

  void UpdateActiveChunks(Vector2 playerPosition);
  void Draw(Texture2D tileset) const;
  bool Collides(Vector2 position, Vector2 size) const;
  Vector2 ClampPosition(Vector2 position, Vector2 size) const;
  Vector2 GetWorldSize() const;
  void DrawMinimap(Rectangle bounds, Vector2 playerPosition) const;
  std::optional<WorldEntrance> FindEntrance(Vector2 position,
                                             Vector2 size) const;
  bool IsAtExit(Vector2 position, Vector2 size) const;

private:
  int tileSize = 64;
  int chunkWidth = 128;
  int chunkHeight = 128;
  std::vector<std::vector<Chunk>> chunks;
  std::vector<WorldEntrance> entrances;
  std::optional<Rectangle> exitBounds;

  void SetChunkActivity(int playerChunkX, int playerChunkY);
  void DrawEntranceMarkers() const;
};