#include "intersection.hpp"


Intersection::Intersection(Vector2 position, RoadNetwork& network)
  :position{position},
   network{network},
   index_in_network{network.next_index()},
   tile{network.get_assets().get_texture("assets/four_way_intersection.svg", 39, 39)}
{}

void Intersection::update(float dt) {}

void Intersection::render() const {
  DrawTextureEx(*this->tile, this->position, 0, 1, WHITE);
}
