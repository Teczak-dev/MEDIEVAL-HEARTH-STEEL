#include "Worlds/Chunk.hpp"

#include <fstream>
#include <nlohmann/json.hpp>

Chunk::Chunk(int gridX, int gridY, int width, int height, int tileSize,
             int sourceTileSize)
    : m_gridX(gridX), m_gridY(gridY), m_width(width), m_height(height),
      m_tileSize(tileSize), m_sourceTileSize(sourceTileSize),
      m_isLoaded(false) {}

Chunk::~Chunk() { UnloadData(); }

void Chunk::LoadData(const std::string &jsonPath) {
  if (m_isLoaded)
    return;

  if (m_width <= 0 || m_height <= 0) {
    TraceLog(LOG_WARNING, "Cannot load chunk with invalid dimensions: %s",
             jsonPath.c_str());
    return;
  }

  std::ifstream file(jsonPath);
  if (!file.is_open()) {
    TraceLog(LOG_WARNING, "Could not open chunk JSON file: %s",
             jsonPath.c_str());
    return;
  }

  try {
    const nlohmann::json data = nlohmann::json::parse(file);
    if (!data.contains("tiles") || !data["tiles"].is_array()) {
      TraceLog(LOG_WARNING, "Invalid chunk JSON format: %s", jsonPath.c_str());
      return;
    }

    const std::vector<int> loadedTiles =
        data["tiles"].get<std::vector<int>>();
    const std::size_t expectedTileCount =
        static_cast<std::size_t>(m_width) * m_height;
    if (loadedTiles.size() != expectedTileCount) {
      TraceLog(LOG_WARNING,
               "Invalid tile count in chunk JSON: %s (expected %zu, got %zu)",
               jsonPath.c_str(), expectedTileCount, loadedTiles.size());
      return;
    }

    tiles = loadedTiles;
    m_isLoaded = true;
  } catch (const nlohmann::json::exception &error) {
    TraceLog(LOG_WARNING, "Could not parse chunk JSON file %s: %s",
             jsonPath.c_str(), error.what());
  }
}

void Chunk::UnloadData() {
  tiles.clear();
  m_isLoaded = false;
}

void Chunk::Update(float deltaTime) {
  // Update logic for the chunk entities would go here in the future.
}

void Chunk::Draw(Texture2D tileset) {
  if (!m_isLoaded || m_width <= 0 || m_height <= 0 || m_tileSize <= 0 ||
      tileset.id == 0 || m_sourceTileSize <= 0 ||
      tileset.width < m_sourceTileSize ||
      tileset.height < m_sourceTileSize) {
    return;
  }

  float chunkWorldX = m_gridX * m_width * m_tileSize;
  float chunkWorldY = m_gridY * m_height * m_tileSize;

  int tilesPerRow = tileset.width / m_sourceTileSize;
  int tileRows = tileset.height / m_sourceTileSize;
  int tileCount = tilesPerRow * tileRows;

  for (int y = 0; y < m_height; ++y) {
    for (int x = 0; x < m_width; ++x) {
      int tileID = tiles[y * m_width + x];
      if (tileID < 0 || tileID >= tileCount)
        continue;

      float srcX = (tileID % tilesPerRow) * m_sourceTileSize;
      float srcY = (tileID / tilesPerRow) * m_sourceTileSize;

      Rectangle sourceRect = {srcX, srcY, (float)m_sourceTileSize,
                              (float)m_sourceTileSize};
      Rectangle destRec = {chunkWorldX + x * m_tileSize,
                           chunkWorldY + y * m_tileSize, (float)m_tileSize,
                           (float)m_tileSize};
      DrawTexturePro(tileset, sourceRect, destRec, {0.0f, 0.0f}, 0.0f, WHITE);
    }
  }
}
