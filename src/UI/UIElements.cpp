#include "UI/UIElements.hpp"
#include "raylib.h"

UIElements::UIElements() {}

UIElements::~UIElements() {}

void UIElements::UI_Slider(int x, int y, int width, int height, int border,
                           float *value, float minValue, float maxValue) {

  DrawRectangle(x - border, y - border, width + border, height + border, BLACK);
}
