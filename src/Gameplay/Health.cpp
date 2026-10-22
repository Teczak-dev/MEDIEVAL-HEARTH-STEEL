#include "Gameplay/Health.hpp"

Health::Health(int maxHealth, int currentHealth)
    : maxHealth(maxHealth), currentHealth(currentHealth) {}

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
