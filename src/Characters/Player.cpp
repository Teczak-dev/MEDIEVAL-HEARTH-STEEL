#include "Characters/Player.hpp"
#include "raylib.h"
#include "raymath.h"

Player::Player(Vector2 position, float speed)
    : position(position), speed(speed), health(100, 100) {}

Player::~Player() {}

Vector2 Player::GetPosition() { return position; }

void Player::SetPosition(Vector2 newPosition) { position = newPosition; }

float Player::GetSpeed() { return speed; }

void Player::Update(float deltaTime, InputSystem &inpSys,
                    const int &screenWidth, const int &screenHeight,
                    Damage &damage) {

  if (inpSys.IsReleasedKeyName("damage")) {
    damage.TakeDamage(10, DamageType::Physical, health);
  }
  if (inpSys.IsReleasedKeyName("heal")) {
    health.Heal(10);
  }

  Vector2 movement = {0, 0};
  if (inpSys.IsDownKeyName("move_up"))
    movement.y -= 1.0f;
  if (inpSys.IsDownKeyName("move_down"))
    movement.y += 1.0f;
  if (inpSys.IsDownKeyName("move_left"))
    movement.x -= 1.0f;
  if (inpSys.IsDownKeyName("move_right"))
    movement.x += 1.0f;

  if (Vector2Length(movement) > 0) {
    movement = Vector2Normalize(movement);
  }

  const float movementSpeed =
      GetSpeed() * (inpSys.IsDownKeyName("sprint") ? 2.0f : 1.0f);
  Vector2 velocity = Vector2Scale(movement, movementSpeed * deltaTime);
  Vector2 newPosition = Vector2Add(GetPosition(), velocity);
  if (health.GetCurrentHealth() > 0) {
    SetPosition(newPosition);
  }
  if (movement.x != 0 || movement.y != 0)
    lastDirection = movement;
}

void Player::Draw() {
  DrawRectangle(position.x, position.y, 64, 64, BLUE);
  DrawRectangle(position.x + (32 - (16.0f / 2)) + (lastDirection.x * 48),
                position.y + (32 - (16.0f / 2)) + (lastDirection.y * 48), 16,
                16, WHITE);
}
