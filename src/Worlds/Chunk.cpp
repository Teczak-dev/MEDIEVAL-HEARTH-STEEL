#include "Worlds/Chunk.hpp"

namespace {
constexpr int kWaterTile = 3;
}

Chunk::Chunk(int width, int height, int fill, int chunkX, int chunkY,
             int tileSize)
    : tiles(height, std::vector<int>(width, fill)) {
  BuildWaterCollisions(chunkX, chunkY, tileSize);
}

Chunk::Chunk(const std::vector<std::vector<int>> &sourceTiles, int chunkX,
             int chunkY, int tileSize)
    : tiles(sourceTiles) {
  BuildWaterCollisions(chunkX, chunkY, tileSize);
}

void Chunk::BuildWaterCollisions(int chunkX, int chunkY, int tileSize) {
  collisions.clear();
  for (int tileY = 0; tileY < static_cast<int>(tiles.size()); ++tileY) {
    int waterStart = -1;
    for (int tileX = 0; tileX <= static_cast<int>(tiles[tileY].size());
         ++tileX) {
      const bool isWater =
          tileX < static_cast<int>(tiles[tileY].size()) &&
          tiles[tileY][tileX] == kWaterTile;
      if (isWater && waterStart == -1) {
        waterStart = tileX;
      } else if (!isWater && waterStart != -1) {
        collisions.push_back(
            {static_cast<float>((chunkX * tiles[tileY].size() + waterStart) *
                                tileSize),
             static_cast<float>((chunkY * tiles.size() + tileY) * tileSize),
             static_cast<float>((tileX - waterStart) * tileSize),
             static_cast<float>(tileSize)});
        waterStart = -1;
      }
    }
  }
}

bool Chunk::HasWater() const { return !collisions.empty(); }
