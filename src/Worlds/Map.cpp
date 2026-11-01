#include "Worlds/Map.hpp"
#include <cmath>
#include <string>

Map::Map(int worldWidthChunks, int worldHeightChunks, int chunkWidthTiles,
         int chunkHeightTiles, int tileSize, int sourceTileSize)
    : m_worldWidthChunks(worldWidthChunks),
      m_worldHeightChunks(worldHeightChunks),
      m_chunkWidthTiles(chunkWidthTiles), m_chunkHeightTiles(chunkHeightTiles),
      m_tileSize(tileSize), m_sourceTileSize(sourceTileSize) {
  if (m_worldWidthChunks <= 0 || m_worldHeightChunks <= 0 ||
      m_chunkWidthTiles <= 0 || m_chunkHeightTiles <= 0 || m_tileSize <= 0 ||
      m_sourceTileSize <= 0) {
    TraceLog(LOG_WARNING, "Map has invalid dimensions or tile sizes");
    return;
  }

  m_chunks.resize(m_worldHeightChunks, std::vector<Chunk>());
  for (int y = 0; y < m_worldHeightChunks; ++y) {
    for (int x = 0; x < m_worldWidthChunks; ++x) {
      m_chunks[y].emplace_back(x, y, m_chunkWidthTiles, m_chunkHeightTiles,
                               m_tileSize, m_sourceTileSize);
    }
  }
}

Map::~Map() { UnloadAssets(); }

void Map::LoadAssets() {
  if (m_sharedTileset.id != 0) {
    return;
  }

  m_sharedTileset = LoadTexture("assets/textures/tileset.png");
  if (m_sharedTileset.id == 0) {
    TraceLog(LOG_ERROR, "Could not load tileset: assets/textures/tileset.png");
  }
}

void Map::UnloadAssets() {
  if (m_sharedTileset.id == 0) {
    return;
  }

  UnloadTexture(m_sharedTileset);
  m_sharedTileset = {0};
}

Vector2 Map::GetChunkCoordsFromPosition(Vector2 worldPosition) const {
  if (m_chunkWidthTiles <= 0 || m_chunkHeightTiles <= 0 || m_tileSize <= 0) {
    return {0.0f, 0.0f};
  }

  // Size of one chunk in pixels = (number of tiles) * (tile size)
  float chunkPixelWidth = m_chunkWidthTiles * m_tileSize;
  float chunkPixelHeight = m_chunkHeightTiles * m_tileSize;

  //  Dividing the player's position by the chunk size and rounding down gives
  //  us the chunk coordinates
  int chunkX = static_cast<int>(std::floor(worldPosition.x / chunkPixelWidth));
  int chunkY = static_cast<int>(std::floor(worldPosition.y / chunkPixelHeight));

  return {static_cast<float>(chunkX), static_cast<float>(chunkY)};
}

void Map::Update(Vector2 playerPosition) {
  Vector2 playerChunk = GetChunkCoordsFromPosition(playerPosition);

  for (int y = 0; y < m_worldHeightChunks; ++y) {
    for (int x = 0; x < m_worldWidthChunks; ++x) {
      bool inRange = (x >= playerChunk.x - 1 && x <= playerChunk.x + 1) &&
                     (y >= playerChunk.y - 1 && y <= playerChunk.y + 1);
      if (inRange) {
        m_chunks[y][x].LoadData("assets/maps/chunk_" + std::to_string(x) + "_" +
                                std::to_string(y) + ".json");
      } else {
        m_chunks[y][x].UnloadData();
      }
    }
  }
}

void Map::Draw() {
  if (m_sharedTileset.id == 0) {
    return;
  }

  for (auto &row : m_chunks) {
    for (auto &chunk : row) {
      if (chunk.IsLoaded()) {
        chunk.Draw(m_sharedTileset);
      }
    }
  }
}
