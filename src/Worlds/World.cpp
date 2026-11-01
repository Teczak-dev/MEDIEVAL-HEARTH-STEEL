#include "Worlds/World.hpp"
#include <fstream>

MapData LoadMapFromJson(const std::string &filepath) {
  MapData map;
  std::ifstream file(filepath);
  if (!file.is_open())
    return map;

  nlohmann::json j;
  file >> j;
  map.width = j["width"];
  map.height = j["height"];
  map.tiles = j["tiles"].get<std::vector<int>>();
  return map;
}

void DrawMap(const MapData &map, int tileSize, const Texture2D &tileset,
             int sourceTileSize) {
  for (int y = 0; y < map.height; ++y) {
    for (int x = 0; x < map.width; ++x) {
      int tileID = map.tiles[y * map.width + x];
      if (tileID < 0)
        continue; // Skip empty tiles
      int tilesPerRow = tileset.width / sourceTileSize;
      float srcX = (tileID % tilesPerRow) * sourceTileSize;
      float srcY = (tileID / tilesPerRow) * sourceTileSize;

      Rectangle sourceRect = {srcX, srcY,
                              (float)sourceTileSize, (float)sourceTileSize};

      Rectangle destRec = {(float)(x * tileSize), (float)(y * tileSize),
                           (float)tileSize, (float)tileSize};

      Vector2 origin = {0.0f, 0.0f};
      DrawTexturePro(tileset, sourceRect, destRec, origin, 0.0f, WHITE);
    }
  }
}
