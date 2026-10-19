#include "Characters/Player.hpp"
#include "raylib.h"
#include "raymath.h"

Player::Player(Vector2 position, float speed)
    : position(position), speed(speed) {}

Player::~Player() {}

Vector2 Player::GetPosition() { return position; }

void Player::SetPosition(Vector2 newPosition) { position = newPosition; }

float Player::GetSpeed() { return speed; }

int Player::GetHealth() { return health; }

void Player::TakeDamage(int damage) {
  health -= damage;
  if (health < 0)
    health = 0;
}

void Player::Heal(int amount) {
  health += amount;
  if (health > 100)
    health = 100;
}

void Player::Update(float deltaTime, InputSystem &inpSys, int screenWidth,
                    int screenHeight) {

  // TEST: TAKING DAMAGE/HEALING AND HEALTH BAR Update
  if (inpSys.IsReleasedKeyName("damage")) {
    TakeDamage(10);
  }
  if (inpSys.IsReleasedKeyName("heal")) {
    Heal(10);
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

  Vector2 velocity = Vector2Scale(movement, GetSpeed() * deltaTime);
  Vector2 newPosition = Vector2Add(GetPosition(), velocity);
  if (GetHealth() > 0) { // simplyfide death check, player can't move if dead
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
