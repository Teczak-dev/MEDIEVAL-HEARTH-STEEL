#pragma once

// Applies different types of damage to objects with health.
#include "Core/Types.hpp"
#include "Gameplay/Health.hpp"

class Damage {
public:
  void TakeDamage(int amount, DamageType type, Health &objectHealth);
};
