#include "Worlds/World.hpp"
#include "nlohmann/json.hpp"
#include "raymath.h"
#include <cmath>
#include <fstream>
#include <stdexcept>

using json = nlohmann::json;

World::World(const std::string &mapPath) {
  std::ifstream file(mapPath);
  if (!file) {
    throw std::runtime_error("Could not open map file: " + mapPath);
  }

  json document;
  file >> document;
  const json &mapChunks = document.at("chunks");
  if (!mapChunks.is_array() || mapChunks.empty() ||
      !mapChunks.front().is_array() || mapChunks.front().empty()) {
    throw std::runtime_error("Map field 'chunks' must be a non-empty 2D array");
  }

  const std::size_t mapWidth = mapChunks.front().size();
  chunks.resize(mapChunks.size());
  for (std::size_t y = 0; y < mapChunks.size(); ++y) {
    if (!mapChunks[y].is_array() || mapChunks[y].size() != mapWidth) {
      throw std::runtime_error("Map chunks must form a rectangular 2D array");
    }
    chunks[y].reserve(mapWidth);
    for (std::size_t x = 0; x < mapWidth; ++x) {
      const json &sourceChunk = mapChunks[y][x];
      if (sourceChunk.contains("fill")) {
        chunks[y].emplace_back(chunkWidth, chunkHeight,
                               sourceChunk["fill"].get<int>(), x, y,
                               tileSize);
      } else if (sourceChunk.contains("tiles")) {
        auto tiles = sourceChunk["tiles"].get<std::vector<std::vector<int>>>();
        if (tiles.size() != static_cast<std::size_t>(chunkHeight)) {
          throw std::runtime_error("Chunk tile height does not match chunkSize");
        }
        for (const auto &row : tiles) {
          if (row.size() != static_cast<std::size_t>(chunkWidth)) {
            throw std::runtime_error("Chunk tile width does not match chunkSize");
          }
        }
        chunks[y].emplace_back(tiles, x, y, tileSize);
      } else {
        chunks[y].emplace_back(chunkWidth, chunkHeight, 0, x, y, tileSize);
      }
    }
  }
}

void World::UpdateActiveChunks(Vector2 playerPosition) {
  const int worldChunkWidth = chunkWidth * tileSize;
  const int worldChunkHeight = chunkHeight * tileSize;
  SetChunkActivity(static_cast<int>(playerPosition.x / worldChunkWidth),
                   static_cast<int>(playerPosition.y / worldChunkHeight));
}

void World::SetChunkActivity(int playerChunkX, int playerChunkY) {
  for (int y = 0; y < static_cast<int>(chunks.size()); ++y) {
    for (int x = 0; x < static_cast<int>(chunks[y].size()); ++x) {
      chunks[y][x].active = std::abs(x - playerChunkX) <= 1 &&
                            std::abs(y - playerChunkY) <= 1;
    }
  }
}

void World::Draw(Texture2D tileset) const {
  for (std::size_t chunkY = 0; chunkY < chunks.size(); ++chunkY) {
    for (std::size_t chunkX = 0; chunkX < chunks[chunkY].size(); ++chunkX) {
      const Chunk &chunk = chunks[chunkY][chunkX];
      if (!chunk.active) {
        continue;
      }
      for (int tileY = 0; tileY < chunkHeight; ++tileY) {
        for (int tileX = 0; tileX < chunkWidth; ++tileX) {
          const int tile = chunk.tiles[tileY][tileX];
          if (tile == 0) {
            continue;
          }
          const int x = (static_cast<int>(chunkX) * chunkWidth + tileX) *
                        tileSize;
          const int y = (static_cast<int>(chunkY) * chunkHeight + tileY) *
                        tileSize;
          if (tileset.id != 0 && tile >= 1 && tile <= 3) {
            DrawTextureRec(tileset,
                           {(tile - 1) * static_cast<float>(tileSize), 0,
                            static_cast<float>(tileSize),
                            static_cast<float>(tileSize)},
                           {static_cast<float>(x), static_cast<float>(y)},
                           WHITE);
          } else {
            DrawRectangle(x, y, tileSize, tileSize,
                          tile == 2 ? BROWN : (tile == 3 ? DARKGRAY : GREEN));
          }
        }
      }
    }
  }
}

bool World::Collides(Vector2 position, Vector2 size) const {
  const Rectangle playerBounds = {position.x, position.y, size.x, size.y};
  for (const auto &row : chunks) {
    for (const Chunk &chunk : row) {
      if (!chunk.active) {
        continue;
      }
      for (const Rectangle &collision : chunk.collisions) {
        if (CheckCollisionRecs(playerBounds, collision)) {
          return true;
        }
      }
    }
  }
  return false;
}

Vector2 World::GetWorldSize() const {
  return {static_cast<float>(chunks.front().size() * chunkWidth * tileSize),
          static_cast<float>(chunks.size() * chunkHeight * tileSize)};
}

Vector2 World::ClampPosition(Vector2 position, Vector2 size) const {
  const Vector2 worldSize = GetWorldSize();
  return {Clamp(position.x, 0.0f, worldSize.x - size.x),
          Clamp(position.y, 0.0f, worldSize.y - size.y)};
}

void World::DrawMinimap(Rectangle bounds, Vector2 playerPosition) const {
  const float minimapChunkWidth = bounds.width / chunks.front().size();
  const float minimapChunkHeight = bounds.height / chunks.size();
  DrawRectangleRec(bounds, Fade(BLACK, 0.75f));
  DrawRectangleLinesEx(bounds, 2.0f, GOLD);
  for (std::size_t y = 0; y < chunks.size(); ++y) {
    for (std::size_t x = 0; x < chunks[y].size(); ++x) {
      const Color color = chunks[y][x].HasWater()
                              ? Color{55, 145, 210, 255}
                              : Color{90, 150, 70, 255};
      DrawRectangle(static_cast<int>(bounds.x + x * minimapChunkWidth) + 1,
                    static_cast<int>(bounds.y + y * minimapChunkHeight) + 1,
                    static_cast<int>(minimapChunkWidth) - 2,
                    static_cast<int>(minimapChunkHeight) - 2, color);
    }
  }
  const Vector2 worldSize = GetWorldSize();
  DrawCircle(static_cast<int>(bounds.x + playerPosition.x / worldSize.x *
                              bounds.width),
             static_cast<int>(bounds.y + playerPosition.y / worldSize.y *
                              bounds.height),
             4.0f, RED);
}
