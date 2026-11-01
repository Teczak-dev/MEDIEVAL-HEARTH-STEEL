#include "Systems/InputSystem.hpp"
#include "raylib.h"
#include <cstring>
#include <fstream>
#include <nlohmann/json.hpp>
#include <filesystem>
#include <string>

InputSystem::InputSystem() {
  std::string inputPath = "assets/config/input.json";
#ifdef __APPLE__
  const std::string bundleInputPath =
      std::string(GetApplicationDirectory()) +
      "../Resources/assets/config/input.json";
  if (FileExists(bundleInputPath.c_str())) {
    inputPath = bundleInputPath;
  }
#endif

  std::ifstream f(inputPath);
  if (!f.is_open()) {
    f.clear();
    const std::filesystem::path executablePath =
        std::filesystem::path(GetApplicationDirectory()) /
        "assets/config/input.json";
    f.open(executablePath);
  }

  if (f.is_open()) {
    try {
      nlohmann::json data = nlohmann::json::parse(f);

      // 1. Iterate over input categories (e.g., "movement", "actions")
      for (auto &[categoryName, categoryContent] : data.items()) {

        // 2. Iterate over actions within each category (e.g., "move_up")
        for (auto &[actionName, keys] : categoryContent.items()) {
          std::vector<int> keyCodes;

          // 3. Convert each key name from the JSON array (e.g., ["W", "UP"])
          for (const auto &key : keys) {
            if (stringToKey.find(key) != stringToKey.end()) {
              keyCodes.push_back(stringToKey[key]);
            }
          }
          actionBindings[actionName] = keyCodes;
        }
      }
    } catch (const nlohmann::json::exception &error) {
      TraceLog(LOG_ERROR, "Could not parse input configuration: %s", error.what());
    }
  } else {
    TraceLog(LOG_WARNING, "Could not open input configuration: %s", inputPath.c_str());
  }
};
InputSystem::~InputSystem() {};

bool InputSystem::IsDownKeyName(const char *name) {
  // 1. Find the requested action in the bindings map
  auto it = actionBindings.find(name);
  if (it != actionBindings.end()) {
    // 2. Check every key assigned to the action
    for (int keyCode : it->second) {
      // 3. Return true when any assigned key is held down
      if (IsKeyDown(keyCode)) {
        return true;
      }
    }
  }
  return false;
}

bool InputSystem::IsPressedKeyName(const char *name) {
  // 1. Find the requested action in the bindings map
  auto it = actionBindings.find(name);
  if (it != actionBindings.end()) {
    // 2. Check every key assigned to the action
    for (int keyCode : it->second) {
      // 3. Return true when any assigned key was pressed
      if (IsKeyPressed(keyCode)) {
        return true;
      }
    }
  }
  return false;
}

bool InputSystem::IsReleasedKeyName(const char *name) {
  // 1. Find the requested action in the bindings map
  auto it = actionBindings.find(name);
  if (it != actionBindings.end()) {
    // 2. Check every key assigned to the action
    for (int keyCode : it->second) {
      // 3. Return true when any assigned key was released
      if (IsKeyReleased(keyCode)) {
        return true;
      }
    }
  }
  return false;
}
