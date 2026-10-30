#pragma once

#include "raylib.h"
#include <vector>

class Chunk {
public:
  Chunk(int width, int height, int fill, int chunkX, int chunkY, int tileSize);
  Chunk(const std::vector<std::vector<int>> &tiles, int chunkX, int chunkY,
        int tileSize);

  void BuildWaterCollisions(int chunkX, int chunkY, int tileSize);
  bool HasWater() const;

  std::vector<std::vector<int>> tiles;
  std::vector<Rectangle> collisions;
  bool active = false;
};