#include "raylib.h"
#include "road_segment.hpp"
#include <string>
#include <fstream>

int main(int argc, char **argv) {
  int init_window_width { std::stoi(argv[1]) };
  int init_window_height{ std::stoi(argv[2]) };

  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
  InitWindow(init_window_width, init_window_height, "Raylib WASM Example");
  SetWindowState(FLAG_WINDOW_RESIZABLE);

  RoadSegment road{Vector2{10.0f, 10.0f}, Vector2{100.0f, 50.0f}};
  
  while (!WindowShouldClose()) {
    float dt = GetFrameTime();
    road.update(dt);

    BeginDrawing();
      ClearBackground(BROWN);
      road.render();
    EndDrawing();
  }
  
  CloseWindow();
  return 0;
}
