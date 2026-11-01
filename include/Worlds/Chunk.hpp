#pragma once

// Represents a loaded portion of the game world and manages its tiles.
#include "raylib.h"
#include <string>
#include <vector>

class Chunk {
public:
  Chunk(int gridX, int gridY, int width, int height, int tileSize,
        int sourceTileSize);
  ~Chunk();

  void LoadData(const std::string &jsonPath);
  void UnloadData();

  void Update(float deltaTime);
  void Draw(Texture2D tileset);

  // Getters
  int GetX() const { return m_gridX; }
  int GetY() const { return m_gridY; }
  bool IsLoaded() const { return m_isLoaded; }

private:
  int m_gridX;            // X position in the chunk grid (e.g., 0, 1, -1)
  int m_gridY;            // Y position in the chunk grid
  int m_width;            // Width in tiles
  int m_height;           // Height in tiles
  std::vector<int> tiles; // Flattened two-dimensional array of tile IDs
  int m_tileSize;         // Size of each tile in pixels
  int m_sourceTileSize;   // Size of each tileset tile in pixels
  bool m_isLoaded;        // Whether the chunk is currently loaded in memory

};
