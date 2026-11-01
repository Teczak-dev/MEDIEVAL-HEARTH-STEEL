#include "Gameplay/Health.hpp"
#include <algorithm>
#include <iostream>

Health::Health(int maxHealth, int currentHealth)
    : maxHealth(std::max(maxHealth, 100)),
      currentHealth(std::clamp(currentHealth, 0, maxHealth)) {}

Health::~Health() {}

void Health::Heal(const int &amount) {
  currentHealth += amount;
  if (currentHealth > maxHealth) {
    currentHealth = maxHealth;
  }
}

void Health::removeHealth(int amount) {
  currentHealth -= amount;
  if (currentHealth < 0) {
    currentHealth = 0;
  }
}

int Health::GetCurrentHealth() const { return currentHealth; }
