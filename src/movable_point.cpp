#include "movable_point.hpp"

MovablePoint::MovablePoint(Vector2 position, float radius, Color color)
  :position{position}, radius{radius}, color{color}
{}

void MovablePoint::attach(MovablePoint& other) {
  this->attached_points.push_back(other);
}
  
void MovablePoint::update(float dt) {
  if(!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    this->mouse_offset = {};
    return;
  }
  
  Vector2 mouse = GetMousePosition();
  if(this->mouse_offset) {
    Vector2 old_positon{ this->position };
    this->position = Vector2Add(mouse, *this->mouse_offset);
    Vector2 translation{ Vector2Subtract(this->position, old_positon) };
    
    for(MovablePoint& point: this->attached_points) {
      point.position = Vector2Add(point.position, translation);
    }
  }
  else if (CheckCollisionPointCircle(mouse, this->position, this->radius)) {
    this->mouse_offset = Vector2Subtract(this->position, mouse);
  }
}

void MovablePoint::render() const {
  DrawCircleV(this->position, this->radius, this->color);
}
