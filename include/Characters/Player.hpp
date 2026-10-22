#pragma once

#include "Gameplay/Damage.hpp"
#include "Gameplay/Health.hpp"
#include "Systems/InputSystem.hpp"
#include "raylib.h"

class Player {

public:
  Player(Vector2 position, float speed);
  ~Player();
  Vector2 GetPosition();
  void SetPosition(Vector2 newPosition);
  float GetSpeed();
  void Draw();
  void Update(float deltaTime, InputSystem &inpSys, const int &screenWidth,
              const int &screenHeight, Damage &damage);
  Health health;
  void TakeDamage(int damage);

private:
  Vector2 position;
  Vector2 lastDirection = {0.0f, 0.1f};
  float speed;
};
