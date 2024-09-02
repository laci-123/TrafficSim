#include "movable_point.hpp"

MovablePoint::MovablePoint(Vector2 position)
  :position{position}, velocity{Vector2{80.0f, 120.0f}}
{}
  
void MovablePoint::update(float dt, int window_width, int window_height) {
  Vector2 new_position = Vector2Add(this->position, Vector2Scale(this->velocity, dt));
  if(0 <= new_position.x && new_position.x <= window_width) {
    this->position.x = new_position.x;
  }
  else {
    this->velocity.x *= -1;
  }
  if(0 <= new_position.y && new_position.y <= window_height) {
    this->position.y = new_position.y;
  }
  else {
    this->velocity.y *= -1;
  }
}

void MovablePoint::render() const {
  DrawCircleV(this->position, 10.0f, PINK);
}
