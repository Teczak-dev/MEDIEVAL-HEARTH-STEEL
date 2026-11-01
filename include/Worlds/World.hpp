#pragma once
#include "raylib.h"
#include <nlohmann/json.hpp>
#include <vector>

struct MapData {
  int width;
  int height;
  std::vector<int> tiles; // 2D array of tile IDs
};

MapData LoadMapFromJson(const std::string &filepath);

void DrawMap(const MapData &map, int tileSize, const Texture2D &tileset,
             int sourceTileSize);
