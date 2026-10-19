#pragma once

#include "raylib.h"

class TestMap {
public:
  TestMap(int sizeX, int sizeY, int width, int height);
  ~TestMap();
  int GetSize();
  int GetWidth();
  int GetHeight();
  void Draw();

private:
  int sizeX;
  int sizeY;
  int width;
  int height;
};
