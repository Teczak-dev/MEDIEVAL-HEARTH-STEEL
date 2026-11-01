#pragma once

// Provides the interface for map data and map rendering.
#include "Worlds/Chunk.hpp"
#include "raylib.h"
#include <vector>

class Map {
public:
  Map(int worldWidthChunks, int worldHeightChunks, int chunkWidthTiles,
      int chunkHeightTiles, int tileSize, int sourceTileSize);
  ~Map();

  void LoadAssets();
  void UnloadAssets();
  void Update(
      Vector2 playerPosition); // Update the map based on the player's position

  void Draw(); // Draw the visible chunks of the map
private:
  int m_worldWidthChunks;  // Width of the world in chunks e.g., 10 chunks wide
  int m_worldHeightChunks; // Height of the world in chunks
  int m_chunkWidthTiles;   // Width of each chunk in tiles e.g., 128
  int m_chunkHeightTiles;  // Height of each chunk in tiles
  int m_tileSize;
  int m_sourceTileSize;

  Texture2D m_sharedTileset = {0};

  std::vector<std::vector<Chunk>> m_chunks; // 2 dimensional array of chunks

  Vector2 GetChunkCoordsFromPosition(Vector2 worldPosition) const;
};
