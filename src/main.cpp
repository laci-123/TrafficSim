#include "raylib.h"
#include "road_segment.hpp"
#include "road_network.hpp"
#include "intersection.hpp"
#include "assets.hpp"
#include <string>
#include <memory>

int main(int argc, char **argv) {
  int init_window_width { std::stoi(argv[1]) };
  int init_window_height{ std::stoi(argv[2]) };

  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
  InitWindow(init_window_width, init_window_height, "Raylib WASM Example");
  SetWindowState(FLAG_WINDOW_RESIZABLE);

  Assets assets;
  RoadNetwork network{assets};
  network.add_part(std::make_unique<RoadSegment>(RoadSegment{Vector2{10.0f, 10.0f}, Vector2{100.0f, 50.0f}, network}));
  network.add_part(std::make_unique<RoadSegment>(RoadSegment{Vector2{10.0f, 40.0f}, Vector2{200.0f, 50.0f}, network}));
  network.add_part(std::make_unique<RoadSegment>(RoadSegment{Vector2{50.0f, 20.0f}, Vector2{300.0f, 10.0f}, network}));
  network.add_part(std::make_unique<Intersection>(Intersection{Vector2{100, 100}, network}));
  network.add_part(std::make_unique<Intersection>(Intersection{Vector2{120, 150}, network}));
  
  while (!WindowShouldClose()) {
    float dt = GetFrameTime();
    network.update(dt);

    BeginDrawing();
      ClearBackground(BROWN);
      network.render();
    EndDrawing();
  }
  
  CloseWindow();
  return 0;
}
