#include "Gameplay/Damage.hpp"

void Damage::TakeDamage(float amount, DamageType type, Health &objectHealth) {
  // Implement damage logic based on the type of damage
  switch (type) {
  case DamageType::Physical:
    // Apply physical damage logic
    objectHealth.removeHealth(amount);
  case DamageType::Magical:
    // Apply magical damage logic
    objectHealth.removeHealth(amount);
    break;
  case DamageType::Fire:
    // Apply fire damage logic
    objectHealth.removeHealth(amount);
    break;
  case DamageType::Ice:
    // Apply ice damage logic
    objectHealth.removeHealth(amount);
    break;
  case DamageType::Poison:
    // Apply poison damage logic
    objectHealth.removeHealth(amount);
    break;
  default:
    // Handle unknown damage type
    objectHealth.removeHealth(amount);
    break;
  }
}
