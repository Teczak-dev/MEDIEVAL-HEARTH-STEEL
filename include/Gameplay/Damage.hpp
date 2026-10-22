#pragma once
#include "Core/Types.hpp"
#include "Gameplay/Health.hpp"

class Damage {
public:
  void TakeDamage(float amount, DamageType type, Health &objectHealth);
};
