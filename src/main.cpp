#include <string>
#include "raylib.h"
#include "movable_point.hpp"

int main(int argc, char **argv) {
  int init_window_width { std::stoi(argv[1]) };
  int init_window_height{ std::stoi(argv[2]) };
  
  SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(init_window_width, init_window_height, "Raylib WASM Example");
  SetWindowState(FLAG_WINDOW_RESIZABLE);

  MovablePoint mp{Vector2{10.0f, 5.0f}, 10.0f, GREEN};
  
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
