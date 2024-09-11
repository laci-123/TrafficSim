#include "intersection.hpp"


Intersection::Intersection(Vector2 position, RoadNetwork& network)
  :Dragable{position},
   network{network},
   index_in_network{network.next_index()},
   tile{network.get_assets().get_texture("assets/four_way_intersection.svg", 39, 39)}
{}

void Intersection::update(float dt) {
  Dragable::update();
}

void Intersection::render() const {
  DrawTextureEx(*this->tile, this->get_position(), 0, 1, WHITE);
}

bool Intersection::is_mouse_over(Vector2 mouse) const {
  return CheckCollisionPointCircle(mouse, this->get_position(), 40);
}
