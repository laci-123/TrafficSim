#include <string>
#include "raylib.h"
#include "movable_point.hpp"

int main(int argc, char **argv) {
  int init_window_width { std::stoi(argv[1]) };
  int init_window_height{ std::stoi(argv[2]) };
  
  SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(init_window_width, init_window_height, "Raylib WASM Example");
  SetWindowState(FLAG_WINDOW_RESIZABLE);

  MovablePoint mp1{Vector2{10.0f, 5.0f}, 10.0f, GREEN};
  MovablePoint mp2{Vector2{100.0f, 10.0f}, 10.0f, BLUE};
  MovablePoint mp3{Vector2{30.0f, 50.0f}, 10.0f, BLUE};

  mp1.attach(mp2);
  mp1.attach(mp3);
  
  while (!WindowShouldClose()) {
    float dt = GetFrameTime();
    mp1.update(dt);
    mp2.update(dt);
    mp3.update(dt);

    BeginDrawing();
      ClearBackground(BLACK);
      mp1.render();
      mp2.render();
      mp3.render();
    EndDrawing();
  }
  
  CloseWindow();
  return 0;
}
