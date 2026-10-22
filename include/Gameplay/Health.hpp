#pragma once

class Health {
public:
  Health(int maxHealth, int currentHealth);
  ~Health();
  void Heal(const int &amount);
  void removeHealth(int amount);
  int GetCurrentHealth() const;

private:
  int currentHealth;
  int maxHealth;
};
