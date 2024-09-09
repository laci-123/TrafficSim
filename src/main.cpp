#include "raylib.h"
#include "game.hpp"

int main(int argc, char **argv) {
  int init_window_width { std::stoi(argv[1]) };
  int init_window_height{ std::stoi(argv[2]) };

  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
  InitWindow(init_window_width, init_window_height, "Raylib WASM Example");
  SetWindowState(FLAG_WINDOW_RESIZABLE);

  Game game;
  
  while (!WindowShouldClose()) {
    game.update();

    BeginDrawing();
      game.render();
    EndDrawing();
  }
  
  CloseWindow();
  return 0;
}
