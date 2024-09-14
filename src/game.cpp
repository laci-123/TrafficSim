#include "game.hpp"
#include "road_segment.hpp"
#include "intersection.hpp"
#include "raylib.h"

Game::Game()
  :network{this->assets},
   toolbox{
     Vector2{20, 30},
     this->network,
     {
       Entry{"road segment", [](Vector2 position, RoadNetwork& network){return std::make_unique<RoadSegment>( RoadSegment{ position, network});}},
       Entry{"intersection", [](Vector2 position, RoadNetwork& network){return std::make_unique<Intersection>(Intersection{position, network});}},
     }
   }
{}

void Game::update() {
  this->network.update(GetFrameTime());
  if(std::unique_ptr<RoadNetworkPart> part = this->toolbox.update()) {
    this->network.add_part(std::move(part));
  }
}

void Game::render() const {
  ClearBackground(BROWN);
  this->network.render();
  this->toolbox.render();
}
