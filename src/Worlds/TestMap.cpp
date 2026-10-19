#include "Worlds/TestMap.hpp"
#include "raylib.h"

TestMap::TestMap(int sizeX, int sizeY, int width, int height)
    : sizeX(sizeX), sizeY(sizeY), width(width), height(height) {}

TestMap::~TestMap() {}

int TestMap::GetSize() { return sizeX * sizeY; }

int TestMap::GetWidth() { return width; }

int TestMap::GetHeight() { return height; }

void TestMap::Draw() {
  for (int pos = 0; pos < GetSize(); pos++) {
    int x = (pos % GetWidth()) * 64;
    int y = (pos / GetWidth()) * 64;
    DrawRectangle(x, y, 64, 64, DARKGRAY);
    DrawRectangleLines(x, y, 64, 64, GRAY);
  }
}
