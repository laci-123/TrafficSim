#include "movable_point.hpp"

MovablePoint::MovablePoint(Vector2 position)
  :position{position}
{}
  
void MovablePoint::update(float dt) {
  this->position = Vector2Add(this->position, Vector2{0.1f, 0.1f});
}

void MovablePoint::render() const {
  DrawCircleV(this->position, 10.0f, PINK);
}
