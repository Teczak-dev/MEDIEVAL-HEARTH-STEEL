#include "Worlds/Map.hpp"
#include "raylib.h"

Map::Map(const std::string &mapPath) : world(mapPath) {}

void Map::LoadAssets() {
  if (tileset.id == 0) {
    tileset = LoadTexture("assets/textures/tileset.png");
    if (tileset.id == 0) {
      TraceLog(LOG_ERROR, "Could not load map tileset");
    }
  }
}

void Map::UnloadAssets() {
  if (tileset.id != 0 && IsWindowReady()) {
    UnloadTexture(tileset);
  }
  tileset = {0};
}

void Map::Draw() {
  world.Draw(tileset);
}

void Map::UpdateActiveChunks(Vector2 playerPosition) {
  world.UpdateActiveChunks(playerPosition);
}

bool Map::Collides(Vector2 position, Vector2 size) const {
  return world.Collides(position, size);
}

Vector2 Map::GetWorldSize() const { return world.GetWorldSize(); }

Vector2 Map::ClampPosition(Vector2 position, Vector2 size) const {
  return world.ClampPosition(position, size);
}

void Map::DrawMinimap(Rectangle bounds, Vector2 playerPosition) const {
  world.DrawMinimap(bounds, playerPosition);
}
