#include "movable_point.hpp"

MovablePoint::MovablePoint(Vector2 position, float radius, Color color)
  :position{position}, radius{radius}, color{color}
{}

void MovablePoint::attach(MovablePoint& other) {
  this->attached_points.push_back(other);
}
  
bool MovablePoint::update(float dt) {
  if(!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    this->mouse_offset = {};
    return false;
  }
  
  Vector2 mouse = GetMousePosition();
  if(this->mouse_offset) {
    Vector2 old_position{ this->position };
    this->position = Vector2Add(mouse, *this->mouse_offset);
    Vector2 translation{ Vector2Subtract(this->position, old_position) };
    
    for(MovablePoint& point: this->attached_points) {
      point.position = Vector2Add(point.position, translation);
    }

    return !Vector2Equals(this->position, old_position);
  }
  else if (CheckCollisionPointCircle(mouse, this->position, this->radius)) {
    this->mouse_offset = Vector2Subtract(this->position, mouse);
  }

  return false;
}

void MovablePoint::render() const {
  DrawCircleV(this->position, this->radius, this->color);
}
