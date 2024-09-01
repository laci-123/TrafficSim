#include <iostream>
#include "raylib.h"
#include "movable_point.hpp"

int main() {
  std::cout << "The quick brown fox jumps over the lazy dog." << std::endl;
  
  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
  InitWindow(512, 512, "Raylib WASM Example");
  SetWindowState(FLAG_WINDOW_RESIZABLE);

  MovablePoint mp{Vector2{10.0f, 5.0f}};
  
  while (!WindowShouldClose()) {
    float dt = GetFrameTime();
    mp.update(dt);

    BeginDrawing();
      ClearBackground(BLACK);
      mp.render();
    EndDrawing();
  }
  
  CloseWindow();
  return 0;
}
