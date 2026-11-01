#pragma once

// Provides reusable user-interface controls and visual elements.
class UIElements {
public:
  UIElements();
  ~UIElements();
  void UI_Slider(int x, int y, int width, int height, int border, float *value,
                 float minValue, float maxValue);
};
