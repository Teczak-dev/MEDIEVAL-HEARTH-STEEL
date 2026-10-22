#include "Gameplay/Damage.hpp"

void Damage::TakeDamage(int amount, DamageType type, Health &objectHealth) {
  // Implement damage logic based on the type of damage
  switch (type) {
  case DamageType::Physical:
  case DamageType::Magical:
  case DamageType::Fire:
  case DamageType::Ice:
  case DamageType::Poison:
    objectHealth.removeHealth(amount);
    break;
  }
}
