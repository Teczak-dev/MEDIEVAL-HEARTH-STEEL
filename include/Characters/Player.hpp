#pragma once

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
  void Update(float deltaTime, InputSystem &inpSys, int screenWidth,
              int screenHeight);

  int GetHealth();
  void TakeDamage(int damage);
  void Heal(int amount);

private:
  Vector2 position;
  Vector2 lastDirection = {0.0f, 0.1f};
  float speed;
  int health = 100;
};
