#include <iostream>
#include "raylib.h"

int main() {
  std::cout << "The quick brown fox jumps over the lazy dog." << std::endl;
  
  InitWindow(512, 512, "Raylib WASM Example");
  
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawCircle(100, 100, 10.0f, GREEN);
    EndDrawing();
  }
  
  CloseWindow();
  return 0;
}
