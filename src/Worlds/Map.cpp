#include "Worlds/Map.hpp"
#include "raylib.h"
#include <stdexcept>

Map::Map(const std::string &mapPath) : world(mapPath) {}

void Map::LoadAssets() {
  if (outdoorTileset.id == 0) {
    outdoorTileset = LoadTexture("assets/textures/tileset.png");
    if (outdoorTileset.id == 0) {
      TraceLog(LOG_ERROR, "Could not load map tileset");
    }
  }
}

void Map::UnloadAssets() {
  if (IsWindowReady()) {
    if (outdoorTileset.id != 0) {
      UnloadTexture(outdoorTileset);
    }
    if (interiorTileset.id != 0) {
      UnloadTexture(interiorTileset);
    }
  }
  outdoorTileset = {0};
  interiorTileset = {0};
  interiorWorld.reset();
}

bool Map::IsInteriorActive() const { return interiorWorld != nullptr; }

bool Map::HasEntrance(Vector2 playerPosition, Vector2 playerSize) const {
  return !interiorWorld &&
         world.FindEntrance(playerPosition, playerSize).has_value();
}

bool Map::IsAtInteriorExit(Vector2 playerPosition, Vector2 playerSize) const {
  return interiorWorld && interiorWorld->IsAtExit(playerPosition, playerSize);
}

bool Map::EnterInterior(Vector2 playerPosition, Vector2 playerSize,
                        Vector2 &interiorSpawn) {
  if (interiorWorld) {
    return false;
  }
  const auto entrance = world.FindEntrance(playerPosition, playerSize);
  if (!entrance) {
    return false;
  }

  interiorWorld = std::make_unique<World>(entrance->worldPath);
  interiorTileset = LoadTexture(entrance->tilesetPath.c_str());
  if (interiorTileset.id == 0) {
    interiorWorld.reset();
    throw std::runtime_error("Could not load interior tileset: " +
                             entrance->tilesetPath);
  }
  outdoorReturnPosition = entrance->outdoorReturn;
  interiorSpawn = entrance->interiorSpawn;
  return true;
}

bool Map::LeaveInterior(Vector2 &outdoorPosition) {
  if (!interiorWorld) {
    return false;
  }
  if (interiorTileset.id != 0 && IsWindowReady()) {
    UnloadTexture(interiorTileset);
  }
  interiorTileset = {0};
  interiorWorld.reset();
  outdoorPosition = outdoorReturnPosition;
  return true;
}

void Map::Draw() {
  if (interiorWorld) {
    ClearBackground(BLACK);
    interiorWorld->Draw(interiorTileset);
  } else {
    world.Draw(outdoorTileset);
  }
}

void Map::UpdateActiveChunks(Vector2 playerPosition) {
  if (interiorWorld) {
    interiorWorld->UpdateActiveChunks(playerPosition);
  } else {
    world.UpdateActiveChunks(playerPosition);
  }
}

bool Map::Collides(Vector2 position, Vector2 size) const {
  return interiorWorld ? interiorWorld->Collides(position, size)
                       : world.Collides(position, size);
}

Vector2 Map::GetWorldSize() const {
  return interiorWorld ? interiorWorld->GetWorldSize() : world.GetWorldSize();
}

Vector2 Map::ClampPosition(Vector2 position, Vector2 size) const {
  return interiorWorld ? interiorWorld->ClampPosition(position, size)
                       : world.ClampPosition(position, size);
}

void Map::DrawMinimap(Rectangle bounds, Vector2 playerPosition) const {
  if (interiorWorld) {
    interiorWorld->DrawMinimap(bounds, playerPosition);
  } else {
    world.DrawMinimap(bounds, playerPosition);
  }
}
