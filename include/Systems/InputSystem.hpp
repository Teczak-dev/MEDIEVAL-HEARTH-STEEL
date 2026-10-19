#pragma once

#include "raylib.h"
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
#include <vector>
class InputSystem {
public:
  InputSystem();
  ~InputSystem();
  bool IsDownKeyName(const char *name);
  bool IsPressedKeyName(const char *name);
  bool IsReleasedKeyName(const char *name);

private:
  std::unordered_map<std::string, std::vector<int>> actionBindings;
  std::unordered_map<std::string, int> stringToKey = {
      {"W", KEY_W},       {"S", KEY_S},         {"A", KEY_A},
      {"D", KEY_D},       {"UP", KEY_UP},       {"DOWN", KEY_DOWN},
      {"LEFT", KEY_LEFT}, {"RIGHT", KEY_RIGHT}, {"SPACE", KEY_SPACE},
      {"Q", KEY_Q},       {"E", KEY_E},         {"R", KEY_R},
      {"F", KEY_F},       {"G", KEY_G},         {"H", KEY_H},
      {"J", KEY_J},       {"K", KEY_K},         {"L", KEY_L},
      {"Z", KEY_Z},       {"X", KEY_X},         {"C", KEY_C},
      {"V", KEY_V},       {"B", KEY_B},         {"N", KEY_N},
      {"M", KEY_M}};
};
