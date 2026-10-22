#pragma once
#include "Core/Types.hpp"
#include "Gameplay/Health.hpp"

class Damage {
public:
  void TakeDamage(int amount, DamageType type, Health &objectHealth);
};
